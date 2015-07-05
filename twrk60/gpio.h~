/*
 * gpio.h
 *
 *  Created on: Mar 2, 2015
 *      Author: karibe
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Mk60.h"
#include "main.h"

void gpio_init(void);
extern void toggle_LEDS(void);
extern void toggle_LED1(void);
extern void toggle_LED2(void);
extern void toggle_LED3(void);
extern void toggle_LED4(void);
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
	//GPIO port data direction Port A as output for LEDs (pin 11, 28, 29 and 10)
	GPIOA->PDDR.bit_reg.bit11 = out;
	GPIOA->PDDR.bit_reg.bit28 = out;
	GPIOA->PDDR.bit_reg.bit29 = out;
	GPIOA->PDDR.bit_reg.bit10 = out;
	//initialization: pns high means all LEDs off
	GPIOA->PDOR.bit_reg.bit11 = GPIOA->PDOR.bit_reg.bit28 =GPIOA->PDOR.bit_reg.bit29 = GPIOA->PDOR.bit_reg.bit10 = 1;
}


/*
	brief  Port A ISR Handler
 */
void PORTA_IRQHandler(void)
{
	PA->ISFR.word_reg = 0xFFFFFFFF; //clear Interrupt Status Register by writing ones in all bits --- why???
	toggle_LED1(); //toggle the first LED to indicate interrupt serviced
	toggle_LED2(); //toggle the second LED to indicate interrupt serviced
        toggle_LED3(); //toggle the third LED to indicate interrupt serviced
	toggle_LED4(); //toggle the fourth LED to indicate interrupt serviced
}



#endif /* GPIO_H_ */
