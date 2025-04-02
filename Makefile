CXX := clang
CXXFLAGS := -Iincludes
SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/main

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all build run clean

all: build run

build: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	@$(TARGET)

clean:
	@rm -rf $(BUILD_DIR)