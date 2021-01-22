#include "get_data.h"
#include "can.h"
#include "usart.h"

CAN_FilterTypeDef  CAN1_FilterConf;
uint8_t mybuffer[RC_FRAME_LENGTH];
RC_Ctl_t RC_CtrlData;


void CANfilterConf(CAN_HandleTypeDef* hcan)
{
	if(hcan->Instance==CAN1)
	{
	CAN1_FilterConf.FilterIdHigh = 0x0000;
	CAN1_FilterConf.FilterIdLow =  0x0000;
	CAN1_FilterConf.FilterMaskIdHigh = 0x0000;
	CAN1_FilterConf.FilterMaskIdLow =0x0000;
	CAN1_FilterConf.FilterFIFOAssignment = CAN_RX_FIFO0;
	CAN1_FilterConf.FilterBank = 0;
	CAN1_FilterConf.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN1_FilterConf.FilterScale = CAN_FILTERSCALE_32BIT;
	CAN1_FilterConf.FilterActivation = ENABLE;   
	HAL_CAN_ConfigFilter(&hcan1,&CAN1_FilterConf);
	}
}

void Send_message(int16_t current1)
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
	message[2]=0;
	message[3]=0;
	message[4]=0;
	message[5]=0;
	message[6]=0;
	message[7]=0;
	HAL_CAN_AddTxMessage(&hcan1,&Txmessage,message,&TxMail);
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



