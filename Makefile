# Make a simple shell.
SRC_DIR := src
BIN := $(SRC_DIR)/shell
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))
CFLAGS := -Wall -Wextra -std=c11 -pedantic -Werror \
	-D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L
VALGRIND_OPTS := --leak-check=full --show-leak-kinds=all

.PHONY: all test clean leak

all: $(OBJ_FILES)
	gcc $(CFLAGS) $(OBJ_FILES) -o $(BIN)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) $< -c -o $@

test:
	./$(BIN)

clean:
	@rm -f $(BIN) $(SRC_DIR)/*.o
	@echo 'Clean.'

leak:
	valgrind $(VALGRIND_OPTS) ./$(BIN)
