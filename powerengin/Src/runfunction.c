#include "runfunction.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "gpio.h"



uint8_t num[N]={0};
int flag1=0,flag2=0,flag3=0,flag4=0,flag5=0;
int j=0;
int TIM_STA=0;
int time1=0;

void get_number(void)
{

		srand(HAL_GetTick());
    int RandNum;
    int i, flag = 0, t=0;
    while(1)
    {
    	flag = 0;
    	if(t == N)
    		break;
    		
		RandNum = (rand()%(MAX - MIN+1)) + MIN;
		for(i = 0; i < t; i++)
		{
			if(num[i] == RandNum)
				flag = 1;
		}
		if(flag != 1)
		{
			num[t] = RandNum;
//			printf("µÚ%2dµÄÊý: %d\n",t+1,num[t]);
			t++;
		}	
	}
}

void middleLED(uint8_t num)
{
	if (num == 1)
	{
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);
	}
	if (num == 2)
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
	}
	if (num == 3)
	{
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_SET);
	}
	if (num == 4)
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
	}
	if (num == 5)
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	TIM_STA++;
	time1++;
}

void led_off(void)
{
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6|LED_GREEN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
}
