#include "plc_runtime.h"

int main(void)
{
    int i;

    plc_runtime_init();
    for (i = 0; i < 8; i++) {
        plc_runtime_tick();
    }
    return plc_status()->log_count == 8 ? 0 : 1;
}
