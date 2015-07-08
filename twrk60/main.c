/*
 * File: main.c
 * Copyright (c) 2015 David Muriuki
 * see the LICENCE file
 */
#include "main.h"
int main(void){		
	//temporally UART data holder
	uint8_t byte=0;
	//initialize system
	SystemInit();
      	//initialize UART5 with 8-N-1 settings, 57600 baudrate
	init_uart(UART5_BASE_PTR,periph_clk_khz,57600);
	//clear all interrupts and enable interrupts
	nvic->ICPR[2] |= 1 << (87 & 0x1F); //Clear Pending Interrupts
	nvic->ISER[2] |= 1 << (87 & 0x1F); //Enable Interrupts	
	//initialize GPIO ports
	gpio_init();
	//Loop forever
	while(1)
	{	//use polling method to echo back data when available
		if(data_available()){ 
			byte = uart_read();
			if(byte==0xD) puts((uint8_t *)"\r\n"); //send new line character
			else {
			uartsend((uint8_t)byte); //echo back the data
			display_tmp(byte);			
			}
		}else{}
	}
}
/*
	brief  Silly delay
*/
void delay(void)
{
  volatile unsigned int i,j;
  for(i=0; i<1000; i++)
  {	for(j=0; j<300; j++)        __asm__("nop");    }
}


void display_tmp(uint8_t data){ 
	char bit0, bit1, bit2, bit3; 
	uint32_t LEDS; 
	bit0 = data>>0&1;  bit1 = data>>1&1; bit2 = data>>2&1; 	bit3 = data>>3&1;
	LEDS = bit0<<11 | bit1<<28 | bit2<<29 | bit3<<10; //declaring the LEDS mask
  GPIOA->PDOR.word_reg = ~LEDS; 
/* Initialisation for error communication; Though not important for this level
.equ LED1, 1<<11	//declare LED1 mask
.equ LED2, 1<<28	//declare LED2 mask
.equ LED3, 1<<29	//declare LED3 mask
.equ LED4, 1<<10	//declare LED4 mask*/
	
	 
        //byte>>27(byte>>2&1)	

/*
Important comments
whether to blink LED2*/  //uint8_t blink=1;
/*a>>y&z===>a shifted by y bits and ANDED with z.
//>>read  <<write*/
}

