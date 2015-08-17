/*
 * adc1.h
 *
 */
 
#ifndef ADC1_H_
#define ADC1_H_

#include "MK60DZ10.h"

#define A                 0x0
#define B                 0x1

#define COCO_NOT          0x00

#define CALF_FAIL          ADC_SC3_CALF_MASK

#define AVGS_4             0x00
#define AVGS_8             0x01
#define AVGS_16            0x02
#define AVGS_32            0x03

//Configuration for single-ended mode
void ADC1_Init16b(void);
uint16_t ADC1_Read16b(uint8_t channelNumber);

//Calibration for single-ended mode
uint8_t ADC_CalSingle(ADC_MemMapPtr adcmap);

#endif /* ADC1_H_ */
