#include "ADC.h"


void ADC_Config(void)
{
	/* Config GPIO */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRL &= ~GPIO_CRL_CNF6;
	GPIOA->CRL &= ~GPIO_CRL_MODE6;
	
	/* Config ADC */
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // ennable clock ADC
	RCC->CFGR &= ~RCC_CFGR_ADCPRE; // clear bit
	RCC->CFGR |= RCC_CFGR_ADCPRE_0; // set bit
	
	ADC1->CR1 &= ~ADC_CR1_DUALMOD;
	ADC1->CR1 &= ~ADC_CR1_SCAN; // disable scan mode
	ADC1->CR2 |= ADC_CR2_CONT; // 
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->CR2 |= ADC_CR2_EXTSEL;
	ADC1->SQR1 &= ~ADC_SQR1_L; 
	
	ADC1->SQR3 = 6; // set gia tri no set thanh ghi
	ADC1->SMPR2 |= ADC_SMPR2_SMP6;
	
	ADC1->CR2 |= ADC_CR2_ADON;
	__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
	ADC1->CR2 |= ADC_CR2_ADON;
	
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while((ADC1->CR2 & ADC_CR2_RSTCAL) == ADC_CR2_RSTCAL); // waiting bit RSTCAL clear
	ADC1->CR2 |= ADC_CR2_CAL;
	while((ADC1->CR2 & ADC_CR2_CAL) == ADC_CR2_CAL);  

	ADC1->CR2 |= ADC_CR2_SWSTART;
}

void ADC_Read(void)
{
	while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC);
	adcValue = ADC1->DR;
	ADC1->SR &= ~ADC_SR_EOC;
	
}
