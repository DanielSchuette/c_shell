#include <string.h>

#include "builtin.h"
#include "cmd.h"

enum builtin builtin_action(const char *token)
{
    if (strcmp(token, "exit") == 0) return exit_builtin;
    if (strcmp(token, "cd") == 0) return cd_builtin;
    return 0;
}
