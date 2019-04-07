/* Utility functions. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

int prmpt(const char *ps1)
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
