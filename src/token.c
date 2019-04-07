#include <string.h>

#include "token.h"

char *get_token(char **line)
{
    char *token;
    while ((token = strsep(line, DELIMS)) && (strcmp(token, "") == 0))
        ; /* return if token is NULL or anything but "" */

    /*
     * TODO: does token start with \' or \"? If it does, split off quote and
     * get tokens until a matching quote is reached. Then, return the entire
     * string which was enclosed in the quotes without the quotes but with all
     * white space.
     */

    return token;
}
