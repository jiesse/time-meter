/**
  ******************************************************************************
  * @file FSMC/SRAM/main.c 
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
#include "fsmc_sram.h"

/** @addtogroup StdPeriph_Examples
  * @{
  */

/** @addtogroup FSMC_SRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE        0x400
#define WRITE_READ_ADDR    0x8000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
uint16_t TxBuffer[BUFFER_SIZE];
uint16_t RxBuffer[BUFFER_SIZE];
uint32_t WriteReadStatus = 0, Index = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void Fill_Buffer(uint16_t *pBuffer, uint16_t BufferLenght, uint32_t Offset);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
  /* System Clocks Configuration */
  RCC_Configuration();   

  /* PF.06 and PF.07 config to drive LD1 and LD2 ******************************/
  /* Enable GPIOF clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  
  /* Configure PF.06 and PF.07 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Configure FSMC Bank1 NOR/SRAM3 */
  FSMC_SRAM_Init();

  /* Write data to FSMC SRAM memory */
  /* Fill the buffer to send */
  Fill_Buffer(TxBuffer, BUFFER_SIZE, 0x3212);
  FSMC_SRAM_WriteBuffer(TxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);


  /* Read data from FSMC SRAM memory */
  FSMC_SRAM_ReadBuffer(RxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);  

  /* Read back SRAM memory and check content correctness */   
  for (Index = 0x00; (Index < BUFFER_SIZE) && (WriteReadStatus == 0); Index++)
  {
    if (RxBuffer[Index] != TxBuffer[Index])
    {
      WriteReadStatus = Index + 1;
    }
  }	

  if (WriteReadStatus == 0)
  {	/* OK */
    /* Turn on LD1 */
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
  }
  else
  { /* KO */
    /* Turn off LD2 */
    GPIO_SetBits(GPIOF, GPIO_Pin_7);     
  }

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
}

/**
   * @brief  Fill the global buffer
  * @param pBuffer: pointer on the Buffer to fill
  * @param BufferSize: size of the buffer to fill
  * @param Offset: first value to fill on the Buffer
  */
void Fill_Buffer(uint16_t *pBuffer, uint16_t BufferLenght, uint32_t Offset)
{
  uint16_t IndexTmp = 0;

  /* Put in global buffer same values */
  for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++ )
  {
    pBuffer[IndexTmp] = IndexTmp + Offset;
  }
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
