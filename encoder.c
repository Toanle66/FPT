#include "encoder.h"

uint16_t encoderValue;
uint16_t previousValue = 0;
uint16_t speed;

float RPM;

void GPIO_Config(void)
{
    // C?u hình GPIOA->CRH cho các chân PA8 và PA9 làm input v?i pull-up
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // B?t clock cho Port A

    GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);  // Xóa c?u hình hi?n t?i cho PA8
    GPIOA->CRH |= GPIO_CRH_CNF8_1;  // PA8 ? ch? d? input v?i pull-up/pull-down
    GPIOA->ODR |= GPIO_ODR_ODR8;    // Kéo lên cho PA8

    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);  // Xóa c?u hình hi?n t?i cho PA9
    GPIOA->CRH |= GPIO_CRH_CNF9_1;  // PA9 ? ch? d? input v?i pull-up/pull-down
    GPIOA->ODR |= GPIO_ODR_ODR9;    // Kéo lên cho PA9
}

void Timer_Config(void)
{
    // C?u hình Timer 1 ? ch? d? encoder mode
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // B?t clock cho Timer 1

    TIM1->ARR = 0xFFFF;  // Ð?t giá tr? t? d?ng reload (ARR)
    TIM1->PSC = 0;       // Không chia t?n s? clock
    TIM1->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;  // C?u hình encoder mode 3 (d?m c? hai c?nh xung)
    TIM1->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;  // Kích ho?t capture trên c? hai kênh 1 và 2
    TIM1->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);  // Không d?o pha

    TIM1->CR1 |= TIM_CR1_CEN;  // Kích ho?t Timer 1
}

void encoder_Config(void)
{
    GPIO_Config();
    Timer_Config();
}

void readEncoderSpeed(void) {
    encoderValue = TIM1->CNT;  // Ð?c giá tr? counter hi?n t?i
    speed = encoderValue - previousValue;  // Tính s? xung trong kho?ng th?i gian
    previousValue = encoderValue;  // C?p nh?t giá tr? tru?c dó

    RPM = (speed * 60.0f) / (ENCODER_PULSES_PER_REVOLUTION * TIME_INTERVAL);

    // Reset counter n?u c?n
    if (encoderValue > 0xFFFF) {
        TIM1->CNT = 0;
    }
}

