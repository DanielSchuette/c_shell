#ifndef __UTILS_H__
#define __UTILS_H__

#define MAX_LEN 1024
#define TOKEN_SEP " \t\n\r"

/* Struct representing a shell command and its arguments. */
typedef struct {
    char* progname;       /* name of the executable */

    int redirect[2];      /* IO redirects; i'th elem is used as i'th fd i in */
                          /* the child; a value of -1 indicates no redirect */
    char* args[];         /* cmd args which must be '\0'-terminated */
} cmd_struct;

/* Struct representing a pipeline of cmds. cmd[i]-out goes to cmd[i+1]-in. */
typedef struct {
    int n_cmds;           /* total number of commands */
    cmd_struct* cmds[];   /* array of command structs */
} pipeline_struct;

/*
 * Parses str into a freshly allocated cmd_struct and returns a pointer to it.
 * The redirects in the returned cmd_struct will be set to -1, ie no redirect.
 */
cmd_struct* parse_command(char* str);

/*
 * Parses str into a freshly allocated pipeline_struct and returns a pointer to
 * it.  All cmd_structs in cmds will also be freshy allocated, and have their
 * redirects set to -1, ie no redirect.
 */
pipeline_struct* parse_pipeline(char* str);

/* For debugging purposes. */
void print_command(cmd_struct* command);
void print_pipeline(pipeline_struct* pipeline);

#endif  /* __UTILS_H__ */
