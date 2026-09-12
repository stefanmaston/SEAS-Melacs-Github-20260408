#include "plc_runtime.h"
#include "oem_reuse.h"

#include <stdio.h>

#ifdef __PIC32MX__
#include <fcntl.h>
#include <unistd.h>

static int sd_exists(const char *path)
{
    int fd = open(path, O_RDONLY, 0666);
    if (fd < 0) {
        return 0;
    }
    close(fd);
    return 1;
}

bool plc_loader_program_present(void)
{
    return sd_exists(PLC_ST_PATH) || sd_exists(PLC_BIN_PATH) || sd_exists(PLC_LOADED_PATH);
}

#else

#include <unistd.h>

bool plc_loader_program_present(void)
{
    return access("../plc/blink_dio.st", R_OK) == 0
        || access("../plc/program.st", R_OK) == 0
        || access("plc/blink_dio.st", R_OK) == 0;
}

#endif
