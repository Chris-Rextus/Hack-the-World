# Define variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TARGET = myprogram
SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) $(BUILD_DIR)/main.o

# Main target
all: $(BIN_DIR)/$(TARGET)

# Rule to build the target executable
$(BIN_DIR)/$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) $^ -o $@

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
    $(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.c
    $(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
    $(RM) -r $(BUILD_DIR)/* $(BIN_DIR)/*

# PHONY targets
.PHONY: all clean