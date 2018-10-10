#include <stdio.h>

#define MCP_SID0_HIGH MCP_TXB0CTRL + 1
#define MCP_SID0_LOW MCP_TXB0CTRL + 2
#define MCP_RXB0DLC 0x65
#define MCP_RXB1DLC 0x75
#define MCP_RXB 0x66
#define MCP_TXB 0x36



typedef struct {
    uint8_t id;
    uint8_t length;
    uint8_t data[8];

} Can_block;

void CAN_init(void);

void CAN_send(Can_block* can_block);

Can_block CAN_recieve(uint8_t buffer);

void CAN_reset_interrupt_flag();
