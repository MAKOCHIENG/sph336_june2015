/*
 * adc1.c
 *
 */
 
#include "adc.h"


// Configure ADC1 16bit single ended mode
void ADC1_Init16b(void)
{
    SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK; //Gives clock to ADC1
	
    ADC1_CFG1 = (ADC_CFG1_MODE(3) | ADC_CFG1_ADIV(2)); //16bit mode
	ADC1_SC1A = ADC_SC1_ADCH(31); //disable module

        /* Configure ADC pins as ADC Inputs manually */
        
        /*In Kinetis the ADC pins are ADC inputs by default */          
}

uint16_t ADC1_Read16b(uint8_t channelNumber)
{
	ADC1_SC1A = channelNumber & ADC_SC1_ADCH_MASK;	                /* Write to ADCSC1 to start conversion */
	while ((ADC1_SC2 & 0x80)); 				  	/* Wait if the conversion is in progress */
	while (!(ADC1_SC1A & 0x80)); 					/* Wait until the conversion is complete */
	return ADC1_RA; 
}

/******************************************************************************
	AUTO CAL ROUTINE  
	Calibrates the ADC1_ automatically.
	Required after reset and before a conversion is initiated
	16-bit single-ended mode
******************************************************************************/
uint8_t ADC_CalSingle(ADC_MemMapPtr adcmap)
{

  unsigned int cal_var;

  ADC_SC2_REG(adcmap) &=  ~ADC_SC2_ADTRG_MASK ; // Enable Software Conversion Trigger for Calibration Process
  ADC_SC3_REG(adcmap) &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); // set single conversion, clear avgs bitfield for next writing
  ADC_SC3_REG(adcmap) |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(AVGS_32) );  // Turn averaging ON and set at max value ( 32 )


  ADC_SC3_REG(adcmap) |= ADC_SC3_CAL_MASK ;      // Start CAL
  while ( (ADC_SC1_REG(adcmap,A) & ADC_SC1_COCO_MASK ) == COCO_NOT ); // Wait calibration end
  	
  if ((ADC_SC3_REG(adcmap)& ADC_SC3_CALF_MASK) == CALF_FAIL ) return(1);    // Check for Calibration fail error and return

  // Calculate plus-side calibration for the overall conversion in single-ended mode.
  cal_var = 0x00;

  cal_var =  ADC_CLP0_REG(adcmap);
  cal_var += ADC_CLP1_REG(adcmap);
  cal_var += ADC_CLP2_REG(adcmap);
  cal_var += ADC_CLP3_REG(adcmap);
  cal_var += ADC_CLP4_REG(adcmap);
  cal_var += ADC_CLPS_REG(adcmap);

  cal_var = cal_var/2;
  cal_var |= 0x8000; // Set MSB

  ADC_PG_REG(adcmap) = ADC_PG_PG(cal_var);

  ADC_SC3_REG(adcmap) &= ~ADC_SC3_CAL_MASK ; /* Clear CAL bit */

  return(0);
}
