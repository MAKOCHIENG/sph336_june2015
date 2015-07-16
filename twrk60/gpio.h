/*
 * gpio.h
 *
 * Copyright (c) 2015 David Muriuki
 * see the LICENCE file
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Mk60.h"
#include "main.h"

void gpio_init(void);
void display(uint8_t byte);

extern void toggle_LEDS(void);
extern void toggle_LED1(void);
extern void toggle_LED2(void);
extern void toggle_LED3(void);
extern void toggle_LED4(void);
extern void puts(uint8_t *s);
extern void SystemInit(void);
/*
	brief PORTA initialization
*/
void gpio_init(void)
{
	//PTA19 as a button input
	PA->PCR[19].mux = 0x01; //PortA pin 19 as GPIO
	PA->PCR[19].irqc = 0xA; //Interrupt on falling edge
	PA->PCR[19].pe = 0x01; //pull-up enable
	PA->PCR[19].ps = 0x01; //select internal pull-up resistor
	//PortA pins 10, 11, 28 and 29 as alt1=GPIO
	PA->PCR[10].mux = 0x01;
	PA->PCR[11].mux = 0x01;
	PA->PCR[28].mux = 0x01;
	PA->PCR[29].mux = 0x01;
	//PTE8 and PTE9 as UART5
	PE->PCR[8].mux = 0x0;	//clear default function
	PE->PCR[9].mux = 0x0;	//clear default function
	PE->PCR[8].mux = 0x3;	//alt3 = UART5_TX
	PE->PCR[9].mux = 0x3; 	//alt3 = UART5_RX
	//GPIO port data direction Port A as output for LEDs (pin 11, 28, 29 and 10), Port E UART5(PTE8 TX, PTE9 RX)
	GPIOA->PDDR.bit_reg.bit11 = out;
	GPIOA->PDDR.bit_reg.bit28 = out;
	GPIOA->PDDR.bit_reg.bit29 = out;
	GPIOA->PDDR.bit_reg.bit10 = out;
	GPIOE->PDDR.bit_reg.bit8 = out; //UART5_TX is an output
	//No need to configure GPIO pins as an input, by default all pins are inputs
	//GPIOA->PDDR.bit_reg.bit19 = IN;
	//GPIOE->PDDR.bit_reg.bit9 = IN //UART5_RX is an input
	GPIOA->PDOR.bit_reg.bit10 = GPIOA->PDOR.bit_reg.bit29 = GPIOA->PDOR.bit_reg.bit28 = GPIOA->PDOR.bit_reg.bit11 = 0x01;
}


/*
	brief  Port A ISR Handler
 */
void PORTA_IRQHandler(void)
{
	PA->ISFR.word_reg = 0xFFFFFFFF; //clear Interrupt Status Register by writing ones in all bits --- why???
	toggle_LED2(); //toggle the second LED to indicate interrupt serviced
}

void display(uint8_t byte){
	GPIOA->PDOR.word_reg = ~(uint32_t)((byte>>0&1)<<11 | (byte>>1&1)<<28 | (byte>>2&1)<<29 | (byte>>3&1)<<10);
}

#endif /* GPIO_H_ */



