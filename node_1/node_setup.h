#ifndef F_CPU
#define F_CPU 4915200UL


#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))

#endif
