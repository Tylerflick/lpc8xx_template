#include "LPC8xx.h"

#ifndef DELAY_H_
#define DELAY_H_

void delay_init(uint8_t channel);
void delay_ms(uint32_t millis);
void delay_us(uint32_t micros);

#endif
