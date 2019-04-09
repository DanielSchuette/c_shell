#include <stdio.h>
#include <string.h>

#include "token.h"
#include "utils.h"

char *get_token(char **line)
{
    char *token;
    char quote;
    int llen;
    static char buf[BUF_SIZE];

    /* TODO: replace with a custom function, so DELIMS aren't lost */
    while ((token = strsep(line, DELIMS)) && (strcmp(token, "") == 0))
        ; /* loop until token is NULL or anything but "" */

    /* TODO: refactor into separate function */
    /* handle tokens that are enclosed in single or double quotes */
    if (token && (*token == '\'' || *token == '"')) {
        llen  = strlen(*line);
        quote = *token; /* save quote for later comparisons */

        /* check if only a single token is quoted without DELIMS */
        if (token[strlen(token) - 1] == quote) {
            token[strlen(token) - 1] = '\0'; /* strip quotes off */
            return &token[1];                /* and return token */
        } else if (llen == 0) {
            /* no more chars on line, but also no closing quote */
            fprintf(stderr, "Error: No closing quote `%c`.", quote);
            return NULL;
        }

        /*
         * If potentially multiple tokens are enclosed in quotes,
         * an empty buffer is used, the first token is copied into
         * it (without the leading quote) and all chars up to the
         * closing quote are added, too. Since the first separator
         * is lost to the tokenizing function `strsep', a whitespace
         * is added for now.
         */
        if (strlen(token) < BUF_SIZE - 1) {
            strncpy(buf, &token[1], BUF_SIZE);
            int _len      = strlen(buf);
            buf[_len]     = ' ';  /* ' ' was stripped off by */
            buf[_len + 1] = '\0'; /* strsep and is lost */
        }

        while (**line != quote && --llen > 0) {
            int _len = strlen(buf);
            if (_len < BUF_SIZE - 1) {
                buf[_len]     = **line;
                buf[_len + 1] = '\0';
            } else {
                fprintf(stderr, "Error: Quoted string too long.");
            }
            (*line)++;
        }

        if (llen == 0) {
            fprintf(stderr, "Error: No closing quote `%c`.", quote);
            return NULL; /* no valid token found */
        }
        token = buf;
    }

    return token;
}
