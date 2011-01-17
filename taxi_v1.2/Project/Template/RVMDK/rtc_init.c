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
 *	RCC��ʼ������
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
 *	NVIC��ʼ������
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
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;	  //ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  													
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQChannel;	  //ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  													
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;	  //ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
}


/**
 *	GPIO��ʼ������
 */
void GPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
    
  	/* LED�����ã�����ÿ������һ�� */
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  

  	/* Ĭ������PA9Ϊ���ڵ������������ */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  	/* Ĭ������PA10Ϊ���ڵ������������ */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE); 
						 
/**
 *	LED1 -> PB8	 ,	LED2 -> PB9 , LED3 -> PE0 , LED4 -> PE1
 *  ������ -> PC5
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
 *  ���ڳ�ʼ������
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
  printf("\r\n  Please Set Minutes��");
  while(Tmp_MM == 0xFF)
  {
    Tmp_MM = USART_Scanf(59);
  }
  printf(":  %d", Tmp_MM); 
  printf("\r\n  Please Set Seconds��");
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
/* ��Printf���ݷ���ITM�����Ĵ����˿�  */
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
#else  
/* ��Printf���ݷ������� */
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
* @author �߽���
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
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xAAAA ) {	 //���������û�б��
		//GPIO_ResetBits(GPIOE, GPIO_Pin_0);
		printf("\r\n\n RTC configuring....");
		RTC_Configuration();       						 //��RTC���г�ʼ��
		//GPIO_SetBits(GPIOE, GPIO_Pin_0);
		printf("OK!");
		RTC_WaitForLastTask();			    			 //�̼���ָ����Ҫ�ȵ���RTC_WaitForLastTask()���ȴ���־λRTOFF������
														 //ʵ���϶�RTC�κμĴ�������д����ǰ�������뱣֤��ǰһ��д������������ܽ��У�
														 //�������֤��������ͨ����ѯRTC_CR�Ĵ����е�RTOFF״̬λ���ж�RTC�Ĵ����Ƿ��ڸ����С�
														 //ֻ�е�RTOFF״̬λ��1���ſ���дRTC�Ĵ��� 

		RTC_SetCounter(Time_Regulate());		   	 	 //������ֵд��RTC������

		RTC_WaitForLastTask(); 

		BKP_WriteBackupRegister(BKP_DR1, 0xAAAA);

	} else {								 		//����������ǹ��ˣ�������ʲô������
		
     	RTC_WaitForSynchro();        				//�ȴ�RTC�Ĵ�����RTC_CNT,RTC_ALR and RTC_PRL����RTC��APBʱ��ͬ��
													//ʵ�����������ȴ�RTC_CRL�Ĵ����е�RSFλ���Ĵ���ͬ����־����Ӳ����1
     
	 	RTC_WaitForLastTask();       				//�̼���ָ����Ҫ�ȵ���RTC_WaitForLastTask()���ȴ���־λRTOFF������
													//ʵ���϶�RTC�κμĴ�������д����ǰ�������뱣֤��ǰһ��д������������ܽ��У�
													//�������֤��������ͨ����ѯRTC_CR�Ĵ����е�RTOFF״̬λ���ж�RTC�Ĵ����Ƿ��ڸ����С�
													//ֻ�е�RTOFF״̬λ��1���ſ���дRTC�Ĵ���
														 
     	RTC_ITConfig(RTC_IT_SEC, ENABLE);   		//ʹ�ܻ���ЧRTC�жϣ���������ʵ�����ж�ʹ�ܣ�
													//������������ʹ�ܵĲ����ֱ���RTC_IT_OW����ж�ʹ�ܡ�RTC_IT_ALR�����ж�ʹ��
     	RTC_WaitForLastTask();
	}
	/* Clear reset flags */
	RCC_ClearFlag();								//��λ�ж��֣������ϵ縴λ���ܽŸ�λ�������λ�����Ź���λ�ȵ�													//������Щ��λ������ͨ��дRMVFλ��1�������
	printf("\r\n ");
}
/** 
* @brief RTC refresh
* @author �߽���
*/
void RTC_GO()
{

    	if( SecStatus == OneSec ) {
			GPIO_ResetBits(GPIOE, GPIO_Pin_1);
			SecStatus = NoOneSec;
			Delay(0xfff);
			    
			RTCCount = RTC_GetCounter();		   //��ü���ֵ�����㵱ǰʱ��
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
