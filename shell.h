#include <unistd.h>

#include "utils.h"

#ifndef __SHELL_H__
#define __SHELL_H__

/* Doc. */
ssize_t prompt_and_get_input(const char*, char **, size_t *);

/* Doc. */
void close_all_pipes(int, int (*)[2]);

/* Doc. */
int exec_with_redir(cmd_struct *, int , int (*)[2]);

/* Doc. */
pid_t run_with_redir(cmd_struct *, int , int (*)[2]);

/*
 * Get an environmental variable and return a pointer to it. The second arg is
 * used as a default return value if the env var could not be found.
 */
const char *get_from_env(const char *, const char *);

#endif /* __SHELL_H__ */
