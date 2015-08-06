#include "ds18b20.h"
#include "one_wire.h"
#include "core_cmFunc.h"
#include <stdio.h>

uint64_t srch_sng_rom(void)
{
  if (!ow_reset()) {
		return 0;
	}
	ow_write_byte(0x33);
	return ow_read_big_int();
}

void read_bytes(uint8_t* bytes)
{
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

float read_temp(void)
{

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
  float celc = (float)raw/16;
  return celc;
  // uint8_t big = (uint8_t)celc;
  // uint8_t small = celc - big;
  // printf("test\r\n");
  // printf("%d.%d", big, small);
  // return (int)celc;
}
