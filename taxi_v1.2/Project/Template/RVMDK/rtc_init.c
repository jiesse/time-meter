#include "stm32f10x_lib.h"
#include <stdio.h>
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void RTC_Configuration(void);
u32 Time_Regulate(void);
u8 USART_Scanf(u32 value);
ErrorStatus HSEStartUpStatus;
volatile unsigned int SecStatus;
int OneSec = 1;
int NoOneSec = 0;
//BitAction  SecStatus;
typedef unsigned int uint32_t;
#define RTCClockSource_LSE
u32 RTCCount;
u32 THH = 0, TMM = 0, TSS = 0;
 void Delay(vu32 time )
{
	for(; time != 0; time--);
}
void RTC_Configuration(void)
{
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

#ifdef RTCClockSource_LSI
  /* Enable LSI */ 
  RCC_LSICmd(ENABLE);
  /* Wait till LSI is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select LSI as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);  
#elif defined	RTCClockSource_LSE  
  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
#endif


  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);


#ifdef RTCClockOutput_Enable  
  /* Disable the Tamper Pin */
  BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
                               functionality must be disabled */
                               
  /* Enable RTC Clock Output on Tamper Pin */
  BKP_RTCCalibrationClockOutputCmd(ENABLE);
#endif 

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  
  /* Enable the RTC Second */  
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  
  /* Set RTC prescaler: set RTC period to 1sec */
#ifdef RTCClockSource_LSI
  RTC_SetPrescaler(31999); /* RTC period = RTCCLK/RTC_PR = (32.000 KHz)/(31999+1) */
#elif defined	RTCClockSource_LSE
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
#endif
  
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/**
 *	RCC初始化配置
 */
void RCC_Configuration(void)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  } 
  
  /* Enable USART1, GPIOA and GPIOE clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | 
                         RCC_APB2Periph_GPIOE , ENABLE);
}


/**
 *	NVIC初始化配置
 */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif 

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  													
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;	  //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  													
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQChannel;	  //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  													
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;	  //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
}


/**
 *	GPIO初始化配置
 */
void GPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
    
  	/* LED灯配置，用于每秒闪动一次 */
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  

  	/* 默认配置PA9为串口的输入输出引脚 */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  	/* 默认配置PA10为串口的输入输出引脚 */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE); 
						 
/**
 *	LED1 -> PB8	 ,	LED2 -> PB9 , LED3 -> PE0 , LED4 -> PE1
 *  蜂鸣器 -> PC5
 */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}


/**
 *  串口初始化配置
 */
