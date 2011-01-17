#include "stm32f10x_lib.h"
#include <stdio.h>
extern float distance;
extern long wait_time;
extern float speed;
extern int money;
extern u32 RTCCount;
extern u32 THH, TMM, TSS;
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
/** 
* @brief Get the final information to print the bill
* @author 高金龙
* @param info a pointer
*/
void Get_Info(Bill_Info_t *info)
{
	info->Year = 2011;
	info->Month = 1;
	info->Day = 10;
	info->Hour = THH;
	info->Minute = TMM;
	info->Second = TSS;
	info->Total_Miles = distance;
	info->Total_Money = money/10;
}
/** 
* @brief Print the bill to the COM
* @author 高金龙
* 
* @return 0 to success
*/
u16  Print_Bill(void)
{
	Bill_Info_t Info;

    Get_Info(&Info);

    printf("\r\n************Receipt************\r\n");
    printf("\r\n\r\nThank you for taking our service!\r\n\r\n");
    printf("Total Miles: %.1f km\r\n\r\n",Info.Total_Miles);
    printf("Money Amount: RMB %.2f Yuan\r\n\r\n\r\n",Info.Total_Money);
    printf("%d-%d-%d %d:%d:%d\r\n\r\n\r\n",Info.Year,Info.Month,Info.Day,Info.Hour,Info.Minute,Info.Second);
    printf("*******************************\r\n");
	return 0;
}

