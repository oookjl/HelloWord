#include "main.h"

#define middleLED1 
#define middleLED2
#define middleLED3
#define middleLED4
#define middleLED5
#define LED1 HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_1)
#define LED2 HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)
#define LED3 HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)
#define LED4 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)
#define LED5 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)
#define BLED1 HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_2)
#define BLED2 HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_7)
#define BLED3 HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_6)
#define BLED4 HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_5)
#define BLED5 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)

#define LED_RED_Pin GPIO_PIN_11
#define LED_RED_GPIO_Port GPIOE
#define LED_GREEN_Pin GPIO_PIN_14
#define LED_GREEN_GPIO_Port GPIOF

#define MAX 5
#define MIN 1
#define N 5

extern uint8_t num[N];
extern int i;
extern int j;
extern int TIM_STA;
extern int flag1,flag2,flag3,flag4,flag5;
extern int time1;


extern void get_number(void);
extern void middleLED(uint8_t num);
extern void led_off(void);


