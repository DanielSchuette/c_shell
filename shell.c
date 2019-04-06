#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"
#include "utils.h"

#define  DEBUG  0
#define  PS1    "\033[31m[[daniel@shell]]\033[m "    /* man console_codes */

int main(void)
{
    char        *line   = NULL;
    size_t      len     = 0;
    const char  *ps1    = NULL;

    ps1 = get_from_env("MY_PRMPT", PS1);     /* determine which prompt to use */

    while(prompt_and_get_input(ps1, &line, &len) > 0) {
        pipeline_struct* pipeline = parse_pipeline(line);
        int n_pipes = pipeline->n_cmds - 1;

        if (DEBUG)
            print_pipeline(pipeline);

        /* pipes[i] redirects from pipeline->cmds[i] to pipeline->cmds[i+1]. */
        int (*pipes)[2] = calloc(sizeof(int[2]), n_pipes);

        for (int i = 1; i < pipeline->n_cmds; ++i) {
            pipe(pipes[i-1]);
            pipeline->cmds[i]->redirect[STDIN_FILENO] = pipes[i-1][0];
            pipeline->cmds[i-1]->redirect[STDOUT_FILENO] = pipes[i-1][1];
        }

        for (int i = 0; i < pipeline->n_cmds; ++i) {
            run_with_redir(pipeline->cmds[i], n_pipes, pipes);
        }

        close_all_pipes(n_pipes, pipes);

        /* Wait for all children to terminate. Rule 0: not checking status. */
        for (int i = 0; i < pipeline->n_cmds; ++i) {
          wait(NULL);
        }
    }

    fprintf(stdin, "\n");
    return 0;
}

ssize_t prompt_and_get_input(const char* prompt, char **line, size_t *len)
{
    fputs(prompt, stderr);
    return getline(line, len, stdin);
}

void close_all_pipes(int n_pipes, int (*pipes)[2])
{
    for (int i = 0; i < n_pipes; ++i) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

int exec_with_redir(cmd_struct* command, int n_pipes, int (*pipes)[2])
{
    int fd = -1;

    for (int i = 0; i < 2; i++) {
        if ((fd = command->redirect[i]) != -1) {
            dup2(fd, STDIN_FILENO);
        }
    }

    close_all_pipes(n_pipes, pipes);
    return execvp(command->progname, command->args);
}

pid_t run_with_redir(cmd_struct* command, int n_pipes, int (*pipes)[2])
{
    pid_t child_pid = fork();

    if (child_pid) {                /* parent */
        switch(child_pid) {
            case -1:
                fprintf(stderr, "Error.\n");
                return -1;
            default:
                return child_pid;
        }
    } else {                        /* child */
        exec_with_redir(command, n_pipes, pipes);
        perror("Error");
        return 0;
    }
}

const char *get_from_env(const char *name, const char *dflt)
{
    const char *ptr = getenv(name);

    if (DEBUG && ptr == NULL)
        fprintf(stderr, "Error: Could not get `$%s' from env.", name);
    if (ptr == NULL)
        return dflt;

    return ptr;
}
