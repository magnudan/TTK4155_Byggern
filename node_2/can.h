#ifndef can_H_
#define can_H_

#include <stdio.h>

#endif

typedef struct {
    uint8_t id;
    uint8_t length;
    uint8_t data[8];

} Can_block;

void CAN_init(void);

int CAN_send(Can_block* can_block);

Can_block CAN_recieve(uint8_t buffer);

void CAN_reset_interrupt_flag();

int CAN_clear_to_send();

int CAN_error();

void CAN_message_interrupt_init();
