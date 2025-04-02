C := clang
CFLAGS := -Iincludes

BUILD_DIR := build

SRC_DIR := src
SRC_TARGET := $(BUILD_DIR)/main

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

.PHONY: all build run clean

all: build run

build: $(SRC_TARGET)

$(SRC_TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(C) $(CFLAGS) $(OBJS) -o $(SRC_TARGET)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(C) $(CFLAGS) -c $< -o $@

run: $(SRC_TARGET)
	@$(SRC_TARGET)

clean:
	@rm -rf $(BUILD_DIR)