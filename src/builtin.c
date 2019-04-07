#include <string.h>

#include "builtin.h"

enum builtin builtin_action(const char *token)
{
    if (strcmp(token, "exit") == 0)
        return exit_builtin;
    return 0;
}
