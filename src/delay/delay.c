/**************************************************************************/
/*!
    @file     delay.c
    @author   Tyler Hoeflicker

    @description Blocking timer based on the MRT bus stall mode. CPU will block
    all processing/interupts until the timer has finished.

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2015, Tyler Hoeflicker (github.com/tylerflick)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include "LPC8xx.h"
#include "delay.h"
#include "mrt.h"

uint8_t ticks;
uint8_t chan;

void delay_init(uint8_t channel)
{
  chan = channel;

  LPC_SYSCON->SYSAHBCLKCTRL |= (0x1<<10);
  LPC_SYSCON->PRESETCTRL &= ~(0x1<<7);
  LPC_SYSCON->PRESETCTRL |= (0x1<<7);

  LPC_MRT->Channel[chan].CTRL = MRT_ONE_SHOT_STALL;
  ticks = SystemCoreClock/1000000;
}

void delay_ms(uint32_t millis)
{
	uint32_t us = millis*1000;
	if (us == 0)
		return;

  delay_us(us);
}

void delay_us(uint32_t micros) {
  LPC_MRT->Channel[chan].INTVAL = micros*ticks;
}
