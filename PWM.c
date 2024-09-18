#include "PWM.h"

void PWM_Timer2_Reister(void)
{
	// enable clock cho timer2
	RCC->APB1ENR |= 0x01;
	// dat gia tri reload, no tuong duong voi chon tan so, chon do rong xung 
	TIM2->ARR = 1000-1;
	// chia clock, set tgian cho 1 tick
	TIM2->PSC = 720-1;
	// chon pwm mode 1 (xung thuan) : dat bit [6:4] = 110
	TIM2->CCMR1 = 0x60;
	/* dat do rong muc cao/thap mong muon, CCR1 la dung cho chan PA0, max la 4 chan 
	tuong duong CCR2,3,4 dieu khien cho PB0, PC0, PD0 */
	TIM2->CCR1 = 1000/5;
	/* bit cc1e trong thanh ghi chon input/output cho dau phat
	con bit cc1p trong thanh ghi chon xem muc mong muon la muc cao hay muc thap (0:cao, 1:thap) */
	TIM2->CCER = 0x01;
	// enable counter
	TIM2->CR1 = 0x01;
	// enable bit UDIS de cap nhap su kien, vi ben tren set tran roi ben cai nay khong can lam
	//TIM2->EGR = 0x01;
}

void ConfigAlternate(void)
{
	RCC->APB2ENR |= 0x04;
	GPIOA->CRL &= ~0x0F;
	GPIOA->CRL |= 0x0B;
}




void PWM_Config(void)
{
	PWM_Timer2_Reister();
	ConfigAlternate();
}
