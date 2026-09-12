#ifndef OEM_REUSE_H
#define OEM_REUSE_H

#include <stdbool.h>

/*
 * Återanvänd Application_OEM utan att ändra den.
 * I MPLAB: lägg OEM .c som existing files och sätt include till
 * Application_OEM/Top/Melacs/Application_OEM.X
 */

#define OEM_FW_DIR "../../Application_OEM/Top/Melacs/Application_OEM.X"

#define PLC_SD_MOUNT "/dev/sd/d1"
#define PLC_SD_DIR PLC_SD_MOUNT "/plc"
#define PLC_ST_PATH PLC_SD_DIR "/program.st"
#define PLC_BIN_PATH PLC_SD_DIR "/program.bin"
#define PLC_LOADED_PATH PLC_SD_DIR "/LOADED"

void plat_boot_check(void);
bool plc_loader_program_present(void);

#endif
