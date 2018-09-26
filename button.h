#define BUTTON_L PB0
#define BUTTON_R PB1
#define BUTTON_JOYSTICK PB3

void button_init(void);
unsigned int button_read(unsigned int button_nr);
