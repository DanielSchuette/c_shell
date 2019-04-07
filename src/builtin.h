#ifndef __BUILTIN_H__
#define __BUILTIN_H__

enum builtin {
    exit_builtin = 1,     /* builtin `exit' command returns from shell */
};

/*
 * Try to interpret a token as a builtin. If the token matches a builtin,
 * return -1, otherwise return 0.
 */
enum builtin builtin_action(const char *);

#endif  /* __BUILTIN_H__ */
