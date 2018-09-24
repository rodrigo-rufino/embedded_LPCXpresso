/*
===============================================================================
 Name        : Project.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_adc.h"

#include "joystick.h"
#include "led7seg.h"
#include "oled.h"
#include "temp.h"
#include "rgb.h"

#define INCREMENT 1

// Inicializacao do Joystick
uint8_t joy = 0;
uint8_t level = 0;


static uint32_t msTicks = 0;
static uint8_t buf[10];

static void intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base)
{
    static const char* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
    int pos = 0;
    int tmpValue = value;

    // the buffer must not be null and at least have a length of 2 to handle one
    // digit and null-terminator
    if (pBuf == NULL || len < 2)
    {
        return;
    }

    // a valid base cannot be less than 2 or larger than 36
    // a base value of 2 means binary representation. A value of 1 would mean only zeros
    // a base larger than 36 can only be used if a larger alphabet were used.
    if (base < 2 || base > 36)
    {
        return;
    }

    // negative value
    if (value < 0)
    {
        tmpValue = -tmpValue;
        value    = -value;
        pBuf[pos++] = '-';
    }

    // calculate the required length of the buffer
    do {
        pos++;
        tmpValue /= base;
    } while(tmpValue > 0);


    if (pos > len)
    {
        // the len parameter is invalid.
        return;
    }

    pBuf[pos] = '\0';

    do {
        pBuf[--pos] = pAscii[value % base];
        value /= base;
    } while(value > 0);

    return;

}

void SysTick_Handler(void) {
    msTicks++;
}

static uint32_t getTicks(void)
{
    return msTicks;
}

static void init_ssp(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK;
	 * P0.8 - MISO
	 * P0.9 - MOSI
	 * P2.2 - SSEL - used as GPIO
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);

}

static void init_i2c(void)
{
	PINSEL_CFG_Type PinCfg;

	/* Initialize I2C2 pin connect */
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);

	// Initialize I2C peripheral
	I2C_Init(LPC_I2C2, 100000);

	/* Enable I2C1 operation */
	I2C_Cmd(LPC_I2C2, ENABLE);
}

static void init_adc(void)
{
	PINSEL_CFG_Type PinCfg;

	/*
	 * Init ADC pin connect
	 * AD0.0 on P0.23
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 23;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);

	/* Configuration for ADC :
	 * 	Frequency at 1Mhz
	 *  ADC channel 0, no Interrupt
	 */
	ADC_Init(LPC_ADC, 1000000);
	ADC_IntConfig(LPC_ADC,ADC_CHANNEL_0,DISABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);

}

static void joystickLed(){
	// Inicializzacao das cores
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
    joy = joystick_read();

    if ((joy & JOYSTICK_DOWN) != 0) {
		if (level > 0){
			level -= INCREMENT;
		} else if (level <= 0){
			level = 0;
		}
	}

	if ((joy & JOYSTICK_UP) != 0) {
		if (level<=10){
			level += INCREMENT;
		} else if (level > 10){
			level = 10;
		}
	}

	if (level < 3){
		r = RGB_RED;
		g = 0;
		b = 0;
		rgb_setLeds(r|g|b);
	} else if (level >=3 && level <7){
		r = 0;
		g = 0;
		b = RGB_BLUE;
		rgb_setLeds(r|g|b);
	} else {
		r = 0;
		g = RGB_GREEN;
		b = 0;
		rgb_setLeds(r|g|b);
	}
}

static int32_t temperatureLed(int32_t t){
	// Inicializzacao das cores
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	t = temp_read();

	if (t < 200){
		r = 0;
		g = 0;
		b = RGB_BLUE;

		rgb_setLeds(r|g|b);
	} else if (t >=200 && t <350){
		r = 0;
		g = RGB_GREEN;
		b = 0;

		rgb_setLeds(r|g|b);
	} else {
		r = RGB_RED;
		g = 0;
		b = 0;

		rgb_setLeds(r|g|b);
	}

	intToString(t, buf, 10, 10);
	oled_fillRect((1+9*6),1, 80, 8, OLED_COLOR_WHITE);
	oled_putString((1+9*6),1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

	return t;
}
int main (void) {
	// Inicializacao do estado do display
	// Valores da selecao:
	//	0 = Joystick
	// 	1 = Acc
	//	2 = Temperatura
    uint8_t ch[] = {'0', '1', '2'};
    uint8_t displayCount = 0;

    uint8_t btn1 = 0;

    int32_t t = 0;

	init_i2c();
	init_ssp();
	init_adc();

    rgb_init();
    joystick_init();
    led7seg_init();
    oled_init();

    temp_init(&getTicks);

    if (SysTick_Config(SystemCoreClock / 1000)) {
		while (1);  // Capture error
	}

    led7seg_setChar('8', FALSE);

    oled_clearScreen(OLED_COLOR_WHITE);

	oled_putString(1,1,  (uint8_t*)"Temp   : ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);

    while(1) {
        btn1 = ((GPIO_ReadValue(0) >> 4) & 0x01);

        if (btn1 == 0){
        	displayCount++;
        	if (displayCount == 3){
        		displayCount = 0;
        	}
        }

        if (displayCount == 0){
        	led7seg_setChar(ch[displayCount], FALSE);
        	joystickLed();

        } else if (displayCount == 1) {
        	led7seg_setChar(ch[displayCount], FALSE);
        	t = temperatureLed(t);

        } else if (displayCount == 2){
        	led7seg_setChar(ch[displayCount], FALSE);
        }

        oled_putPixel(50, 50, OLED_COLOR_BLACK);

        /* delay */
        Timer0_Wait(150);
    }

}
