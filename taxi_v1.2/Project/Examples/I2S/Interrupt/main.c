/**
  ******************************************************************************
  * @file I2S/Interrupt/main.c 
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

/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup I2S_Interrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2S_InitTypeDef I2S_InitStructure;
uint16_t I2S2_Buffer_Tx[32] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
                          0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
                          0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
                          0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                          0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
                          0x3D3E, 0x3F40};

uint16_t I2S3_Buffer_Rx[32];
volatile uint8_t TxIdx = 0, RxIdx = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);
TestStatus Buffercmp24bits(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval : None
  */
int main(void)
{
  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* NVIC configuration ------------------------------------------------------*/
  NVIC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();

  /* I2S peripheral configuration */
  I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
  I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16bextended;
  I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_48k;
  I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;

  /* I2S2 Master Transmitter to I2S3 Slave Receiver communication -----------*/
  /* I2S2 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
  I2S_Init(SPI2, &I2S_InitStructure);

  /* I2S3 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
  I2S_Init(SPI3, &I2S_InitStructure);

  /* Enable the I2S2 TxE interrupt */
  SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, ENABLE);

  /* Enable the I2S3 RxNE interrupt */
  SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_RXNE, ENABLE);

  /* Enable the I2S3 */
  I2S_Cmd(SPI3, ENABLE);

  /* Enable the I2S2 */
  I2S_Cmd(SPI2, ENABLE);

  /* Wait the end of communication */
  while (RxIdx < 32)
  {}

  TransferStatus1 = Buffercmp(I2S3_Buffer_Rx, I2S2_Buffer_Tx, 32);
  /* TransferStatus1 = PASSED, if the data transmitted from I2S2 and received by
                               I2S3 are the same
     TransferStatus1 = FAILED, if the data transmitted from I2S2 and received by
                               I2S3 are different */
  
  /* Reinitialize the buffers */
  for (RxIdx = 0; RxIdx < 32; RxIdx++)
  {
    I2S3_Buffer_Rx[RxIdx] = 0;
  }
  TxIdx = 0;
  RxIdx = 0;

  /* I2S peripheral configuration */
  I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
  I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_24b;
  I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_16k;
  I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;

  /* I2S2 Master Transmitter to I2S3 Slave Receiver communication -----------*/
  /* I2S2 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
  I2S_Init(SPI2, &I2S_InitStructure);

  /* I2S3 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
  I2S_Init(SPI3, &I2S_InitStructure);

  /* Enable the I2S2 TxE interrupt */
  SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, ENABLE);

  /* Enable the I2S3 RxNE interrupt */
  SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_RXNE, ENABLE);

  /* Enable the I2S3 */
  I2S_Cmd(SPI3, ENABLE);

  /* Enable the I2S2 */
  I2S_Cmd(SPI2, ENABLE);

  /* Wait the end of communication */
  while (RxIdx < 32)
  {
  }

  TransferStatus2 = Buffercmp24bits(I2S3_Buffer_Rx, I2S2_Buffer_Tx, 32);
  /* TransferStatus2 = PASSED, if the data transmitted from I2S2 and received by
                               I2S3 are the same
     TransferStatus2 = FAILED, if the data transmitted from I2S2 and received by
                               I2S3 are different */     

  while (1)
  {
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval : None
  */
void RCC_Configuration(void)
{
  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  SystemInit();

  /* Enable peripheral clocks ------------------------------------------------*/
  /* GPIOA, GPIOB and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_AFIO, ENABLE);

  /* SPI2 and SPI3 clocks enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval : None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Disable the JTAG interface and enable the SWJ interface */
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  /* Configure SPI2 pins: CK, WS and SD */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure SPI3 pins: CK and SD */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure SPI3 pins: WS */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval : None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  /* SPI2 IRQ Channel configuration */
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* SPI3 IRQ channel configuration */
  NVIC_InitStructure.NVIC_IRQChannel = SPI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Compares two buffers.
  * @param pBuffer1, pBuffer2: buffers to be compared.
  *   : - BufferLength: buffer's length
  * @retval : PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}

/**
  * @brief  Compares two buffers in 24 bits data format.
  * @param pBuffer1, pBuffer2: buffers to be compared.
  * @param BufferLength: buffer's length
  * @retval : PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp24bits(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      if (*pBuffer1 != (*pBuffer2 & 0xFF00))
      {
        return FAILED;
      }
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
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
  {}
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
