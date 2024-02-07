# Phony targets
.PHONY: all clean

LIB_DIR = ./lib
BUILD_DIR = ./build
SRC_DIR = ./src

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Library and object files
LIBRARY = libintarithmetic.a
OBJECTS = $(patsubst %.c, %.o, $(wildcard $(LIB_DIR)/*.c))
HEADERS = int_arithmetic.h

# Target for the main executable
TARGET = integer_math.out

# Default target
all: $(OBJECTS) $(LIBRARY) $(TARGET)
objects: $(OBJECTS)
lib: $(LIBRARY)

# Rule for compiling source files into object files
$(OBJECTS): $(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for creating the static library
$(LIBRARY): $(OBJECTS)
	ar rcs $(LIB_DIR)/$(LIBRARY) $(OBJECTS)
	ranlib $(LIB_DIR)/$(LIBRARY)

# Compiles the main program and links it with the static library
$(TARGET):
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRC_DIR)/main.c -L $(LIB_DIR) -lintarithmetic

# Clean up
clean:
	rm -f $(BUILD_DIR)/$(TARGET) $(OBJECTS) $(LIB_DIR)/$(LIBRARY)