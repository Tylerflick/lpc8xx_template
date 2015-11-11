/**************************************************************************/
/*!
    @file     ds18b20.c
    @author   Tyler Hoeflicker

    @description Library for communicating with Maxim DS18B20 thermometer.

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
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
   THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include "ds18b20.h"
#include "one_wire.h"
#include "core_cmFunc.h"
#include <stdio.h>

uint64_t srch_sng_rom(void) {
  if (!ow_reset()) {
    return 0;
  }
  ow_write_byte(0x33);
  return ow_read_big_int();
}

void read_bytes(uint8_t *bytes) {
  // if (sizeof(bytes) != sizeof(uint8_t)*DS18_BYTE_LEN) {
  // return;
  // }
  // Skip ROM command
  ow_write_byte(0xCC);
  delay_us(10);
  // Issue Convert command
  ow_write_byte(0x44);

  delay_ms(800);
  if (!ow_reset()) {
    printf("Reset failed \r\n");
    return;
  }
  // Skip ROM command
  ow_write_byte(0xCC);
  delay_us(10);
  /*delay_us(10);*/

  // Issue command to read scratch pad
  ow_write_byte(0xBE);

  uint8_t i;
  for (i = 0; i < DS18_BYTE_LEN; ++i) {
    bytes[i] = ow_read_byte();
  }
}

float read_temp(void) {

  if (!ow_reset()) {
    printf("Reset failed \r\n");
    return;
  }
  // Skip ROM command
  ow_write_byte(0xCC);
  delay_us(10);
  // Issue Convert command
  ow_write_byte(0x44);

  delay_ms(800);
  if (!ow_reset()) {
    printf("Reset failed \r\n");
    return;
  }
  // Skip ROM command
  ow_write_byte(0xCC);
  delay_us(10);
  /*delay_us(10);*/

  // Issue command to read scratch pad
  ow_write_byte(0xBE);

  // int data = 0;
  // data = ow_read_byte();
  // data |= ow_read_byte()<<8;
  uint8_t bytes[DS18_BYTE_LEN];
  read_bytes(&bytes[0]);
  uint32_t raw = (bytes[1] << 8) | bytes[0];
  float celc = (float)raw / 16;
  return celc;
  // uint8_t big = (uint8_t)celc;
  // uint8_t small = celc - big;
  // printf("test\r\n");
  // printf("%d.%d", big, small);
  // return (int)celc;
}
