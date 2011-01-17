/**
  ******************************************************************************
  * @file NVIC/Priority/main.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main program body
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
#include "stm32f10x.h"
#include "platform_config.h"

/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup NVIC_Priority
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
NVIC_InitTypeDef NVIC_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
bool PreemptionOccured = FALSE; 
uint8_t PreemptionPriorityValue = 0; 

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
  /* Configure the system clocks */
  RCC_Configuration();

  /* Configure GPIOs */
  GPIO_Configuration();

  /* Configures the EXTI Lines */
  EXTI_Configuration();

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI0 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriorityValue;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable the EXTI9_5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Configure the SysTick Handler Priority: Preemption priority and subpriority */
  NVIC_SetPriority(SysTick_IRQn, (!PreemptionPriorityValue << 0x03));
  
  while (1)
  {
    if(PreemptionOccured != FALSE)
    {
      GPIO_WriteBit(GPIO_LED, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_LED, GPIO_Pin_6)));
      Delay(0x5FFFF);
      GPIO_WriteBit(GPIO_LED, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_LED, GPIO_Pin_7)));
      Delay(0x5FFFF);
      GPIO_WriteBit(GPIO_LED, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_LED, GPIO_Pin_8)));
      Delay(0x5FFFF);
      GPIO_WriteBit(GPIO_LED, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_LED, GPIO_Pin_9)));
      Delay(0x5FFFF); 
    }
  }
}

/**
  * @brief  Configures the different system clocks
  * @param  None
  * @retval : None
  */
void RCC_Configuration(void)
{
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

  /* Enable GPIOA, GPIO KEY Button, GPIO_LED and AFIO Clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIO_KEY_BUTTON | 
                         RCC_APB2Periph_GPIO_LED | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configures the used GPIO pins.
  * @param  None
  * @retval : None
  */
void GPIO_Configuration(void)
{
  /* Configure GPIO_LED pin 6, GPIO_LED pin 7, GPIO_LED pin 8 and GPIO_LED pin 9 as output push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_LED, &GPIO_InitStructure);
  
  /* Configure PA.00 as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure KEY Button GPIO pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY_BUTTON;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_KEY_BUTTON, &GPIO_InitStructure);
}

/**
  * @brief  Configures the used EXTI lines.
  * @param  None
  * @retval : None
  */
void EXTI_Configuration(void)
{
  /* Connect EXTI Line0 to PA.00 */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  /* Configure EXTI Line0 to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;  
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Connect KEY Button EXTI Line to KEY Button GPIO pin */
  GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KEY_BUTTON, GPIO_PIN_SOURCE_KEY_BUTTON);

  /* Configure KEY Button EXTI Line to generate an interrupt on falling edge */    
  EXTI_InitStructure.EXTI_Line = EXTI_LINE_KEY_BUTTON;
  EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  Inserts a delay time.
  * @param nCount: specifies the delay time length.
  * @retval : None
  */
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
