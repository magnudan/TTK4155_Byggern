#define SRAM_START_ADDR 0x1800


int SRAM_init(void);
int SRAM_write(unsigned int address, unsigned int data);
unsigned int SRAM_read(unsigned int address);
void SRAM_test(void);
