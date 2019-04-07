#ifndef __UTILS_H__
#define __UTILS_H__

#include <unistd.h>

#define BUF_SIZE 4096
#define DEBUG 0                               /* 1=on, 0=off */
#define PS1 "\033[31m[[daniel@shell]]\033[m " /* `man console_codes' */

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

/* Exit with error code and a message printed to stderr. */
void p_error(int, char *);

#endif /* __UTILS_H__ */
