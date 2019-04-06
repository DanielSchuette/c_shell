#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"
#include "utils.h"

#define  DEBUG  1
#define  PS1    "\033[31m[[daniel@shell]]\033[m "   /* `man console_codes' */

int main(void)
{
    char        *line   = NULL;
    size_t      len     = 0;
    const char  *ps1    = NULL;
    pid_t       pid;

    ps1 = get_from_env("MY_PRMPT", PS1); /* determine which prompt to use */

    while(prmpt(ps1) || (get_line(&line, &len) > 0)) {
        command *cmd = get_cmd(line);

        if ((pid = fork()) < 0) { /* fork error */
            fprintf(stderr, "Error: Failed to fork another process.\n");
            exit(1);
        } else if (pid == 0) {    /* child */
            if (execvp(cmd->prog, cmd->args) < 0) {
                fprintf(stderr, "Error: Unknown command.\n");
            }
        } else {                  /* parent */
            wait(NULL);
        }

        free_cmd(cmd);
    }
    free(line);     /* if SIGINT exists instead of ^D, 120 bytes are lost */
    fprintf(stderr, "\n");

    return 0;
}

int prmpt(const char* ps1)
{
    fprintf(stderr, "%s", ps1);
    return 0;
}

ssize_t get_line(char **line, size_t *len)
{
    ssize_t siz = getline(line, len, stdin);
    return siz;
}

const char *get_from_env(const char *name, const char *dflt)
{
    const char *ptr = getenv(name);

    if (DEBUG && ptr == NULL)
        fprintf(stderr, "Error: Could not get `$%s' from env.\n", name);
    if (ptr == NULL)
        return dflt;

    return ptr;
}
