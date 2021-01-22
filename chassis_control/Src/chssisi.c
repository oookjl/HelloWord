#include "chssisi.h"
#include "can.h"
#include "stm32f4xx.h"

CAN_TxHeaderTypeDef  CAN_TxHeaderStructure;
uint8_t chassis_can_send_data[2];
//将电流值发送给电调(标准帧)
void CAN_cmd_chassis(uint16_t motor1)
{
	uint32_t send_mail_box;  //
	send_mail_box = CAN_TX_MAILBOX0;
	
	CAN_TxHeaderStructure.StdId = 0x200;      //CAN_CHASSIS_ALL_ID
	CAN_TxHeaderStructure.IDE = CAN_ID_STD;             //CAN_ID_STD
	CAN_TxHeaderStructure.RTR = CAN_RTR_DATA;     //数据帧
	CAN_TxHeaderStructure.DLC = 0x02;
	chassis_can_send_data[0] = motor1>>8;   
	chassis_can_send_data[1]  = motor1; 
	/*
	chassis_can_send_data[2] = motor2>>8;
	chassis_can_send_data[3] = motor2;
	chassis_can_send_data[4] = motor3>>8;
	chassis_can_send_data[5] = motor3;
	chassis_can_send_data[6] = motor4>>8;
	chassis_can_send_data[7] = motor4;
	*/
	HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeaderStructure,chassis_can_send_data,&send_mail_box);
}//CHASSIS_CAN  -> hcan1                 pHeader->IDE

