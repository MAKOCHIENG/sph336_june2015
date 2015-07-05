/*
 * File: main.c
 *
 * Copyright (c) karibe 2015, karfes@gmail.com
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 *
 */

#include "main.h"

int main(void){	
	//whether to blink LEDS
	blink=1;

	//initialize system
	SystemInit();

	//clear all interrupts and enable interrupts
	nvic->ICPR[2] |= 1 << (87 & 0x1F); //Clear Pending Interrupts
	nvic->ISER[2] |= 1 << (87 & 0x1F); //Enable Interrupts
	
	//initialize GPIO ports
	gpio_init();

	//Loop forever
	while(1)
	{
		
         blink_all();                          
                 
	}
}

/*
	brief  Silly delay
*/
void delay(void)
{
  volatile unsigned int i,j;

  for(i=0; i<2300; i++)
  {
	for(j=0; j<300; j++)
      __asm__("nop");
  }
}




void delay_long(void)
{
  volatile unsigned int a,s;

  for(a=0; a<2800; a++)
  {
	for(s=0; s<300; s++)
      __asm__("nop");
  }
}

void blink_all(void)
{

if(blink)

                  toggle_LED1(); delay(); toggle_LED2(); delay(); toggle_LED3();delay(); toggle_LED4();
                  delay_long();
                  toggle_LED1(); delay(); toggle_LED2(); delay(); toggle_LED3();delay(); toggle_LED4();
                  delay_long();
                  toggle_LED4(); delay(); toggle_LED3(); delay(); toggle_LED2();delay(); toggle_LED1();
                  delay_long();
                  toggle_LED4(); delay(); toggle_LED3(); delay(); toggle_LED2();delay(); toggle_LED1();
                  delay_long();

}

