#include "stm32f10x.h"

#include "ADC.h"
#include "delay.h"
#include "encoder.h"
#include "UART.h"
#include "PWM.h"

uint16_t adcValue;
uint32_t temp;
extern float RPM;
 

int main(void)
{
	ADC_Config();
	encoder_Config();
	Delay_Systick();
	UART_Config();
	PWM_Config();

	while(1)
	{
		ADC_Read();
		readEncoderSpeed();
		temp = (float)adcValue / 4096 * 1000;
		TIM2->CCR1 = (uint32_t)temp;
		
		printString(intToStringStatic((int)RPM));
		delay_ms(500);
	}

}
