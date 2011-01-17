/**
  ******************************************************************************
  * @file FSMC/NOR_CodeExecute/binary/main.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main program body.
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

/** @addtogroup FSMC_NOR_CodeExecute_binary
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
  /* Enable GPIOF clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

  /* Configure IO connected to LD1, LD2, LD3 and LD4 leds */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  while (1)
  {
    /* Turn on LD1 */
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    /* Insert delay */
    Delay(0xAFFFF);

    /* Turn on LD2 and LD3 */
    GPIO_SetBits(GPIOF, GPIO_Pin_7 | GPIO_Pin_8);
    /* Turn off LD1 */
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    /* Insert delay */
    Delay(0xAFFFF);

    /* Turn on LD4 */
    GPIO_SetBits(GPIOF, GPIO_Pin_9);
    /* Turn off LD2 and LD3 */
    GPIO_ResetBits(GPIOF, GPIO_Pin_8 | GPIO_Pin_7);
    /* Insert delay */
    Delay(0xAFFFF);

    /* Turn off LD4 */
    GPIO_ResetBits(GPIOF, GPIO_Pin_9);
  }
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
