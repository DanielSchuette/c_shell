#ifndef __TOKEN_H__
#define __TOKEN_H__

#define  DELIMS             " \t\n\r"           /* valid token delimiters */

/*
 * Get the next non-empty token from `line'. Returns NULL if `line' is empty or
 * exhausted, i.e. no more tokens are available. Empty tokens (i.e. "") are
 * never returned to the caller.
 */
char *get_token(char **);

#endif /* __TOKEN_H__ */
