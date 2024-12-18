# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/**/*.cc $(SRC_DIR)/*.cc)
OBJS := $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Output executable
TARGET := $(BIN_DIR)/gameboy-emulator

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean rules
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean