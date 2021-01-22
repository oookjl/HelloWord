#include "can.h"
//#include "gpio.h"
#include "get_motor.h"
#include "pid.h"
get_motor_t motor={0};
CAN_RxHeaderTypeDef RxHeader;
uint8_t can1_rx_Data[8];
void get_motor_data(get_motor_t *motor, uint8_t buf[8]){
	motor->angle        = (int16_t)(buf[0] << 8 | buf[1]);
	motor->speed_rpm    = (int16_t)(buf[2] << 8 | buf[3]);
	motor->current_get  = (int16_t)(buf[4] << 8 | buf[5]);
	motor->temperature  = (uint8_t)buf[6];
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&RxHeader,can1_rx_Data);
	if(RxHeader.StdId==0X201)
	{
		get_motor_data(&motor,can1_rx_Data);

	}
	
}
