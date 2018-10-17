#ifndef sram_H_
#define sram_H_

#define SRAM_START_ADDR 0x1800

#endif

int SRAM_init(void);
int SRAM_write(unsigned int address, unsigned int data);
unsigned int SRAM_read(unsigned int address);
void SRAM_test(void);
