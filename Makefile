# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Output
EXEC = cijs

# Source files
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/tokenizer.c $(SRC_DIR)/lexer.c $(SRC_DIR)/ast.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default target
all: $(EXEC)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the executable
$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o ${BUILD_DIR}/$(EXEC)

# Compile .c to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

# Run the interpreter
run: $(EXEC)
	./${BUILD_DIR}/$(EXEC)

.PHONY: all clean run
