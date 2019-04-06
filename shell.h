#include <unistd.h>

#include "utils.h"

#ifndef __SHELL_H__
#define __SHELL_H__

/* Print the shell prompt. */
int prmpt(const char *);

/*
 * A simple wrapper around `getline' which can be updated to be an entry point
 * to a proper parser.
 */
ssize_t get_line(char **, size_t *);

/*
 * Get an environmental variable and return a pointer to it. The second arg is
 * used as a default return value if the env var could not be found.
 */
const char *get_from_env(const char *, const char *);

#endif /* __SHELL_H__ */
