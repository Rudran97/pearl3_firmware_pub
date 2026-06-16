// --------------------------------------------------------------------------
// Demo program for the ST7735-library
//
// Author: Bernhard Bablok
//
// The code is based on work from Gavin Lyons, see
// https://github.com/gavinlyonsrepo/pic_16F18346_projects
//
// https://github.com/bablokb/pic-st7735
// --------------------------------------------------------------------------

#include "hw.h"
#include "tst_funcs.h"
#include "ST7735_TFT.h"

////////////////////////////////////////////////////////////////////////
// Intialize registers

SPI_CONFIG_t tft_spi_config = {
	.mode = SPI_MODE0,
	.baud_rate = SPI_FREQ(5000000),
	.sclkPin = PIN_SPI_SCLK,
	.sdoPin = PIN_SPI_SDO,
	.sdiPin = PIN_SPI_SDI,
	.ssPin = PIN_TFT_CS
};

static void init(void)
{
	DDRB &= ~ ((1 << PIN_TFT_RST) | (1 << PIN_TFT_DC));
	SysTick_Init(23999);
}

// --- main program   --------------------------------------------------------

int main()
{
	init();
	SPI_Initialize(&tft_spi_config);

#ifdef TFT_ENABLE_BLACK
	TFT_BlackTab_Initialize();
#elif defined(TFT_ENABLE_GREEN)
	TFT_GreenTab_Initialize();
#elif defined(TFT_ENABLE_RED)
	TFT_RedTab_Initialize();
#elif defined(TFT_ENABLE_GENERIC)
	TFT_ST7735B_Initialize();
#endif
	setTextWrap(true);
	TEST_DELAY1();
	fillScreen(ST7735_BLACK);

#if defined(ENABLE_TEST1)
	Test1();
#endif
#if defined(ENABLE_TEST1A)
	Test1A();
#endif
#if defined(ENABLE_TEST2)
	Test2();
#endif
#if defined(ENABLE_TEST3)
	Test3();
#endif
#if defined(ENABLE_TEST4)
	Test4();
#endif
#if defined(ENABLE_TEST5)
	Test5();
#endif
#if defined(ENABLE_TEST6)
	Test6();
#endif
#if defined(ENABLE_TEST7)
	Test7();
#endif
#if defined(ENABLE_TEST8)
	Test8();
#endif
#if defined(ENABLE_TEST9)
	Test9();
#endif
#if defined(ENABLE_TEST9A)
	Test9A();
#endif

#if defined(TFT_ENABLE_TEXT)
#if defined(ENABLE_TESTR) && defined(TFT_ENABLE_ROTATE)
	for (size_t i = 0; i < 4; i++)
	{
		setRotation(i);
#endif
		fillScreen(ST7735_BLACK);
		drawText(10, 10, "Test over!", ST7735_WHITE, ST7735_BLACK, 1);
		drawFastHLine(0, 0, 80, ST7735_CYAN);
		drawFastHLine(0, 25, 80, ST7735_CYAN);
		drawFastVLine(0, 0, 25, ST7735_CYAN);
		drawFastVLine(80, 0, 25, ST7735_CYAN);
#if defined(ENABLE_TESTR) && defined(TFT_ENABLE_ROTATE)
		TEST_DELAY1();
	}
#endif
#endif
	while (1)
		LATD = 10;
}
