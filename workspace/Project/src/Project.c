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
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_ssp.h"

#include "joystick.h"
#include "rgb.h"
#include "led7seg.h"
#include "rotary.h"
#include <cr_section_macros.h>

#define INCREMENT 1

// Inicializacao do Joystick
uint8_t joy = 0;

uint8_t level = 0;

static void joystickLevel(){
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
		if (level<=100){
			level += INCREMENT;
		} else if (level > 100){
			level = 100;
		}
	}

	if (level < 30){
		r = RGB_RED;
		g = 0;
		b = 0;
		rgb_setLeds(r|g|b);
	} else if (level >=30 && level <70){
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

int main (void) {
	// Inicializacao do estado do display
	// Valores da selecao:
	//	0 = Joystick
	// 	1 = Acc
	//	2 = Temperatura
    uint8_t ch[] = {'0', '1', '2'};
    uint8_t displayCount = 0;

    uint8_t btn1 = 0;

    // Configuracao do display
	PINSEL_CFG_Type PinCfg;
	SSP_CFG_Type SSP_ConfigStruct;

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

    rgb_init();
    joystick_init();
    led7seg_init();

    led7seg_setChar('8', FALSE);

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
        	joystickLevel();
        } else if (displayCount == 1) {
        	led7seg_setChar(ch[displayCount], FALSE);
        } else if (displayCount == 2){
        	led7seg_setChar(ch[displayCount], FALSE);
        }



        /* delay */
        Timer0_Wait(150);
    }

}