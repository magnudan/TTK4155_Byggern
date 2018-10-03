#include <stdio.h>

typedef struct {
    uint8_t id;
    uint8_t length;
    uint8_t data[8];

} Can_block;

void CAN_init(void);

void CAN_send(Can_block* can_block);
