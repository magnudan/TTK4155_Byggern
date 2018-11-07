#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))

#define write_bit(val, reg, bit) (val ? set_bit(reg, bit) : clear_bit(reg, bit))

