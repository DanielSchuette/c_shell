#ifndef __CMD_H__
#define __CMD_H__

typedef struct {          /* represent a single shell command: */
    char *prog;           /* name of command, should be command->args[0] */
    char **args;          /* array of cmd args */
} command;

/*
 * Extract a command and arguments from an input line. It is split into tokens,
 * which are then put into a `command' struct and returned to the caller.
 */
command *get_cmd(char *);

/* Allocate and NULL memory for a `command' struct. */
int init_cmd(command *);

/* Free memory of a `command' struct. */
void free_cmd(command *);

#endif /* __CMD_H__ */
