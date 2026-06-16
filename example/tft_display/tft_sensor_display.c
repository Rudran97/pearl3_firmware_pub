#include "prv_i2c.h"
#include "prv_plic.h"
#include "prv_timer0.h"
#include "hw.h"
#include "ST7735_TFT.h"
#include "FreeMonoBold9pt7b.h"
#include "bh1750.h"
#include "printf.h"
#include "prv_csr.h"

SPI_CONFIG_t tft_spi_config = {
	.mode = SPI_MODE0,
	.baud_rate = SPI_FREQ(5000000),
	.sclkPin = PIN_SPI_SCLK,
	.sdoPin = PIN_SPI_SDO,
	.sdiPin = PIN_SPI_SDI,
	.ssPin = PIN_TFT_CS
};

void light_sensor_init(void)
{
    uint32_t i2c_freq = I2C_FREQ(400000);
    I2C0_Initialize(i2c_freq, 7, 6);

    PLIC_INTERRUPT_CONFIG_t i2c_int_config = {
        .attach_interrupt_module = ATTACH_I2C0DNF_TO_INTERRUPT,
        .set_priority = INTERRUPT_PRIORITY_1};

    Set_Interrupt0(&i2c_int_config);

    BH1750_begin(BH1750_I2CADDR, CONTINUOUS_LOW_RES_MODE);
}

static void init(void)
{
	DDRB &= ~ ((1 << PIN_TFT_RST) | (1 << PIN_TFT_DC));

	SysTick_Init(TIMERms_const);
    ENABLE_GLOBAL_INTERRUPT();

    light_sensor_init();
    SPI_Initialize(&tft_spi_config);
    TFT_BlackTab_Initialize();
}

void TFT_drawText(uint8_t x, uint8_t y, uint16_t color, uint16_t bg, uint8_t size, const char *format, ...)
{
	va_list va;
	va_start(va, format);
	char buffer[40];
	vsnprintf(buffer, 20, format, va);
	va_end(va);
	drawText(x, y, buffer, color, bg, size);
}

int main()
{
    // SET_INTERRUPT_VECTOR_MODE(INTERRUPT_MODE_DIRECT);
    // INTCONbits.EXTI = 1; // use external interrupts instead of fast interrupts
    // csr_set_bits_mie(MIE_MEI_BIT_MASK);

    init();
    setTextWrap(true);
    fillScreen(ST7735_BLACK);
	
    setFont(&FreeMonoBold9pt7b);
    setRotation(0);
    
    fillScreen(ST7735_BLUE);
    fillRoundRect(4,  4,120,48,10,ST7735_WHITE);
    drawText(10, 36, "Stop Watch", ST7735_BLACK, ST7735_WHITE, 1);

    uint32_t s = 0, m = 0, h = 0;

    while(true)
    {
        /* light sensor status */
        fillRoundRect(4,  56,120,48,10,ST7735_WHITE);

        float level = BH1750_readLightLevel();
        if (level > 500)
            drawText(10, 88, "BRIGHT", ST7735_BLACK, ST7735_WHITE, 1);
        else
            drawText(10, 84, "DIM", ST7735_BLACK, ST7735_WHITE, 1);

        s += 1;
        if (s == 60)
        {
            s = 0;
            m += 1;
        }
        if (m == 60)
        {
            m = 0;
            h += 1;
        }
        fillRoundRect(4,108,120,48,10,ST7735_WHITE);
        TFT_drawText(10,140,ST7735_BLACK,ST7735_WHITE,1, "%02d:%02d:%02d", h, m, s);
        delay(950);
        LED_ToggleOutput(0);
    }
}