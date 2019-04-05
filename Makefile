# Make a simple shell.
# strsep requires _DEFAULT_SOURCE, strndup requires _POSIX_C_SOURCE.
CPPFLAGS := -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L
CFLAGS := -Wall -Wextra -std=c11 -pedantic -Werror

.PHONY: all test clean

all: shell.o utils.o
	gcc $(CPPFLAGS) $(CFLAGS) shell.o utils.o -o shell

shell.o: shell.c
	gcc $(CPPFLAGS) $(CFLAGS) shell.c -c -o shell.o

utils.o: utils.c
	gcc $(CPPFLAGS) $(CFLAGS) utils.c -c -o utils.o

test:
	./shell

clean:
	@rm -f shell *.o
	@echo 'Clean.'
