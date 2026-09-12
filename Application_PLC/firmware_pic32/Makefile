CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Iinclude
SRC = src/plc_runtime.c src/plc_scan_dummy.c src/plat_host.c src/host_main.c
OUT = build/plc_host_test

.PHONY: host-test clean

host-test: $(OUT)
	$(OUT)

$(OUT): $(SRC) include/plc_runtime.h
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -rf build
