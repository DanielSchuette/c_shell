#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "builtin.h"
#include "cmd.h"
#include "utils.h"

enum builtin builtin_action(const char *token)
{
    if (strcmp(token, "exit") == 0) return exit_builtin;
    if (strcmp(token, "cd") == 0) return cd_builtin;
    return 0;
}

int __cd(const char *path)
{
    int err;
    if ((err = chdir(path)) < 0)
        fprintf(stderr, "Error: %s\n", strerror(errno));
    return err;
}
