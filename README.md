# Roadmap of Features to be Implemented
- [x] make `exit` builtin work
- [x] fix memory leaks
- [x] set up a `SIGINT` signal handler (^D still sends an EOF to shell)
- [x] add a `cd` builtin

---

- implement parsing of single- and double-quoted strings
- implement `setenv` in child process, i.e. in cmds like `VAR=val echo $VAR` prints `val`
- implement background processes with `&` (don't wait on child process)

---

- implement IO redirects
- implement two-way pipes (`pipes` system call)
- implement arbitrary-length (?) pipes
- implement file IO redirection (`open` instead of `pipes`)
- implement redirection of fd 2 (`stderr` like `echo 'err' 2> out`)
- implement redirection of fd 2 to fd 2 (like `echo 'err' > out 2>&1`)
- implement shell variable expansion via `getenv` (like `echo $HOME` prints `/home/daniel`)
- implement `export` builtin which sets a var in the _parent_
- implement wildcard expansion (look at `glob` in `glob.h`)

## Documentation
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
