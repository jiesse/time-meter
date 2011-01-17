/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    04/06/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_rtc.h"
/** @addtogroup Template_Project
  * @{
  */
//#define TIM_IT_Update                      ((u16)0x0001)
//#define TIM_IT_CC1                         ((u16)0x0002)
//#define TIM_IT_CC2                         ((u16)0x0004)
//#define TIM_IT_CC3                         ((u16)0x0008)
//#define TIM_IT_CC4                         ((u16)0x0010)
//#define TIM_IT_COM                         ((u16)0x0020)
//#define TIM_IT_Trigger                     ((u16)0x0040)
//#define TIM_IT_Break                       ((u16)0x0080)
//#define TIM_FLAG_Update                    ((u16)0x0001)
//#define TIM_FLAG_CC1                       ((u16)0x0002)
//#define TIM_FLAG_CC2                       ((u16)0x0004)
//#define TIM_FLAG_CC3                       ((u16)0x0008)
//#define TIM_FLAG_CC4                       ((u16)0x0010)
//#define TIM_FLAG_COM                       ((u16)0x0020)
//#define TIM_FLAG_Trigger                   ((u16)0x0040)
//#define TIM_FLAG_Break                     ((u16)0x0080)
//#define TIM_FLAG_CC1OF                     ((u16)0x0200)
//#define TIM_FLAG_CC2OF                     ((u16)0x0400)
//#define TIM_FLAG_CC3OF                     ((u16)0x0800)
//#define TIM_FLAG_CC4OF                     ((u16)0x1000)
extern void RTC_ClearITPendingBit(uint16_t RTC_IT);
extern volatile unsigned int SecStatus;
extern int OneSec;
extern int NoOneSec;
extern u8 kk;
extern ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, u16 TIM_IT);

extern void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, u16 TIM_IT);
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
void RTC_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    RTC_ClearITPendingBit(RTC_IT_SEC);			  //首先必须清中断，否则一直响应中断
/*    
	switch (SecStatus) {
		case: 0
		GPIO_ResetBits(GPIOE, GPIO_Pin_1);
		break;

		case: 1
		GPIO_SetBits(GPIOE, GPIO_Pin_1);
		break;
		
		default
		break;
	}
*/
	SecStatus = OneSec;							  //设置标志位，表示现在达到一秒
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Reset RTC Counter when Time is 23:59:59 */
    if(RTC_GetCounter() == 0x00015180)			  //15180即为24小时的秒计数
    {
      RTC_SetCounter(0x0);
      /* Wait until last write operation on RTC registers has finished */
      RTC_WaitForLastTask();
    }
  }
} 


/*void TIM2_IRQHandler(void)
{
if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) {
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
		 kk++;
		 if(kk==5)
		 {
		 	kk=0;
		//distance+=speed*3.6;

		//if(speed<12)
		//wait_time++;
		}		

	}

}*/


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
