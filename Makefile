CPP := g++
CPPFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wunused-variable -Wuninitialized -Wconversion -Wdeprecated-declarations -Wformat -Wswitch -Wvla -Wunreachable-code
INCLUDES := -Iinclude -Isrc
LDFLAGS := -lcurl

BUILD_DIR := build

SRC_DIR := src
TARGET := $(BUILD_DIR)/main

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

TEST_DIR := test
TEST_TARGET := $(BUILD_DIR)/testProgram

TEST_SRCS := $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJS := $(filter-out $(BUILD_DIR)/src/main.o, $(OBJS) $(TEST_SRCS:%.cpp=$(BUILD_DIR)/%.o))

.PHONY: all build run clean test

all: build run

build: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_TARGET)
	@$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_TARGET)

run: build
	@$(TARGET)

clean:
	@rm -rf $(BUILD_DIR)
