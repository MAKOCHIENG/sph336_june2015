/*
 * adc1.h
 *
 */
 
#ifndef ADC1_H_
#define ADC1_H_

#include "MK60DZ10.h"
#include "adc16.h"

//Configuration
void ADC1_Init16b(void);
uint16_t ADC1_Read16b(uint8_t channelNumber);

//Calibration
uint8_t ADC_Cal(ADC_MemMapPtr adcmap);

#endif /* ADC1_H_ */