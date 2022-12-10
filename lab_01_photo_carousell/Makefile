SRC_DIR = src
BUILD_DIR = build/debug

CC = g++

OBJ_NAME = run 
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib

COMPILER_FLAGS = -std=c++11 -O0 -g
# Other flags:
# -Wall -Wextra -Werror

LINKER_PATHS = -lsdl2

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_PATHS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)
	
run: all
	./$(BUILD_DIR)/$(OBJ_NAME)
