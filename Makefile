# Detect OS
OS := $(shell uname -s)
ifeq ($(OS), Linux)
    PLATFORM = LINUX
    EXE_EXT = 
    FILESYSTEM_LIB = -lstdc++fs
else
    PLATFORM = WINDOWS
    EXE_EXT = .exe
    FILESYSTEM_LIB = 
endif

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
LDFLAGS = $(FILESYSTEM_LIB)

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = .

# Output binary
TARGET = $(BIN_DIR)/market_data_merger$(EXE_EXT)

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/marketdatamerger.cpp \
       $(SRC_DIR)/safepriorityqueue.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Create necessary directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR) > /dev/null 2>&1)

# Default target
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR)/* $(TARGET)

# Windows-specific clean command
ifeq ($(PLATFORM), WINDOWS)
    clean:
	    del /Q $(subst /,\,$(OBJ_DIR)\*) $(subst /,\,$(TARGET))
endif

# Phony targets
.PHONY: all clean
