
#include "stm32f10x_lib.h"
//#include "fonts.h"
#include "lcd.h"

extern void SystemInit(void);
extern void SetSysClock(void);
extern void FSMC_LCD_Init(void);

extern void RCC_Configuration(void);
extern void NVIC_Configuration(void);
//extern void GPIO_Configuration(void);
extern void USART_Configuration(void);
extern void RTC_Configuration(void);
extern void RTC_Init(void);

extern void USART1_Init(void);
extern void GPIO_Configuration(void);
extern void Uart_Printf(char *);
extern void Print_Bill(void);

typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
u32 Time_Regulate(void);
u8 USART_Scanf(u32 value);
ErrorStatus HSEStartUpStatus;
volatile unsigned int SecStatus;
int OneSec = 1;
int NoOneSec = 0;
//BitAction  SecStatus;
typedef unsigned int uint32_t;
#define RTCClockSource_LSE
void Delay(vu32 time )
{
	for(; time != 0; time--);
}
int main(void)
{
	u32 RTCCount;
	u32 THH = 0, TMM = 0, TSS = 0;
	char Buff[80];
//#ifdef DEBUG
//    debug();
//#endif
//	SystemInit();
//	GPIO_Configuration();
//	USART1_Init();

//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);    

//	FSMC_LCD_Init();

//	LCD_Setup();

	RCC_Configuration(); 

 	NVIC_Configuration();

 	GPIO_Configuration();  

 	USART_Configuration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_PWR, ENABLE);
	

//	SystemInit();

//    Print_Bill();
	printf("wewewe");
//	Uart_Printf("why it was unavailable?");
	RTC_Init();
    while (1)
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
    	} 
		else {
			Delay(0xfff);
			GPIO_SetBits(GPIOE, GPIO_Pin_1);
		}
//		test();
    }
}

