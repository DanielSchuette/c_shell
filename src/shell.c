/*
 * shell.c is the entry point for the shell.
 *
 * Author: Daniel Schuette (github.com/DanielSchuette)
 * License: MIT (see LICENSE.md)
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cmd.h"
#include "utils.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    const char *ps1 = NULL;
    pid_t pid;

    ps1 = get_from_env("MY_PRMPT", PS1); /* determine which prompt to use */

    while (prmpt(ps1) || (get_line(&line, &len) > 0)) {
        command *cmd = get_cmd(line);

        if ((pid = fork()) < 0) { /* fork error */
            fprintf(stderr, "Error: Failed to fork another process.\n");
            exit(1);
        } else if (pid == 0) { /* child */
            if (execvp(cmd->prog, cmd->args) < 0) {
                fprintf(stderr, "Error: Unknown command.\n");
            }
        } else { /* parent */
            wait(NULL);
        }

        free_cmd(cmd);
    }
    free(line); /* if SIGINT exists instead of ^D, 120 bytes are lost */
    fprintf(stderr, "\n");

    return 0;
}