void USART_Configuration(void)
{
  	USART_InitTypeDef USART_InitStructure;
  	USART_ClockInitTypeDef  USART_ClockInitStructure;

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	/* Configure the USART1 synchronous paramters */
	USART_ClockInit(USART1, &USART_ClockInitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure USART1 basic and asynchronous paramters */
	USART_Init(USART1, &USART_InitStructure);
    
  	/* Enable USART1 */
  	USART_Cmd(USART1, ENABLE);
}



u32 Time_Regulate(void)
{
  u32 Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;

  printf("\r\n Time Setting...\n\r");
  printf("\r\n **************************************************************************** ");
  printf("\r\n * NOTE:                                                                    *");
  printf("\r\n * If the input number is ( 0<t<9 ),such as '3',YOU MUST input '03' instead *");
  printf("\r\n **************************************************************************** ");
  printf("\r\n\n Please Set Hours:");
  
  while(Tmp_HH == 0xFF)
  {
    Tmp_HH = USART_Scanf(23);
  }
  printf(":  %d", Tmp_HH); 
  printf("\r\n  Please Set Minutes：");
  while(Tmp_MM == 0xFF)
  {
    Tmp_MM = USART_Scanf(59);
  }
  printf(":  %d", Tmp_MM); 
  printf("\r\n  Please Set Seconds：");
  while(Tmp_SS == 0xFF)
  {
    Tmp_SS = USART_Scanf(59);
  }
  printf(":  %d", Tmp_SS); 

  /* Return the value to store in RTC counter register */
  return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}


int fputc(int ch, FILE *f)
{
#ifdef DBG_ITM
/* 将Printf内容发往ITM激励寄存器端口  */
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
#else  
/* 将Printf内容发往串口 */
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
#endif  
  return (ch);
}


u8 USART_Scanf(u32 value)
{
  u32 index = 0;
  u32 tmp[2] = {0, 0};     
  
  while(index < 2)
  {
    /* Loop until RXNE = 1 */
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {
    }
    tmp[index++] = (USART_ReceiveData(USART1));
    if((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    {
      printf("\n\rPlease enter valid number between 0 and 9");
      index--;
    }
  }
  /* Calculate the Corresponding value */
  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10); 
  /* Checks */
  if(index > value)
  {
    printf("\n\rPlease enter valid number between 0 and %d", value);
    return 0xFF;
  }
  return index;
}


/*******************************************************************************
* Function Name  : Time_Adjust
* Description    : Adjusts time.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Time_Adjust(void)
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask(); 
  /* Change the current time */
  RTC_SetCounter(Time_Regulate());
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();   
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
* @brief RTC Initial function
* @author 高金龙
*/
void RTC_Init()
{
  	/* System Clocks Configuration */
  	RCC_Configuration(); 
  	/* NVIC configuration */
  	NVIC_Configuration();
  	/* Configure the GPIOs */
  	GPIO_Configuration();  
  	/* Configure the USART1 */
  	USART_Configuration();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_PWR, ENABLE);
//=========================================================================
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xAAAA ) {	 //如果备份域没有标记
		//GPIO_ResetBits(GPIOE, GPIO_Pin_0);
		printf("\r\n\n RTC configuring....");
		RTC_Configuration();       						 //对RTC进行初始化
		//GPIO_SetBits(GPIOE, GPIO_Pin_0);
		printf("OK!");
		RTC_WaitForLastTask();			    			 //固件库指出，要先调用RTC_WaitForLastTask()，等待标志位RTOFF被设置
														 //实际上对RTC任何寄存器进行写操作前，都必须保证在前一次写操作结束后才能进行，
														 //这个“保证”，就是通过查询RTC_CR寄存器中的RTOFF状态位，判断RTC寄存器是否处于更新中。
														 //只有当RTOFF状态位是1，才可以写RTC寄存器 

		RTC_SetCounter(Time_Regulate());		   	 	 //将计数值写入RTC计数器

		RTC_WaitForLastTask(); 

		BKP_WriteBackupRegister(BKP_DR1, 0xAAAA);

	} else {								 		//如果备份域标记过了，不用做什么工作。
		
     	RTC_WaitForSynchro();        				//等待RTC寄存器（RTC_CNT,RTC_ALR and RTC_PRL）与RTC的APB时钟同步
													//实际上软件必须等待RTC_CRL寄存器中的RSF位（寄存器同步标志）被硬件置1
     
	 	RTC_WaitForLastTask();       				//固件库指出，要先调用RTC_WaitForLastTask()，等待标志位RTOFF被设置
													//实际上对RTC任何寄存器进行写操作前，都必须保证在前一次写操作结束后才能进行，
													//这个“保证”，就是通过查询RTC_CR寄存器中的RTOFF状态位，判断RTC寄存器是否处于更新中。
													//只有当RTOFF状态位是1，才可以写RTC寄存器
														 
     	RTC_ITConfig(RTC_IT_SEC, ENABLE);   		//使能或无效RTC中断，这里是想实现秒中断使能，
													//还有两个可以使能的参数分别是RTC_IT_OW溢出中断使能、RTC_IT_ALR闹钟中断使能
     	RTC_WaitForLastTask();
	}
	/* Clear reset flags */
	RCC_ClearFlag();								//复位有多种，包括上电复位、管脚复位、软件复位、看门狗复位等等													//所有这些复位，都是通过写RMVF位置1来清除。
	printf("\r\n ");
}
/** 
* @brief RTC refresh
* @author 高金龙
*/
void RTC_GO()
{

    	if( SecStatus == OneSec ) {
			GPIO_ResetBits(GPIOE, GPIO_Pin_1);
			SecStatus = NoOneSec;
			Delay(0xfff);
			    
			RTCCount = RTC_GetCounter();		   //获得计数值并计算当前时钟
			/* Compute  hours */
			THH = RTCCount/3600;
			/* Compute minutes */
			TMM = (RTCCount % 3600)/60;
			/* Compute seconds */
			TSS = (RTCCount % 3600)% 60;			
			printf("\rTime: %0.2d:%0.2d:%0.2d\r",THH, TMM, TSS); 		
    	} else {
			Delay(0xfff);
			GPIO_SetBits(GPIOE, GPIO_Pin_1);

		}
}
