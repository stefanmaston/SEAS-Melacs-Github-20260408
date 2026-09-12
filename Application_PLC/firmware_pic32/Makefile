CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Iinclude
SRC = \
	src/plc_runtime.c \
	src/plc_iec_glue.c \
	src/plc_scan.c \
	src/plc_loader.c \
	src/plat_host.c \
	src/host_main.c \
	plc_generated/config_blink.c
OUT = build/plc_host_test

.PHONY: host-test clean

host-test: $(OUT)
	$(OUT)

$(OUT): $(SRC) include/plc_runtime.h include/plc_iec.h include/oem_reuse.h
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -rf build
