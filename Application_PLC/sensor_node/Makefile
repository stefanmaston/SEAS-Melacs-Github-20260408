CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Iinclude -I../shared
SRC = src/node_logic.c src/node_display.c ../shared/modbus_rtu.c tests/node_test.c
OUT = build/node_test

.PHONY: test clean

test: $(OUT)
	$(OUT)

$(OUT): $(SRC) include/board_pins.h include/node_logic.h include/node_display.h ../shared/modbus_rtu.h
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -rf build
