#include "encoder.h"

uint16_t encoderValue;
uint16_t previousValue = 0;
uint16_t speed;

float RPM;

void GPIO_Config(void)
{
    // C?u h�nh GPIOA->CRH cho c�c ch�n PA8 v� PA9 l�m input v?i pull-up
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // B?t clock cho Port A

    GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);  // X�a c?u h�nh hi?n t?i cho PA8
    GPIOA->CRH |= GPIO_CRH_CNF8_1;  // PA8 ? ch? d? input v?i pull-up/pull-down
    GPIOA->ODR |= GPIO_ODR_ODR8;    // K�o l�n cho PA8

    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);  // X�a c?u h�nh hi?n t?i cho PA9
    GPIOA->CRH |= GPIO_CRH_CNF9_1;  // PA9 ? ch? d? input v?i pull-up/pull-down
    GPIOA->ODR |= GPIO_ODR_ODR9;    // K�o l�n cho PA9
}

void Timer_Config(void)
{
    // C?u h�nh Timer 1 ? ch? d? encoder mode
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // B?t clock cho Timer 1

    TIM1->ARR = 0xFFFF;  // �?t gi� tr? t? d?ng reload (ARR)
    TIM1->PSC = 0;       // Kh�ng chia t?n s? clock
    TIM1->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;  // C?u h�nh encoder mode 3 (d?m c? hai c?nh xung)
    TIM1->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;  // K�ch ho?t capture tr�n c? hai k�nh 1 v� 2
    TIM1->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);  // Kh�ng d?o pha

    TIM1->CR1 |= TIM_CR1_CEN;  // K�ch ho?t Timer 1
}

void encoder_Config(void)
{
    GPIO_Config();
    Timer_Config();
}

void readEncoderSpeed(void) {
    encoderValue = TIM1->CNT;  // �?c gi� tr? counter hi?n t?i
    speed = encoderValue - previousValue;  // T�nh s? xung trong kho?ng th?i gian
    previousValue = encoderValue;  // C?p nh?t gi� tr? tru?c d�

    RPM = (speed * 60.0f) / (ENCODER_PULSES_PER_REVOLUTION * TIME_INTERVAL);

    // Reset counter n?u c?n
    if (encoderValue > 0xFFFF) {
        TIM1->CNT = 0;
    }
}

