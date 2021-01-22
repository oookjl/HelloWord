 #include "main.h"
 
#define CAN_3508_M1_ID 0x201
#define CAN_3508_M2_ID 0x202
#define CAN_3508_M3_ID 0x203
#define CAN_3508_M4_ID 0x204
 extern CAN_RxHeaderTypeDef RxHeader;
 
typedef struct get_motor
{
	uint16_t angle;
	uint16_t speed_rpm;
	uint16_t current_get;
	uint16_t temperature;
}get_motor_t;
extern get_motor_t motor;

void get_motor_data(get_motor_t *motor, uint8_t buf[8]);

extern uint8_t can1_rx_Data[8];
