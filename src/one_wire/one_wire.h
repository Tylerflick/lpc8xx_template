/**************************************************************************/
/*
    @file     one_wire.h
    @author   Tyler Hoeflicker github.com/tylerflick
    @brief    DS/Maxim OneWire library
              Adapted from https://github.com/jdesbonnet/LPC810_SousVide/blob/master/src/onewire.c
              Credit for original: github.com/jdesbonn


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

#include "LPC8xx.h"

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

void     ow_init(uint32_t port, uint32_t pin);
void     ow_set_low(void);
void     ow_set_high(void);
uint8_t  ow_reset(void);
uint32_t ow_read_int(void);
uint32_t ow_read_bit(void);
void     ow_write_bit(int b);
void     ow_write_byte(int data);
uint8_t  ow_read_byte(void);
uint64_t ow_read_big_int(void);

#endif
