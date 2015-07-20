#ifndef ONEWIRE_H_
#define ONEWIRE_H_

void owInit(int port, int pin);
void owSetLow(void);
void owSetHigh(void);
int owReset(void);
int owReadInt(void);
int owReadBit(void);
void owWriteBit(int b);
void owWriteByte(int data);
int owReadByte(void);
uint64_t owReadBigInt(void);

#endif

