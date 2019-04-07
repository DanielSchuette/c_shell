#include <string.h>

#include "token.h"

char *get_token(char **line)
{
    char *token;
    while ((token = strsep(line, DELIMS)) &&
            (strcmp(token, "") == 0)); /* return if token is NULL or not "" */
    return token;
}
