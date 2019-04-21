# C Shell
This is a simple shell-like command interpreter. It supports basic operations like executing programs (using `execvp` internally) and changing directories with `cd` (using `chdir`). Implementation of additional features is planned.

This shell is *not* POSIX-compliant and does not have any scripting capabilities. That's mainly because it does not have a complex parser. Instead, single lines are read from `stdin` and split at delimiters like ` ` or tabs. Only a limited set of *special characters* like `|` are treated differently.

GNU shell documentation that covers the basic features of `bash` can be found [here](https://www.gnu.org/software/bash/manual/html_node/Basic-Shell-Features.html#Basic-Shell-Features). Implementing some of these features might be educational, too.

## Roadmap of Future Features

- [ ] implement two-way pipes with `|` (`pipe` system call)
- [ ] implement file IO redirection with `>` (`open` instead of `pipes`)
- [ ] implement `setenv` in child process, i.e. in cmds like `VAR=val echo $VAR` prints `val`
- [ ] implement shell variable expansion via `getenv` (like `echo $HOME` prints `/home/daniel`)
- [ ] implement background processes with `&` (don't wait on child process)

---

- [ ] implement arbitrary-length pipes
- [ ] implement redirection of fd 2 (`stderr` like `echo 'err' 2> out`)
- [ ] implement redirection of fd 2 to fd 1 (like `echo 'err' > out 2>&1`)
- [ ] implement `export` builtin which sets a var in the _parent_
- [ ] implement wildcard expansion (look at `glob` in `glob.h`)
- [ ] implement aliasing of commands
- [ ] support a settings file:
    - [ ] aliases
    - [ ] exported variables
    - [ ] `$PS1`

## Some Useful Documentation
__Pipes__:
```
int pipe_fds[2];
pipe(pipe_fds);  // puts returns [4, 5] in pipe_fds
```

To create a pipe `ls | wc`, we need to:

1. create a pipe with `pipe`. Imagine that this creates file descriptors `4` and `5`.
2. fork twice (once for `ls` and once for `wc`).
  ```
  parent: pid 1000, stdin: terminal, stdout, terminal
  ---- fork twice ----
  parent: pid 1000, stdin: terminal, stdout: terminal
  child 1: pid 2000, stdin: terminal, stdout: terminal (for `ls`)
  child 2: pid 3000, stdin: terminal, stdout: terminal (for `wc`)
  ```
3. In child 1, run `dup2(pipe_fds[1], 1)` and exec `ls`
4. In child 2, run `dup2(pipe_fds[0], 0)` and exec `wc`
5. Close both ends of the pipe in the parent process.

- Write a `fork_and_exec_with_io(cmd* cmd, int stdout_fd, int stdin_fd)` that forks and execs the specified command and changes its stdin and stdout as needed

- Use `fork_and_exec_with_io` to implement pipes with 2 elements.

## License
All code in this repository is MIT-licensed (see [license file](LICENSE.md)).
