#include "prv_spi_host.h"
#include "prv_serial.h"
#include "prv_timer0.h"
#include "prv_interrupt.h"

#define SCLK_PIN 0
#define SDO_PIN 1
#define SDI_PIN 4
#define SS_PIN 5

char message[] = "Hello World!!!";

int main()
{
    SysTick_Init(TIMERms_const);
    Serial_Initialize(115200);
    ENABLE_GLOBAL_INTERRUPT();

    char read_buff[sizeof(message)];

    SPI_CONFIG_t spi_config = {
        .mode = SPI_MODE3,
        .baud_rate = SPI_FREQ(1000000),
        .sclkPin = SCLK_PIN,
        .sdoPin = SDO_PIN,
        .sdiPin = SDI_PIN,
        .ssPin = SS_PIN,
    };

    SPI_Initialize(&spi_config);
    delay(1000);

    // SPI_writeNBytes(message, sizeof(message) - 1, &spi_config);
    // SPI_readNBytes(read_buff, sizeof(read_buff) - 1, &spi_config);

    // SPI_write1Byte(0xA0, &spi_config);
    SPI_transmitReceiveNBytes(message, read_buff, sizeof(message)-1, &spi_config);
    printf("%s %s", read_buff, message);
    while(1);
}