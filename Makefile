CC := gcc

CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -Ilib/include
CFLAGS += -D_POSIX_C_SOURCE=200809L
LDFLAGS :=

BUILD_DIR := build
BIN_DIR := bin

LIB_SRC := $(wildcard lib/src/*.c)
LIB_OBJ := $(patsubst lib/src/%.c,$(BUILD_DIR)/lib/%.o,$(LIB_SRC))

APPS := part_a part_bc part_d part_e

PART_A_SRC := part_a/src/main.c
PART_BC_SRC := part_bc/src/main.c
PART_D_SRC := part_d/src/main.c
PART_E_SRC := part_e/src/main.c

PART_A_OBJ := $(BUILD_DIR)/part_a/main.o
PART_BC_OBJ := $(BUILD_DIR)/part_bc/main.o
PART_D_OBJ := $(BUILD_DIR)/part_d/main.o
PART_E_OBJ := $(BUILD_DIR)/part_e/main.o

.PHONY: all clean directories $(APPS)

all: $(APPS)

part_a: directories $(BIN_DIR)/part_a

part_bc: directories $(BIN_DIR)/part_bc

part_d: directories $(BIN_DIR)/part_d

part_e: directories $(BIN_DIR)/part_e

directories:
	mkdir -p $(BUILD_DIR)/lib
	mkdir -p $(BUILD_DIR)/part_a
	mkdir -p $(BUILD_DIR)/part_bc
	mkdir -p $(BUILD_DIR)/part_d
	mkdir -p $(BUILD_DIR)/part_e
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)/lib/%.o: lib/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

define BUILD_APP
$(BIN_DIR)/$1: $(BUILD_DIR)/$1/main.o $(LIB_OBJ)
	$(CC) $$^ -o $$@ $(LDFLAGS) $(2)

$(BUILD_DIR)/$1/%.o: $1/src/%.c
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

$(eval $(call BUILD_APP,part_a,))
$(eval $(call BUILD_APP,part_bc,))
$(eval $(call BUILD_APP,part_d,-pthread))
$(eval $(call BUILD_APP,part_e,))

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
