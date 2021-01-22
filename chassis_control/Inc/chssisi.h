#ifndef __CHSSISI_H
#define __CHSSISI_H

#include "stdint.h"
#include "stm32f4xx.h"

#define CAN_3508_M1_ID 0x201
#define CAN_3508_M2_ID 0x202
#define CAN_3508_M3_ID 0x203
#define CAN_3508_M4_ID 0x204

typedef struct
{
	uint16_t ecd;
	int16_t speed_rpm;
	int16_t given_current;
	uint8_t temperate;
	int16_t last_ecd;
}motor_measure_t;

typedef struct
{
	uint16_t angle;
	int16_t speed_rpm;
	int16_t current_get;
	uint16_t temperature;
}get_motor_t;
//结构数组  4个电调
extern motor_measure_t motor_chassis[4];

//解码宏定义
#define get_motor_measure(ptr, data) \
{ \
(ptr)->last_ecd = (ptr)->ecd; \
(ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]); \
(ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); \
(ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
(ptr)->temperate = (data)[6]; \
}



void CAN_cmd_chassis(uint16_t motor1);

#endif /*__CHASSIS_MOTOR_H*/
