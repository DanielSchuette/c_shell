#ifndef __UTILS_H__
#define __UTILS_H__

#define  BUF_SIZE           4096
#define  DELIMS             " \t\n\r"           /* valid token delimiters */

typedef struct {          /* represent a single shell command: */
    char *prog;           /* name of command, should be command->args[0] */
    char **args;          /* array of cmd args */
} command;


enum builtin {
    exit_builtin          /* builtin `exit' command returns from shell */
};

/*
 * Extract a command and arguments from an input line. It is split into tokens,
 * which are then put into a `command' struct and returned to the caller.
 */
command *get_cmd(char *);

/*
 * Get the next non-empty token from `line'. Returns NULL if `line' is empty or
 * exhausted, i.e. no more tokens are available. Empty tokens (i.e. "") are
 * never returned to the caller.
 */
char *get_token(char **);

/*
 * Try to interpret a token as a builtin. If the token matches a builtin,
 * return -1, otherwise return 0.
 */
enum builtin builtin_action(const char *);

/* Allocate and NULL memory for a `command' struct. */
int init_cmd(command *);

/* Free memory of a `command' struct. */
void free_cmd(command *);

#endif  /* __UTILS_H__ */
