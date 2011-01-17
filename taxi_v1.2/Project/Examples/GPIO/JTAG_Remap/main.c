/**
  ******************************************************************************
  * @file GPIO/JTAG_Remap/main.c 
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

/** @addtogroup GPIO_JTAG_Remap
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
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
    
  /* Configure Key Button GPIO Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY_BUTTON;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_KEY_BUTTON, &GPIO_InitStructure);

  /* Test if Key Button GPIO Pin level is low (Key push-button on Eval Board pressed) */
  if (GPIO_ReadInputDataBit(GPIO_KEY_BUTTON, GPIO_PIN_KEY_BUTTON) == 0x00)
  { /* Key is pressed */

    /* Disable the Serial Wire Jtag Debug Port SWJ-DP */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    /* Configure PA.13 (JTMS/SWDAT), PA.14 (JTCK/SWCLK) and PA.15 (JTDI) as 
       output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PB.03 (JTDO) and PB.04 (JTRST) as output push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    while (1)
    {
      /* Toggle JTMS/SWDAT pin */
      GPIO_WriteBit(GPIOA, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_13)));
      /* Insert delay */
      Delay(0x5FFFF);

      /* Toggle JTCK/SWCLK pin */
      GPIO_WriteBit(GPIOA, GPIO_Pin_14, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_14)));
      /* Insert delay */
      Delay(0x5FFFF);

      /* Toggle JTDI pin */
      GPIO_WriteBit(GPIOA, GPIO_Pin_15, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15)));
      /* Insert delay */
      Delay(0x5FFFF);

      /* Toggle JTDO pin */
      GPIO_WriteBit(GPIOB, GPIO_Pin_3, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_3)));
      /* Insert delay */
      Delay(0x5FFFF);

      /* Toggle JTRST pin */
      GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_4)));
      /* Insert delay */
      Delay(0x5FFFF);
    }
  }
  else
  {
    while (1)
    {
    }
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
   
  /* Enable GPIOA, GPIOB, RCC_APB2Periph_GPIO_KEY_BUTTON and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIO_KEY_BUTTON | RCC_APB2Periph_AFIO, ENABLE);
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
