#include "prv32.h"
#include "prv_i2c_master.h"

void INT0_handler(void)
{
    if (I2C0CON0bits.I2CIF)
    {
        I2C0_MasterFSM();
    }
    else
    {
        I2C0CON0 = 0;
    }
}