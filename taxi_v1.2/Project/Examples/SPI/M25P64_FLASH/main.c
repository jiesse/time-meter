/**
  ******************************************************************************
  * @file SPI/M25P64_FLASH/main.c 
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
#include "platform_config.h"
#include "spi_flash.h"

/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_M25P64_FLASH
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define  FLASH_WriteAddress     0x700000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
#define  M25P64_FLASH_ID        0x202017
#define  BufferSize (countof(Tx_Buffer)-1)

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t Tx_Buffer[] = "STM32F10x SPI Firmware Library Example: communication with an M25P64 SPI FLASH";
uint8_t Index, Rx_Buffer[BufferSize];
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;
__IO uint32_t FLASH_ID = 0;

/* Private functions ---------------------------------------------------------*/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void RCC_Configuration(void);
void GPIO_Configuration(void);

/**
  * @brief  Main program
  * @param  None
  * @retval : None
  */
int main(void)
{
  /* System clocks configuration */
  RCC_Configuration();

  /* GPIO configuration */
  GPIO_Configuration();

  /* Initialize the SPI FLASH driver */
  SPI_FLASH_Init();

  /* Get SPI Flash ID */
  FLASH_ID = SPI_FLASH_ReadID();
  /* Check the SPI Flash ID */
  if (FLASH_ID == M25P64_FLASH_ID)
  {
    /* OK: Set GPIO_LED pin 6 */
    GPIO_WriteBit(GPIO_LED, GPIO_Pin_6, Bit_SET);
  }
  else
  {
    /* Error: Set GPIO_LED pin 7 */
    GPIO_WriteBit(GPIO_LED, GPIO_Pin_7, Bit_SET);
  }

  /* Perform a write in the Flash followed by a read of the written data */
  /* Erase SPI FLASH Sector to write on */
  SPI_FLASH_SectorErase(FLASH_SectorToErase);

  /* Write Tx_Buffer data to SPI FLASH memory */
  SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);

  /* Read data from SPI FLASH memory */
  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);

  /* Check the corectness of written dada */
  TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
  /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
     are the same */
  /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
     are different */

  /* Perform an erase in the Flash followed by a read of the written data */
  /* Erase SPI FLASH Sector to write on */
  SPI_FLASH_SectorErase(FLASH_SectorToErase);

  /* Read data from SPI FLASH memory */
  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);

  /* Check the corectness of erasing operation dada */
  for (Index = 0; Index < BufferSize; Index++)
  {
    if (Rx_Buffer[Index] != 0xFF)
    {
      TransferStatus2 = FAILED;
    }
  }
  /* TransferStatus2 = PASSED, if the specified sector part is erased */
  /* TransferStatus2 = FAILED, if the specified sector part is not well erased  */

  while (1)
  {}
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

  /* Enable GPIO_LED clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_LED, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval : None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure GPIO LED pin6 and pin7 as Output push-pull --------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_LED, &GPIO_InitStructure);
}

/**
  * @brief  Compares two buffers.
  * @param pBuffer1, pBuffer2: buffers to be compared.
  * @param BufferLength: buffer's length
  * @retval : PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
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
