CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Iinclude -pthread
SRC = src/plc_runtime.c src/rtc.c src/logger.c src/log_history.c src/register_image.c src/modbus_pdu.c src/modbus_tcp.c src/plat_host.c src/host_main.c
OUT = build/plc_host_test

XC32 ?= /Applications/microchip/xc32/v6.00/bin/xc32-gcc
XC32_HEX ?= /Applications/microchip/xc32/v6.00/bin/xc32-bin2hex
XC32_CFLAGS = -mprocessor=32MX795F512L -mdfp=/Applications/microchip/mplabx/v6.35/packs/Microchip/PIC32MX_DFP/1.7.380 -O1 -std=gnu99 -Wall -Iinclude -ffunction-sections -fdata-sections
PIC32_SRC = src/plc_runtime.c src/rtc.c src/logger.c src/log_history.c src/register_image.c src/modbus_pdu.c \
	src/plat_pic32.c src/pic32_config.c src/pic32_board.c src/pic32_spi.c src/pic32_io.c \
	src/pic32_sd.c src/pic32_enc.c src/pic32_net.c src/pic32_main.c
PIC32_ELF = build/melacs_pic32.elf

.PHONY: host-test pic32 clean

host-test: $(OUT)
	$(OUT)

PACK_C = build/sd_pack_data.c
PACK_IN = tools/pack_sd.py ../sd_pack/README.txt ../sd_pack/project.json \
	../sd_pack/pous/programs/main.st ../sd_pack/devices/configuration.json \
	../sd_pack/devices/pin-mapping.json ../sd_pack/devices/remote/Melacs.json \
	../rock5b/openplc/modbus_master.json ../shared/register_map.json

$(PACK_C): $(PACK_IN)
	mkdir -p build
	python3 tools/pack_sd.py $@

$(OUT): $(SRC) $(PACK_C) include/plc_runtime.h include/rtc.h include/logger.h include/register_image.h include/modbus_tcp.h include/modbus_pdu.h include/plat_host.h include/sd_pack.h
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(SRC) $(PACK_C)

pic32: $(PIC32_ELF)
	$(XC32_HEX) $(PIC32_ELF)

$(PIC32_ELF): $(PIC32_SRC) $(PACK_C) include/pin_map.h include/plc_runtime.h include/rtc.h include/logger.h include/register_image.h include/modbus_pdu.h include/sd_pack.h
	mkdir -p build
	$(XC32) $(XC32_CFLAGS) -Wl,--gc-sections -o $@ $(PIC32_SRC) $(PACK_C)

clean:
	rm -rf build
