//#include "stm32f10x.h"
#include "stm32f10x_lib.h"
//#include "platform_config.h"
#include "stm32f10x_usart.h"
//#include "misc.h"
#include <string.h>
typedef struct{
	float Total_Miles;
	float Total_Money;
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;
}Bill_Info_t;
//extern void Get_Info(Bill_Info_t * Info);
void Delay(vu32);
void USART1_Init(void);
void GPIO_Configuration(void);
void Uart_Printf(char *);
void Uart_Printf(char * Str)
{
	u16 i;
	char Buf[100];
	strcpy(Buf,Str);
	for(i = 0;Buf[i] != '\0';i++){
		USART_SendData(USART1 , Buf[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);			
	}
	
}
u16  Print_Bill(void)
{
    char Buf[100];
	Bill_Info_t Info;
    Info.Total_Miles = 12.8;
    Info.Total_Money = 30.2;
    Info.Year = 2011;
    Info.Month = 1;
    Info.Day = 9;
    Info.Hour = 12;
    Info.Minute = 23;
    Info.Second = 34;
#ifdef SET
    Get_Info(&Info);
#endif
    Uart_Printf("\r\n*******************************\r\n");
    Uart_Printf("\r\n\r\nThank you for take our service!\r\n\r\n");
    sprintf(Buf,"Total Miles: %.1f km\r\n\r\n",Info.Total_Miles);
    Uart_Printf(Buf);
    sprintf(Buf,"Money Amount: RMB %.2f Yuan\r\n\r\n\r\n",Info.Total_Money);
    Uart_Printf(Buf);
    sprintf(Buf,"%d-%d-%d %d:%d:%d\r\n\r\n\r\n",Info.Year,Info.Month,Info.Day,Info.Hour,Info.Minute,Info.Second);
    Uart_Printf(Buf);
    Uart_Printf("*******************************\r\n");
	return 0;
}


void USART1_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    

	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE, ENABLE);
    	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	 		//LED4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);		   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
	GPIO_Init(GPIOA, &GPIO_InitStructure);		       

}
