#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"
#include "cmd.h"
#include "token.h"
#include "utils.h"

command *get_cmd(char *line)
{
    command *cmd;
    char *token;
    int i = 0;

    /* allocate `command' struct */
    cmd = malloc(sizeof(command));
    if (!cmd || init_cmd(cmd)) {
        fprintf(stderr, "Error: Not enough memory.\n");
        free_cmd(cmd);
        exit(1);
    }
    cmd->built = no_builtin;

    /* tokenize input and add result to `command' struct */
    while ((token = get_token(&line))) {
        /* for first token, test if it's a builtin */
        enum builtin bi;
        if ((i == 0) && (bi = builtin_action(token)))
            cmd->built = bi; /* set builtin field of command struct */

        /* add token to argument array */
        cmd->args[i] = token;

        if (i == BUF_SIZE) {
            fprintf(stderr, "Error: Too many arguments.\n");
            exit(1);
        }
        i++;
    }
    cmd->prog = cmd->args[0]; /* point prog name to 1'st arg or NULL */

    return cmd;
}

int init_cmd(command *cmd)
{
    /* allocate BUF_SIZE char ptrs for argument array */
    cmd->args = malloc(sizeof(char *) * BUF_SIZE);

    if (cmd->args) {
        for (int i = 0; i < BUF_SIZE; i++) /* NULL all ptrs for `execvp' */
            cmd->args[i] = NULL;
        return 0; /* successfully allocated memory */
    }

    return -1;
}

void free_cmd(command *cmd)
{
    free(cmd->args);
    free(cmd);
}
