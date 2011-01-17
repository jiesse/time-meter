/**
  ******************************************************************************
  * @file NVIC/DMA_WFIMode/main.c 
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

/** @addtogroup NVIC_DMA_WFIMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART1_DR_Address    0x40013804

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
NVIC_InitTypeDef  NVIC_InitStructure;
DMA_InitTypeDef  DMA_InitStructure;
__IO uint32_t LowPowerMode = 0;
uint16_t DST_Buffer[10]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void DMA_Configuration(void);
void USART_Configuration(void);
uint8_t Buffercmp16(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
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
  
  /* Configures the DMA Channel */
  DMA_Configuration();
  
  /* Configures the USART1 */
  USART_Configuration();

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the DMA1 Channel 5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the EXTI9_5  Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
    
  while (1)
  {
    if(LowPowerMode == 1)
    {

      GPIO_ResetBits(GPIO_LED, GPIO_Pin_7 | GPIO_Pin_8);

      /* Request to enter WFI mode */
      __WFI();
      LowPowerMode = 0;
    }

    Delay(0xFFFFF);
    GPIO_WriteBit(GPIO_LED, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_LED, GPIO_Pin_6)));
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
  
  /* Enable USART1, GPIOA, GPIO_LED, GPIO_KEY_BUTTON and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | 
                         RCC_APB2Periph_GPIO_LED | RCC_APB2Periph_GPIO_KEY_BUTTON |
                         RCC_APB2Periph_AFIO, ENABLE);  
  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

/**
  * @brief  Configures the used GPIO pins.
  * @param  None
  * @retval : None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Configure GPIO_LED Pin 6, GPIO_LED Pin 7 and GPIO_LED Pin 8 as
     Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_LED, &GPIO_InitStructure);
  
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure GPIO KEY Button Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY_BUTTON;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_KEY_BUTTON, &GPIO_InitStructure);  
}

/**
  * @brief  Configures the used EXTI line.
  * @param  None
  * @retval : None
  */
void EXTI_Configuration(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Connect KEY Button EXTI Line to GPIO KEY Button Pin */
  GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KEY_BUTTON, GPIO_PIN_SOURCE_KEY_BUTTON);

  /* Configure KEY Button EXTI Line to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line = EXTI_LINE_KEY_BUTTON;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);  
}

/**
  * @brief  Configures the used DMA Channel.
  * @param  None
  * @retval : None
  */
void DMA_Configuration(void)
{
  DMA_InitTypeDef  DMA_InitStructure;

  /* DMA1 Channel5 Config */
  DMA_DeInit(DMA1_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DST_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 10;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);

  /* Enable Channel5 Transfer complete interrupt */
  DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
  
  /* DMA1 Channel5 enable */
  DMA_Cmd(DMA1_Channel5, ENABLE);
}

/**
  * @brief  Configures the USART1.
  * @param  None
  * @retval : None
  */
void USART_Configuration(void)
{
  USART_InitTypeDef  USART_InitStructure;

/* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);
  
  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
  
  /* Enable the USART1 */  
  USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  Compares two buffers.
  * @param pBuffer1, pBuffer2: buffers to be compared.
  * @param BufferLength: buffer's length
  * @retval : 0: pBuffer1 identical to pBuffer2
  *           1: pBuffer1 differs from pBuffer2
  */
uint8_t Buffercmp16(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return 0;
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
