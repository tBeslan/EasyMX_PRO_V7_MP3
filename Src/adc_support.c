/*
 * adc_support.c
 *
 *  Created on: 14 окт. 2017 г.
 *      Author: beslan
 */



#include "adc_support.h"

#define ADCCONVERTEDVALUES_BUFFER_SIZE ((uint32_t)    2)   /* Size of array containing ADC converted values: set to ADC sequencer number of ranks converted, to have a rank in each address */

/* Variable containing ADC conversions results */
__IO uint16_t   aADCxConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE];

void ADC_Start(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)aADCxConvertedValues, ADCCONVERTEDVALUES_BUFFER_SIZE);
}

uint32_t getADC0(void)
{
	return aADCxConvertedValues[0];
}

uint32_t getADC1(void)
{

	return aADCxConvertedValues[1];
}


/**
  * @brief  Conversion complete callback in non blocking mode
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion
  *         and get conversion result. You can add your own implementation.
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{

  /* Report to main program that ADC sequencer has reached its end */

}

