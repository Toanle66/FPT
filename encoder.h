#include "stm32f10x.h"

#define ENCODER_PULSES_PER_REVOLUTION 11
#define TIME_INTERVAL 1  // Th?i gian do (1 giây)

void encoder_Config(void);
void readEncoderSpeed(void);
