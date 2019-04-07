# Make a simple shell.
# strsep requires _DEFAULT_SOURCE, strndup requires _POSIX_C_SOURCE.
SRC_DIR := src
BIN := $(SRC_DIR)/shell
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))
CPPFLAGS := -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L
CFLAGS := -Wall -Wextra -std=c11 -pedantic -Werror
VALGRIND_OPTS := --leak-check=full --show-leak-kinds=all

.PHONY: all test clean

all: $(OBJ_FILES)
	gcc $(CPPFLAGS) $(CFLAGS) $(OBJ_FILES) -o $(BIN)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CPPFLAGS) $(CFLAGS) $< -c -o $@

test:
	./$(BIN)

clean:
	@rm -f $(BIN) $(SRC_DIR)/*.o
	@echo 'Clean.'

leak:
	valgrind $(VALGRIND_OPTS) ./$(BIN)
