/**************************************************************************/
/*
    @file     one_wire.c
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
#include "gpio.h"
#include "delay.h"
#include "one_wire.h"

#define INPUT   0
#define OUTPUT  1
#define LOW     0
#define HIGH    1

uint32_t owPort;
uint32_t owPin;

void ow_init(uint32_t port, uint32_t pin)
{
	owPort = port;
	owPin = pin;
  gpio_set_dir(port, pin, INPUT);
}

void ow_set_low()
{
  gpio_set_dir(owPort, owPin, OUTPUT);
	gpio_set_val(owPort, owPin, LOW);
}

void ow_set_high()
{
    gpio_set_dir(owPort, owPin, OUTPUT);
    gpio_set_val(owPort, owPin, HIGH);
}

uint8_t ow_reset()
{
  ow_set_low();
  delay_us(480);
  ow_set_low();
	delay_us(70);
  uint8_t p = gpio_get_val(owPort, owPin);
	ow_set_high();
	delay_us(410);
	return p ? 0 : 1;
}

uint32_t ow_read_int()
{
	gpio_set_dir(owPort, owPin, INPUT);
	return gpio_get_val(owPort, owPin);
}

uint32_t ow_read_bit()
{
	ow_set_low();
	delay_us(5);
	gpio_set_dir(owPort, owPin, INPUT);
  delay_us(9);
	uint32_t b = ow_read_int();
	delay_us(65);
	return b;
}

void ow_write_bit(int b)
{
	ow_set_low();
  delay_us(6);
	if (b) {
		ow_set_high();
		delay_us(60);
	} else {
		delay_us(60);
		ow_set_high();
	}

	delay_us(10);
}

void ow_write_byte(int data)
{
	uint8_t i;
	for (i = 0; i < 8; i++) {
		ow_write_bit(data & 0x01);
		data >>= 1;
	}
}

uint8_t ow_read_byte()
{
	uint8_t i, data = 0;
	for (i = 0; i < 8; i++) {
		data >>= 1;
		data |= ow_read_bit() ? 0x80 : 0x00;
	}
	return data;
}

uint64_t ow_read_big_int()
{
	uint64_t data = 0;
	uint8_t i;
	for (i = 0; i < 8; i++) {
		data <<= 8;
		data |= ow_read_byte();
	}
	return data;
}
