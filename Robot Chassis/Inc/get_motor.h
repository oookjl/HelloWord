#ifndef _get_motor_H
#define _get_motor_H

 
#include "main.h"
#include "stdint.h"

#define CAN_3508_M1_ID 0x201
#define CAN_3508_M2_ID 0x202
#define CAN_3508_M3_ID 0x203
#define CAN_3508_M4_ID 0x204
#define RC_FRAME_LENGTH 18u

 extern CAN_RxHeaderTypeDef RxHeader;
 
typedef struct
{
	uint16_t angle;
	int16_t speed_rpm;
	int16_t current_get;
	uint16_t temperature;
}get_motor_t;

typedef struct
{
	struct
	{
		uint16_t ch0;
		uint16_t ch1;
		uint16_t ch2;
		uint16_t ch3;
		uint8_t s1;
		uint8_t s2;
	}rc;
	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
		uint8_t press_l;
		uint8_t press_r;
	}mouse;
	struct
	{
		uint16_t v;
	}key;
}RC_Ctl_t;
extern get_motor_t motor;

void get_motor_data(get_motor_t *motor, uint8_t buf[8]);
void RemoteDataProcess(void);
void Send_message(int16_t current1,int16_t current2,int16_t current3,int16_t current4);
void CANfilterConf(CAN_HandleTypeDef* hcan);
void dipan_speed(void);


extern uint8_t can2_rx_Data[8];
extern uint8_t mybuffer[RC_FRAME_LENGTH];
extern CAN_FilterTypeDef  CAN2_FilterConf;
extern RC_Ctl_t RC_CtrlData;
extern get_motor_t motor1;
extern get_motor_t motor2;
extern get_motor_t motor3;
extern get_motor_t motor4;
extern float x_part,y_part,w_part;
extern float wheel[4];
#endif

