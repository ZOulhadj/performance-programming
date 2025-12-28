SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)
EXE := $(BUILD_DIR)/md

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = icx
CFLAGS = -Wall -axBROADWELL -march=broadwell -mtune=broadwell -O3 -ipo -qoverride-limits

LDFLAGS := 
LDLIBS := -lm

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

-include $(OBJ:.o=.d)

clean:
	@$(RM) -rv $(BUILD_DIR)

