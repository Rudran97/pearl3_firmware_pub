#include "prv_gpio.h"
#include "prv_i2c.h"
#include "prv_serial.h"
#include "prv_interrupt.h"

int main()
{
	uint32_t addr = 1;
	uint32_t i2c_freq = I2C_FREQ(400000);

	Serial_Initialize(115200);
	ENABLE_GLOBAL_INTERRUPT();

	/* Configure I2C0 */
	I2C0CON1 = (24 << _I2C0CON1_TOT_POSN) | (_I2C0CON1_BRG_MASK & i2c_freq); // configure tot and baud rate
    I2C0CON2 = (1 << _I2C0CON2_SHTM_POSN) | (_I2C0CON2_SCLPIN_MASK & (6 << _I2C0CON2_SCLPIN_POSN)) | (_I2C0CON2_SDAPIN_MASK & (7 << _I2C0CON2_SDAPIN_POSN));

    /* Configuring Pins to I2C */
    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_I2C0, 6);
    GPIO_SetAlternateOutputPin(ALTERNATE_OUTPUT_I2C0, 7);

	printf("\nI2C Scanner ...\n\n");
	for(addr = 0; addr < 128; addr++)
	{
		I2C0TXbits.TXDATA = addr << 1;    // Load device Address.
		I2C0CON0bits.I2CEN = 1;           // Enable I2C0 module.
		
		I2C0CON0bits.SEN = 1;             // Send Start condition.
		while(!I2C0CON0bits.I2CDNF);      // Wait till done flag is set. Could also poll the I2CIF flag.
		I2C0CON0bits.CLRF = 1;            // Clear All flags.
		
		I2C0CON0bits.TXEN = 1;            // Send device Address. 
		while(!I2C0CON0bits.I2CDNF);      // Wait till done flag is set. Could also poll the I2CIF flag.
		I2C0CON0bits.CLRF = 1;            // Clear All flags.

		if ((addr != 0) && (addr % 16 == 0))
			printf("\n");
		if (!I2C0CON0bits.ACKSTAT)
		{
			// printf("Found device at address: %#x\n", addr);
			printf("\t%2x\t", addr);
		}
		else
		{
			printf("\t--\t", addr);
		}

		I2C0CON0bits.PEN = 1;        // Send Stop condition. 
		while(!I2C0CON0bits.I2CDNF); // Wait till done flag is set. Could also poll the I2CIF flag.
		I2C0CON0bits.CLRF = 1;       // Clear All flags.

		I2C0CON0bits.I2CEN = 0;      // Disable I2C0 module.
	}

	printf("\n");

	while(1);
}
