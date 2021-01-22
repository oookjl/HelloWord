
#include "main.h"
#define RC_FRAME_LENGTH 18u

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

extern RC_Ctl_t RC_CtrlData;
extern uint8_t mybuffer[RC_FRAME_LENGTH];

extern void Send_message(int16_t current1);
void CANfilterConf(CAN_HandleTypeDef* hcan);


