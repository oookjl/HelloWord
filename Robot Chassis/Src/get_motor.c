#include "can.h"
#include "get_motor.h"
#include "pid.h"

get_motor_t motor1;
get_motor_t motor2;
get_motor_t motor3;
get_motor_t motor4;

CAN_RxHeaderTypeDef RxHeader;
CAN_FilterTypeDef  CAN2_FilterConf;
uint8_t mybuffer[RC_FRAME_LENGTH];
RC_Ctl_t RC_CtrlData;
uint8_t can2_rx_Data[8];
float wheel[4];

float x_part,y_part,w_part;


void get_motor_data(get_motor_t *motor, uint8_t buf[8]){
	motor->angle        = (int16_t)(buf[0] << 8 | buf[1]);
	motor->speed_rpm    = (int16_t)(buf[2] << 8 | buf[3]);
	motor->current_get  = (int16_t)(buf[4] << 8 | buf[5]);
	motor->temperature  = (uint8_t)buf[6];
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(&hcan2,CAN_RX_FIFO0,&RxHeader,can2_rx_Data);
	if(RxHeader.StdId==0x201)
		{
			get_motor_data(&motor1,can2_rx_Data);
		}
	if(RxHeader.StdId==0x202)
		{
			get_motor_data(&motor2,can2_rx_Data);
		}
	if(RxHeader.StdId==0x203)
		{
			get_motor_data(&motor3,can2_rx_Data);
		}
	if(RxHeader.StdId==0x204)
		{
			get_motor_data(&motor4,can2_rx_Data);}
		
}

void RemoteDataProcess(void)
{
	uint8_t *pData = mybuffer;

	RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF;
	RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5))& 0x07FF;
	RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |((int16_t)pData[4] << 10)) & 0x07FF;
	RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) &0x07FF;
	RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
	RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);
	RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
	RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
	RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);
	RC_CtrlData.mouse.press_l = pData[12];
	RC_CtrlData.mouse.press_r = pData[13];
	RC_CtrlData.key.v = ((int16_t)pData[14]);// | ((int16_t)pData[15] << 8);
	//your control code ….
}

void Send_message(int16_t current1,int16_t current2,int16_t current3,int16_t current4)
{
	CAN_TxHeaderTypeDef Txmessage;
	uint32_t TxMail;
	uint8_t message[8];
	
	Txmessage.StdId=0X200;
	Txmessage.IDE=CAN_ID_STD;
	Txmessage.RTR=CAN_RTR_DATA;
	Txmessage.DLC=8;
	message[0]=current1>>8;
	message[1]=current1;
	message[2]=current2>>8;
	message[3]=current2;
	message[4]=current3>>8;
	message[5]=current3;	
	message[6]=current4>>8;
	message[7]=current4;

	HAL_CAN_AddTxMessage(&hcan2,&Txmessage,message,&TxMail);
}

void CANfilterConf(CAN_HandleTypeDef* hcan)
{
	if(hcan->Instance==CAN2)
	{
	CAN2_FilterConf.FilterIdHigh = 0x0000;
	CAN2_FilterConf.FilterIdLow =  0x0000;
	CAN2_FilterConf.FilterMaskIdHigh = 0x0000;
	CAN2_FilterConf.FilterMaskIdLow =0x0000;
	CAN2_FilterConf.FilterFIFOAssignment = CAN_RX_FIFO0;
	CAN2_FilterConf.FilterBank = 16;
	CAN2_FilterConf.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN2_FilterConf.FilterScale = CAN_FILTERSCALE_32BIT;
	CAN2_FilterConf.FilterActivation = ENABLE;   
	HAL_CAN_ConfigFilter(&hcan2,&CAN2_FilterConf);
	}
}

void dipan_speed(void)//ÂóÂÖ½âËã
{

	x_part=-((RC_CtrlData.rc.ch0-0x400)*3);
	y_part=((RC_CtrlData.rc.ch1-0x400)*3);//0x400=1024,3=·Å´ó±¶Êý
	w_part=-((RC_CtrlData.rc.ch2-0x400)*3);
	wheel[0]=(-x_part+y_part+w_part);
	wheel[1]=(-x_part-y_part+w_part);
	wheel[2]=-(x_part-y_part+w_part);
	wheel[3]=-(x_part+y_part+w_part);
}
