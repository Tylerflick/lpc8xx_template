/**************************************************************************/
/*!
    @file     main.c

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2015, Tyler Hoeflicker
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
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "LPC8xx.h"
#include "gpio.h"
#include "mrt.h"
#include "uart.h"
#include "one_wire.h"
#include "ds18b20.h"
#include "delay.h"

#if defined(__CODE_RED)
  #include <cr_section_macros.h>
  #include <NXP/crp.h>
  __CRP const unsigned int CRP_WORD = CRP_NO_CRP ;
#endif

const BUF_SIZE = 10;
char ser_buf[10];
uint8_t buf_pos = 0;

void cfg_pins()
{
  /* Enable SWM clock */
   LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);  // this is already done in SystemInit()

  /* Pin Assign 8 bit Configuration */
  /* U0_TXD */
  /* U0_RXD */
  LPC_SWM->PINASSIGN0 = 0xffff0004UL;
  /* U1_TXD */
  /* U1_RXD */
  // LPC_SWM->PINASSIGN1 = 0xff0f10ffUL;
  LPC_SWM->PINASSIGN1 = 0xff100fffUL;
  /* Pin Assign 1 bit Configuration */
  #if !defined(USE_SWD)
    /* Pin setup generated via Switch Matrix Tool
       ------------------------------------------------
       PIO0_5 = RESET
       PIO0_4 = U0_TXD
       PIO0_3 = GPIO            - Disables SWDCLK
       PIO0_2 = GPIO (User LED) - Disables SWDIO
       PIO0_1 = GPIO
       PIO0_0 = U0_RXD
       ------------------------------------------------
       NOTE: SWD is disabled to free GPIO pins!
       ------------------------------------------------ */
    LPC_SWM->PINENABLE0 = 0xffffffbfUL;
  #else
    /* Pin setup generated via Switch Matrix Tool
       ------------------------------------------------
       PIO0_5 = RESET
       PIO0_4 = U0_TXD
       PIO0_3 = SWDCLK
       PIO0_2 = SWDIO
       PIO0_1 = GPIO
       PIO0_0 = U0_RXD
       ------------------------------------------------
       NOTE: LED on PIO0_2 unavailable due to SWDIO!
       ------------------------------------------------ */
    LPC_SWM->PINENABLE0 = 0xffffffb3UL;
  #endif
}

void report_tmp() {
  printf("%d", read_temp());
}

extern void UART0_IRQHandler()
{
	if(LPC_USART0->STAT & UART_STATUS_RXRDY) {
    if (buf_pos >= BUF_SIZE) {
      buf_pos = 0;
    }
     ser_buf[buf_pos] = LPC_USART0->RXDATA;
    ++buf_pos;
	}
}

extern void UART1_IRQHandler()
{
	if(LPC_USART1->STAT & UART_STATUS_RXRDY) {
    if (buf_pos >= BUF_SIZE) {
      buf_pos = 0;
    }
     ser_buf[buf_pos] = LPC_USART1->RXDATA;
     ++buf_pos;
	}
}

void com_evt_hd()
{

  uint8_t curByte = ser_buf[buf_pos - 1];
  if (curByte != 't' && curByte != 'c') {
    return;
  }

  if (curByte == 't') {
    report_tmp();
    buf_pos = 0;
    return;
  }

  return;
}

int main(void)
{
  cfg_pins();
  gpio_init();

  uart0_init(9600);
  uart1_init(9600);
  LPC_USART0->INTENSET = UART_STATUS_RXRDY;
  LPC_USART1->INTENSET = UART_STATUS_RXRDY;
  gpio_set_dir(0, 14, 0);
  delay_init(3);
  ow_init(0, 14);
  printf("System Ready.. \r\n");
  while (1) {
    __WFI();
    com_evt_hd();
  }
}
