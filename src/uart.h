/**************************************************************************/
/*!
    @file     uart.h
    @author   K. Townsend

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, K. Townsend (microBuilder.eu)
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
#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "LPC8xx.h"

#define UART_ENABLE          (1 << 0)
#define UART_DATA_LENGTH_8   (1 << 2)
#define UART_PARITY_NONE     (0 << 4)
#define UART_STOP_BIT_1      (0 << 6)

#define UART0_CLK_ENABLE     (1 << 14)
#define UART1_CLK_ENABLE     (1 << 15)
#define UART2_CLK_ENABLE     (1 << 16)

#define UART0_RST_N          (1 << 3)
#define UART1_RST_N          (1 << 4)
#define UART2_RST_N          (1 << 5)

/* Status bits */
#define UART_STATUS_RXRDY    (1 << 0)
#define UART_STATUS_RXIDLE   (1 << 1)
#define UART_STATUS_TXRDY    (1 << 2)
#define UART_STATUS_TXIDLE   (1 << 3)
#define UART_STATUS_CTSDEL   (1 << 5)
#define UART_STATUS_RXBRKDEL (1 << 11)

void uart0_init     (uint32_t baudRate);
void uart1_init     (uint32_t baudRate);
void uart2_init     (uint32_t baudRate);
void uart0_snd_chr (char buffer);
void uart0_snd     (char *buffer, uint32_t length);
void uart1_snd_chr (char buffer);
void uart1_snd     (char *buffer, uint32_t length);
void uart2_snd_chr (char buffer);
void uart2_snd     (char *buffer, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif
