# Make a simple shell.
# strsep requires _DEFAULT_SOURCE, strndup requires _POSIX_C_SOURCE.
CPPFLAGS := -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L
CFLAGS := -Wall -Wextra -std=c11 -pedantic -Werror

.PHONY: all test clean

all: builtin.o cmd.o shell.o token.o utils.o
	gcc $(CPPFLAGS) $(CFLAGS) builtin.o cmd.o shell.o \
		token.o utils.o -o shell

builtin.o: builtin.c
	gcc $(CPPFLAGS) $(CFLAGS) builtin.c -c -o builtin.o

cmd.o: cmd.c
	gcc $(CPPFLAGS) $(CFLAGS) cmd.c -c -o cmd.o

shell.o: shell.c
	gcc $(CPPFLAGS) $(CFLAGS) shell.c -c -o shell.o

token.o: token.c
	gcc $(CPPFLAGS) $(CFLAGS) token.c -c -o token.o

utils.o: utils.c
	gcc $(CPPFLAGS) $(CFLAGS) utils.c -c -o utils.o

test:
	./shell

clean:
	@rm -f shell *.o
	@echo 'Clean.'

leak:
	valgrind --leak-check=full --show-leak-kinds=all ./shell
