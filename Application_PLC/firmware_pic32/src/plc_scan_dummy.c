#include "plc_runtime.h"

/*
 * Ersätts av MatIEC-genererad C när ett riktigt program läggs in.
 * Dummy: spegla DIO0 -> DIO4 så host-test och dashboard kan visa en scan.
 */
void plc_scan(PlcInputs *in, PlcOutputs *out)
{
    out->dio_out[0] = in->dio_in[0];
    out->dio_out[1] = in->dio_in[1];
    out->dio_out[2] = false;
    out->dio_out[3] = false;
    out->burner_fan_sp = 0;
    out->radiator_fan_sp = 0;
    out->valve_pos = 0;
}
