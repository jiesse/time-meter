
//#include "stm32f10x.h"
#include "stm32f10x_lib.h"
#include <stdio.h>

extern void RCC_Configuration(void);
extern void NVIC_Configuration(void);
extern void GPIO_Configuration(void);
extern void USART_Configuration(void);
extern void RTC_Configuration(void);
extern void RTC_Init(void);
extern void RTC_GO(void);
extern void FSMC_LCD_Init(void);

extern u16  Print_Bill(void);
extern void test(void);
extern void Wel_Logo(void);

u32 Time_Regulate(void);
u8 USART_Scanf(u32 value);
extern void FSMC_LCD_Init(void);

extern void LCD_Setup(void);
//BitAction  SecStatus;
typedef unsigned int uint32_t;
float distance;
long wait_time;

int money;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 u8 kk;
void Timer_Config(void);
void EXTI_Config(void);

u8 key1;
u8 key2;

 
/** 
* @brief main function
* 
* @author: 姚明月
*
* @return 
*/
int main(void)
{
	u8 printed = 0;
	RTC_Init();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); 
	FSMC_LCD_Init();
	LCD_Setup();
	EXTI_Config();
	Timer_Config();
	distance = 0;
	wait_time = 0;
	while(1)
    {	
        if(key1 == 0)
            Wel_Logo();		
        if(key1 == 1)
        {
            printed  = 0;
            distance = 0;
            wait_time = 0;
            test();
        }
        else if(key1 == 2)
        {
            if(!printed)
            {
                Print_Bill();
                printed = 1;
            }
            GPIO_ResetBits(GPIOB , GPIO_Pin_8);
            GPIO_ResetBits(GPIOB , GPIO_Pin_9);
            GPIO_ResetBits(GPIOE , GPIO_Pin_0);
            GPIO_ResetBits(GPIOE , GPIO_Pin_1);
            Delay(0xfffff);
            Delay(0xfffff);
            Delay(0xfffff);
            GPIO_SetBits(GPIOB , GPIO_Pin_8);
            GPIO_SetBits(GPIOB , GPIO_Pin_9);
            GPIO_SetBits(GPIOE , GPIO_Pin_0);
            GPIO_SetBits(GPIOE , GPIO_Pin_1);
            Delay(0xfffff);
            Delay(0xfffff);
            Delay(0xfffff);
        }
			
	}													 
}

 /* * @brief  EXTI_Config Program.
  * @author 范振平
  * @param  None
  * @retval : None
  */
void EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	//EXTI_StructInit(&EXTI_InitStructure);
				 	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);	//管脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	EXTI_ClearITPendingBit(EXTI_Line3);
	EXTI_ClearITPendingBit(EXTI_Line2);

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//EXTI_Cmd(EXTI , ENABLE);
}

/** 
* @brief TIM2 Initial and Configure
* @author 李小龙
*/
void Timer_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period=2000;		 					//自动重装载寄存器周期的值(计数值)
	TIM_TimeBaseStructure.TIM_Prescaler= (36000 - 1);				//时钟预分频数   例如：时钟频率=72MHZ/(时钟预分频+1)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 			//采样分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		//向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);							//清除溢出中断标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);											//开启时钟

}
