#include <stdint.h>

#ifndef DS18B20_H_
#define DS18B20_H_
#endif

#define DS18_BYTE_LEN 9

uint64_t srch_sng_rom(void);
float read_temp(void);
void read_bytes(uint8_t* bytes);
