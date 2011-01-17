/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : lcd.c
* Author             : MCD Application Team
* Version            : V1.1
* Date               : 11/26/2007
* Description        : This file includes the LCD driver for AM-240320LTNQW00H
*                      (LCD_HX8312) and AM-240320L8TNQW00H (LCD_ILI9320)
*                      Liquid Crystal Display Module of STM3210B-EVAL board.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "fonts.h"
#include "lcd.h"
#include "TFT_font.h"

#include<stdio.h>
#include<stdlib.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

extern const unsigned char gImage_12[];

#define LCD_TYPE  0x9325

#define START_BYTE  0x70
#define SET_INDEX   0x00
#define READ_STATUS 0x01
#define WRITE_REG   0x02
#define READ_REG    0x03
#define WRITE_RAM   0x0022

#define LCD_Data_Addr    ((uint32_t)0x60020000)    
#define LCD_Reg_Addr     ((uint32_t)0x60000000)
/*---------------------------LCD marco commad-------------------------------*\
*硬件宏，移植的时候需要处理好
\*---------------------------LCD marco commad-------------------------------*/
#define  LCD_BUS    GPIOE->ODR
#define  LCD_nRST   GPIOE->BRR=GPIO_Pin_1
#define  LCD_nCS    GPIOD->BRR=GPIO_Pin_7
#define  LCD_nRS    GPIOD->BRR=GPIO_Pin_11
#define  LCD_nWR    GPIOD->BRR=GPIO_Pin_5
#define  LCD_nRD    GPIOD->BRR=GPIO_Pin_11

#define  LCD_RST    GPIOE->BSRR=GPIO_Pin_1
#define  LCD_CS     GPIOD->BSRR=GPIO_Pin_7
#define  LCD_RS     GPIOD->BSRR=GPIO_Pin_11
#define  LCD_WR     GPIOD->BSRR=GPIO_Pin_5
#define  LCD_RD     GPIOD->BSRR=GPIO_Pin_11



//extern const u16 ASCII_Table[];
extern const unsigned char tab[]="1234567890abcdefghijklmnopqrstuvwxyz";
extern const unsigned char tab_wel[8]="Welcome!";
extern const unsigned char tab_wait[19]="Wait/Low Speed Time";
extern const unsigned char tab_fee[13]="Current Fee :";
extern const unsigned char tab_distance[17]="Current Distance:";
extern const unsigned char tab_fee_ratio[20]="Fee Ratio:3.5yuan/km";
extern const unsigned char tab_speed[12]="Speed Ratio:";

//extern unsigned char tab_time[8]="22-12-24";
//extern unsigned char tab_date[10]="4011-1-10";
//extern unsigned char tab_wait_time[5]="00-00";
extern char tab_fee_calc[5]="355";
extern char tab_fee_float[3]=".0";
extern unsigned char tab_km[3]="km";
extern char tab_distance_calc[5]="200.2";
extern unsigned char tab_speed_calc[6]="60km/h";
//extern  char tab_speedsize[1]="2";
extern u8 key1;
extern u8 key2;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
extern const unsigned char gImage_arm79[];
extern const unsigned char gImage_arm_logo[] ;


extern float distance;
extern long wait_time;
extern float speed;
extern int money;
extern u32 RTCCount;
extern u32 THH, TMM, TSS;
/*---------------写数据到GRAM----------------*/
void    LCD_WriteRAM(unsigned int val)
{   
	*(volatile uint16_t *)(LCD_Data_Addr) = val; 	
}
/*---------------写索引寄存器----------------*/
void LCD_WriteIndex(unsigned int index)
{
	*(volatile uint16_t *)(LCD_Reg_Addr) = index;

}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/

void LCD_WriteReg(unsigned int LCD_Reg, unsigned int LCD_RegValue)
{
	//LCD_nCS;
	*(volatile uint16_t *) (LCD_Reg_Addr) = LCD_Reg;
	*(volatile uint16_t *) (LCD_Data_Addr) = LCD_RegValue;
	//LCD_CS;
}
/*---------------写数据准备-------------------*/
void LCD_WriteRAM_Prepare(void)   
{
	LCD_WriteIndex(WRITE_RAM);
}

 /**
 * 读数据函数  */
 
unsigned int LCD_RD_Data(void)
{
	unsigned int temp,i=0;

	for(; i < 1; i++){
		temp = (*(volatile uint16_t *) (LCD_Data_Addr)); 
	}
	return( temp );	
}



/*---------------写数据完成-------------------*/
#define  LCD_WriteRAM_Ready() {LCD_CS;}

/*---------------------------LCD marco end-------------------------------*/


/* Private variables ---------------------------------------------------------*/
/* Global variables to set the written text color */
static  vu16 TextColor = 0x0000, BackColor = 0xFFFF;

/* Private function prototypes -----------------------------------------------*/
static  u32   StrLength(u8 *Str);
static  void  Delay    (u32 nCount);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : LCD_Setup
* Description    : Setups the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void  Delay (u32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*******************************************************************************
* Function Name  : StrLength
* Description    : Returns length of string.
* Input          : - Str: Character Pointer.
* Output         : None
* Return         : String length.
*******************************************************************************/
static u32 StrLength(u8 *Str)
{
  u32 Index = 0;

  /* Increment the Index unless the end of string */
  for(Index = 0; *Str != '\0'; Str++, Index++)
  {
  }

  return Index;
}

void LCD_Setup(void)
{
/* Configure the LCD Control pins --------------------------------------------*/
	LCD_CtrlLinesConfig();
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);
    Delay(0x5FFFF);					   
    GPIO_SetBits(GPIOC, GPIO_Pin_1 );		 	 
	Delay(0x5FFFF);	
	  //************* Start Initial Sequence **********//
	LCD_WriteReg(0x00E3, 0x3008); // Set u16ernal timing
	LCD_WriteReg(0x00E7, 0x0012); // Set u16ernal timing
	LCD_WriteReg(0x00EF, 0x1231); // Set u16ernal timing
	LCD_WriteReg(0x0001, 0x0100); // set SS and SM bit
	LCD_WriteReg(0x0002, 0x0700); // set 1 line inversion
	LCD_WriteReg(0x0003, 0x1038); // set GRAM write direction and BGR=1.
	LCD_WriteReg(0x0004, 0x0000); // Resize register
	LCD_WriteReg(0x0008, 0x020E); // set the back porch and front porch
	LCD_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
	LCD_WriteReg(0x000A, 0x0000); // FMARK function
	LCD_WriteReg(0x000C, 0x0000); // RGB u16erface setting
	LCD_WriteReg(0x000D, 0x0000); // Frame marker Position
	LCD_WriteReg(0x000F, 0x0000); // RGB u16erface polarity
	//*************Power On sequence ****************//
	LCD_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
	LCD_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	Delay(0XAFFFF); // Dis-charge capacitor power voltage
	LCD_WriteReg(0x0010, 0x1290); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(0x0011, 0x0221); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	Delay(0XAFFFF); // Delay 50ms
	LCD_WriteReg(0x0012, 0x001A); // External reference voltage= Vci;
	Delay(0XAFFFF); // Delay 50ms
	LCD_WriteReg(0x0013, 0x1600); // R13=0F00 when R12=009E;VDV[4:0] for VCOM amplitude
	LCD_WriteReg(0x0029, 0x0022); // R29=0019 when R12=009E;VCM[5:0] for VCOMH
	LCD_WriteReg(0x002B, 0x000A); // Frame Rate 
	Delay(0XAFFFF); // Delay 50ms
	LCD_WriteReg(0x0020, 0x0000); // GRAM horizontal Address
	LCD_WriteReg(0x0021, 0x0000); // GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WriteReg(0x0030, 0x0000);
	LCD_WriteReg(0x0031, 0x0302);
	LCD_WriteReg(0x0032, 0x0202);
	LCD_WriteReg(0x0035, 0x0103);
	LCD_WriteReg(0x0036, 0x080C);
	LCD_WriteReg(0x0037, 0x0505);
	LCD_WriteReg(0x0038, 0x0504);
	LCD_WriteReg(0x0039, 0x0707);
	LCD_WriteReg(0x003C, 0x0301);
	LCD_WriteReg(0x003D, 0x1008);
	//------------------ Set GRAM area ---------------//
	LCD_WriteReg(0x0050, 0x0000); // Horizontal GRAM Start Address
	LCD_WriteReg(0x0051, 0x00EF); // Horizontal GRAM End Address
	LCD_WriteReg(0x0052, 0x0000); // Vertical GRAM Start Address
	LCD_WriteReg(0x0053, 0x013F); // Vertical GRAM Start Address
	LCD_WriteReg(0x0060, 0x2700); // Gate Scan Line
	LCD_WriteReg(0x0061, 0x0001); // NDL,VLE, REV
	LCD_WriteReg(0x006A, 0x0000); // set scrolling line
	//-------------- Partial Display Control ---------//
	LCD_WriteReg(0x0080, 0x0000);
	LCD_WriteReg(0x0081, 0x0000);
	LCD_WriteReg(0x0082, 0x0000);
	LCD_WriteReg(0x0083, 0x0000);
	LCD_WriteReg(0x0084, 0x0000);
	LCD_WriteReg(0x0085, 0x0000);
	//-------------- Panel Control -------------------//
	LCD_WriteReg(0x0090, 0x0010);
	LCD_WriteReg(0x0092, 0x0600);
	LCD_WriteReg(0x0093, 0x0003);
	LCD_WriteReg(0x0095, 0x0110);
	LCD_WriteReg(0x0097, 0x0000);
	LCD_WriteReg(0x0098, 0x0000);
	LCD_WriteReg(0x0007, 0x0133); // 262K color and display ON
}

/*******************************************************************************
* Function Name  : LCD_SetTextColor
* Description    : Sets the Text color.
* Input          : - Color: specifies the Text color code RGB(5-6-5).
* Output         : - TextColor: Text color global variable used by LCD_DrawChar
*                  and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetTextColor(vu16 Color)
{
  TextColor = Color;
}

/*******************************************************************************
* Function Name  : LCD_SetBackColor
* Description    : Sets the Background color.
* Input          : - Color: specifies the Background color code RGB(5-6-5).
* Output         : - BackColor: Background color global variable used by
*                  LCD_DrawChar and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetBackColor(vu16 Color)
{
  BackColor = Color;
}

/*******************************************************************************
* Function Name  : LCD_ClearLine
* Description    : Clears the selected line.
* Input          : - Line: the Line to be cleared.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ClearLine(u8 Line)
{
  LCD_DisplayStringLine(Line, "                    ");
}

/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : Clears the hole LCD.
* Input          : Color: the color of the background.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(u16 Color)
{
  u32 index = 0;

  LCD_SetCursor(0x00, 0x013F);

    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  for(index = 0; index < 76800; index++)
  {
    LCD_WriteRAM(Color);
  }
  LCD_WriteRAM_Ready();
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(u8 Xpos, u16 Ypos)
{
    LCD_WriteReg(0x0020, Xpos);
    LCD_WriteReg(0x0021, Ypos);
}

/*******************************************************************************
* Function Name  : LCD_DrawChar
* Description    : Draws a character on LCD.
* Input          : - Xpos: the Line where to display the character shape.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - Ypos: start column address.
*                  - c: pointer to the character data.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c)
{
  u32 index = 0, i = 0;
  u8 Yaddress = 0;

  Yaddress = Ypos;

  LCD_SetCursor(Xpos, Yaddress);

  for(index = 0; index < 24; index++)
  {
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(i = 0; i < 16; i++)
    {
      if((c[index] & (1 << i)) == 0x00)
      {
        LCD_WriteRAM(BackColor);
      }
      else
      {
        LCD_WriteRAM(TextColor);
      }
    }
    LCD_WriteRAM_Ready();
    Yaddress++;
    LCD_SetCursor(Xpos, Yaddress);
  }  
}
/*******************************************************************************
* Function Name  : LCD_DisplayChar
* Description    : Displays one character (16dots width, 24dots height).
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - Column: start column address.
*                  - Ascii: character ascii code, must be between 0x20 and 0x7E.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii)
{
  Ascii -= 32;
//  LCD_DrawChar(Line, Column, &ASCII_Table[Ascii * 24]);
}

/*******************************************************************************
* Function Name  : LCD_DisplayStringLine
* Description    : Displays a maximum of 20 char on the LCD.
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - *ptr: pointer to string to display on LCD.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayStringLine(u8 Line, u8 *ptr)
{
  u32 i = 0;
  u16 refcolumn = 0;

  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (i < 15))
  {
    /* Display one character on LCD */
    LCD_DisplayChar(refcolumn, Line, *ptr);
    /* Decrement the column position by 16 */
    refcolumn+= 16;
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    i++;
  }
}

/*******************************************************************************
* Function Name  : LCD_DisplayString
* Description    : Displays a maximum of 200 char on the LCD.
* Input          : - Line: the starting Line where to display the character shape.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - *ptr: pointer to string to display on LCD.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayString(u8 Line, u8 *ptr)
{
  u32 i = 0, column = 0, index = 0, spaceindex = 0;
  u16 refcolumn = 319;
  u32 length = 0;

  /* Get the string length */
  length = StrLength(ptr);
  if(length > 200)
  {
    /* Set the Cursor position */
    LCD_SetCursor(Line, 0x013F);
    /* Clear the Selected Line */
    LCD_ClearLine(Line);
    LCD_DisplayStringLine(Line, "   String too long  ");
  }
  else
  {
    /* Set the Cursor position */
    LCD_SetCursor(Line, 0x013F);
    /* Clear the Selected Line */
//    LCD_ClearLine(Line);

    while(length--)
    {
      if(index == 20)
      {
        if(*ptr == 0x20)
        {
          ptr++;
        }
        else
        {
          for(i = 0; i < spaceindex; i++)
          {
            LCD_DisplayChar(Line, column, ' ');
            column -= 16;
          }
          ptr -= (spaceindex - 1);
          length += (spaceindex - 1);
        }
        Line += 24;
        /* Clear the Selected Line */
//        LCD_ClearLine(Line);
        refcolumn = 319;
        index = 0;
      }
      /* Display one character on LCD */
      LCD_DisplayChar(Line, refcolumn, *ptr);

      /* Increment character number in one line */
      index++;

      /* Decrement the column position by 16 */
      refcolumn -= 16;
      /* Point on the next character */
      ptr++;
      /* Increment the number of character after the last space */
      spaceindex++;
      if(*ptr == 0x20)
      {
        spaceindex = 0;
        column = refcolumn - 16;
      }
    }
  }
}
/*******************************************************************************
* Function Name  : LCD_SetDisplayWindow
* Description    : Sets a display window
* Input          : - Xpos: specifies the X buttom left position.
*                  - Ypos: specifies the Y buttom left position.
*                  - Height: display window height.
*                  - Width: display window width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Width, u16 Height)
{
 
      LCD_WriteReg(0x0050, Xpos);
      LCD_WriteReg(0x0051, (Xpos+Width-1));

      LCD_WriteReg(0x0052, Ypos);
      LCD_WriteReg(0x0053,(Ypos + Height-1));
      
      LCD_SetCursor(Xpos, Ypos);
}

/*******************************************************************************
* Function Name  : LCD_WindowModeDisable
* Description    : Disables LCD Window mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WindowModeDisable(void)
{
    LCD_SetDisplayWindow(0, 0, 239, 319);
}
/*******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : Displays a line.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Length: line length.
*                  - Direction: line direction.
*                    This parameter can be one of the following values: Vertical
*                    or Horizontal.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawLine(u8 Xpos, u16 Ypos, u16 Length, u8 Direction)
{
  u32 i = 0;

  LCD_SetCursor(Xpos, Ypos);

  if(Direction == Horizontal)
  {

    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
     
    for(i = 0; i < Length; i++)
    {
      LCD_WriteRAM(Red);
	  
    }
    
     LCD_WriteRAM_Ready();
  }
  else
  {
   for(i = 0; i < Length; i++)
    {

    	 LCD_WriteRAMWord(Red);      
      	 Ypos++;
      
         LCD_SetCursor(Xpos, Ypos);
    }
  }
}

/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : Displays a rectangle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Width, u16 Height)
{
  LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
  LCD_DrawLine(Xpos, (Ypos + Height), Width, Horizontal);

  LCD_DrawLine(Xpos, Ypos, Height, Vertical);
  LCD_DrawLine((Xpos+Width-1) ,Ypos, Height, Vertical);
}

/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : Displays a rectangle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRectFill(u8 Xpos, u16 Ypos, u8 Width, u16 Height,u16 fill){
  u8 j;
  LCD_SetDisplayWindow(Xpos,Ypos,Width,Height);

  LCD_WriteRAM_Prepare();
   for(Height=Height;Height>0;Height--)
     for(j=Width;j>0;j--)
        LCD_WriteRAM(fill);
  LCD_WriteRAM_Ready();
  LCD_WindowModeDisable();
}

/*******************************************************************************
* Function Name  : LCD_DrawCircle
* Description    : Displays a circle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius)
{
  s32  D;/* Decision Variable */
  u32  CurX;/* Current X Value */
  u32  CurY;/* Current Y Value */

  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;

  while (CurX <= CurY)
  {
    LCD_SetCursor(Xpos + CurX, Ypos + CurY);
 
      LCD_WriteRAMWord(TextColor);

 
    LCD_SetCursor(Xpos + CurX, Ypos - CurY);

      LCD_WriteRAMWord(TextColor);

    LCD_SetCursor(Xpos - CurX, Ypos + CurY);

      LCD_WriteRAMWord(TextColor);

    LCD_SetCursor(Xpos - CurX, Ypos - CurY);

      LCD_WriteRAMWord(TextColor);

    LCD_SetCursor(Xpos + CurY, Ypos + CurX);
    
    
      LCD_WriteRAMWord(TextColor);

    LCD_SetCursor(Xpos + CurY, Ypos - CurX);

      LCD_WriteRAMWord(TextColor);
  

    LCD_SetCursor(Xpos - CurY, Ypos + CurX);

      LCD_WriteRAMWord(TextColor);

    LCD_SetCursor(Xpos - CurY, Ypos - CurX);

      LCD_WriteRAMWord(TextColor);

    if (D < 0)
    {
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

/*******************************************************************************
* Function Name  : LCD_DrawMonoPict
* Description    : Displays a monocolor picture.
* Input          : - Pict: pointer to the picture array.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawMonoPict(uc8 *Pict)
{
  u32 index = 0, i = 0;

  //LCD_SetCursor(0, 0);

    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  for(index = 0; index < (6040); index++)
  {
    for(i = 0; i < 8; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00) {
        LCD_WriteRAM(BackColor);
      }
      else {
        LCD_WriteRAM(TextColor);
      }
    }
  }
  LCD_WriteRAM_Ready();
}




/*******************************************************************************
* Function Name  : LCD_WriteRAMWord
* Description    : Writes 1 word to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAMWord(u16 RGB_Code)
{
  LCD_WriteRAM_Prepare();

  LCD_WriteRAM(RGB_Code);
  
  LCD_WriteRAM_Ready();
}

/*******************************************************************************
* Function Name  : LCD_PowerOn
* Description    : Power on the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PowerOn(void)
{

}

/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{

}

/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{

}											

/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD control lines in Output Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE); 
						 
/*===========GPIO For the LCD_Bus========================*/	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
  								GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
  								GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

/*===========GPIO For the LCD_RESET=======================*/
/**	
 *	PC1 -> LCD_RESET
 */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

/*===========GPIO For the Control========================*/
/**	
 *	PD13 -> Light
 *	PD4	-> OE	,	PD5	-> WE 
 *	PD7	-> CS	,	PD11 -> RS 
 */	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 
  GPIO_Init(GPIOD, &GPIO_InitStructure); 

/*===========GPIO For the LED ========================*/
/**
 *	LED1 -> PB8	,	LED2 -> PB9 , LED3 -> PE0 , LED4 -> PE1
 */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);	
/*===========Please Set LED-back-Light ========================*/
/**
 *	Light_LED -> PD13
 */

  GPIO_SetBits(GPIOD, GPIO_Pin_13);		//打开背光LED
}


/**
 * LCD地址设置
 *
 */

void address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
    LCD_WriteReg(0x0020,x1);//设置X坐标位置	地址计数器初始值x
    LCD_WriteReg(0x0021,y1);//设置Y坐标位置	地址计数器初始值y
    LCD_WriteReg(0x0050,x1);   //开始X
	LCD_WriteReg(0x0052,y1);	  //开始Y
    LCD_WriteReg(0x0051,x2);  //结束X
	LCD_WriteReg(0x0053,y2);  //结束Y
    LCD_WriteRAM_Prepare();	 //	写数据准备
}


/*---------------------------------------------------------------*/

 void lcd_wr_zf(unsigned int a, unsigned int b, unsigned int a1, unsigned int b1, unsigned int d,unsigned int e,unsigned char g,unsigned char *f)    
// X， Y，结束X，y,尺寸，颜色，方向，数据
{   
	

	unsigned int temp=0,num,z,R_dis_mem=0,a2=0,b2=0,b3=0;
	unsigned char temp5;

	if(g==0) LCD_WriteReg(0x0003,0x1030);		 //左上起
	else if(g==1) LCD_WriteReg(0x0003,0x1018);   //左下起
	else if(g==2) LCD_WriteReg(0x0003,0x1010);   //右下起
	else if(g==3) LCD_WriteReg(0x0003,0x1028);   //右上起
	//LCD_WriteReg(0x01,0x07);  
	Delay(200); 
	for(temp=0;temp<d;temp++)
	{
	   b2=(temp*8);
	   b3=b2/(a1-a+1);	    //计算纵坐标偏移
	   a2=b2%(a1-a+1);	    //计算横坐标偏移
	   temp5=*f;
	   z=temp5;
	   for(num=0; num<8; num++){		    
		  if((temp5&0x80)>0){			  	
		  	if(g==0){
				LCD_WriteReg(80,a+a2+num);
	 			LCD_WriteReg(82,b+b3);  

				LCD_WriteReg(81,a+a2+num);
	 			LCD_WriteReg(83,b+b3);  
				LCD_WriteReg(32, a+a2+num);
    			LCD_WriteReg(33, b+b3);
	 			//LCD_WriteReg(0,0x04,239);
	  			//LCD_WriteReg(1,0x05,319);
			}
			else if(g==1){ 

                

				LCD_WriteReg(80,b+b3);
	  			LCD_WriteReg(82,a);
				LCD_WriteReg(81,b+b3);	
				LCD_WriteReg(83,319-(a+a2+num));
				//LCD_WriteReg(83,a);
				LCD_WriteReg(32,b+b3);
	  			LCD_WriteReg(33,319-(a+a2+num));		 			
			}
			else if(g==2){ 
				LCD_WriteReg(80,a);
	 			LCD_WriteReg(82,b);  
	 			LCD_WriteReg(81,239-(a+a2+num));
	  			LCD_WriteReg(83,319-(b+b3));
				LCD_WriteReg(32,239-(a+a2+num));
	  			LCD_WriteReg(33,319-(b+b3));
			
			}
			else if(g==3){ 
				LCD_WriteReg(80,239-(b+b3));
	  			LCD_WriteReg(82,(a+a2+num));
				LCD_WriteReg(81,239-(b+b3));	
				LCD_WriteReg(83,319);	
				LCD_WriteReg(32,239-(b+b3));
	  			LCD_WriteReg(33,(a+a2+num));			
			}
	   		LCD_WriteIndex(34); 
			LCD_WriteRAM(e); 
		  }
		  else{
		   
	
			if(g==0){
				LCD_WriteReg(80,a+a2+num);
				LCD_WriteReg(82,b+b3);
				LCD_WriteReg(81,a+a2+num);
	 			LCD_WriteReg(83,b+b3);  
				LCD_WriteReg(32, a+a2+num);
    			LCD_WriteReg(33, b+b3);
				LCD_WriteIndex(34);				
		  		R_dis_mem=LCD_RD_Data();		  		
				LCD_WriteReg(32,a+a2+num);
				LCD_WriteReg(33,b+b3);
			}
			else if(g==1){


               

				LCD_WriteReg(80,b+b3);
	  			LCD_WriteReg(82,a);
				LCD_WriteReg(81,b+b3);	
				LCD_WriteReg(83,319-(a+a2+num));
				
				LCD_WriteReg(32,b+b3);
	  			LCD_WriteReg(33,319-(a+a2+num));
				LCD_WriteIndex(34);				
		  		R_dis_mem=LCD_RD_Data();		  		
				LCD_WriteReg(32,b+b3);
	  			LCD_WriteReg(33,319-(a+a2+num));
				//LCD_WriteReg(0,0x04,b+b3);	
				//LCD_WriteReg(1,0x05,319-(a+a2+num));	
			}
			else if(g==2){
				LCD_WriteReg(80,a);
	 			LCD_WriteReg(82,b);  
	 			LCD_WriteReg(81,239-(a+a2+num));
	  			LCD_WriteReg(83,319-(b+b3));
				LCD_WriteReg(32,239-(a+a2+num));
	  			LCD_WriteReg(33,319-(b+b3));
				LCD_WriteIndex(34);				
		  		R_dis_mem=LCD_RD_Data();		  		
				LCD_WriteReg(32,239-(a+a2+num));
	  			LCD_WriteReg(33,319-(b+b3));
	 			//LCD_WriteReg(0,0x04,239-(a+a2+num));
	  			//LCD_WriteReg(1,0x05,319-(b+b3));
			}
			else if(g==3){
				LCD_WriteReg(80,239-(b+b3));
	  			LCD_WriteReg(82,(a+a2+num));
				LCD_WriteReg(81,239-(b+b3));	
				LCD_WriteReg(83,319);		 
				LCD_WriteReg(32,239-(b+b3));
	  			LCD_WriteReg(33,(a+a2+num));
				LCD_WriteIndex(34);				
		  		R_dis_mem=LCD_RD_Data();		  		
				LCD_WriteReg(80,239-(b+b3));
	  			LCD_WriteReg(82,(a+a2+num));
				//LCD_WriteReg(0,0x04,239-(b+b3));	
				//LCD_WriteReg(1,0x05,319);		 
			}

			LCD_WriteIndex(34); 					
			LCD_WriteRAM(R_dis_mem);	 			
		  }
		  temp5=z;
		  temp5=temp5<<1; 
		  z=temp5;
		  	
	   }
	   f++;
	}
}
//8888888888888888888888888888888888888888888888888888888888888888888888888888
/*
extern void LCD_WriteIndex(unsigned char index);
extern void LCD_WriteReg(unsigned int index,unsigned int val);
extern unsigned int LCD_RD_data(void);
extern void LCD_WriteRAM(unsigned int val);
unsigned int LCD_RD_Data(void);
extern void LCD_clear(unsigned int p);
extern void LCD_9325_Init(void);
extern void lcd_wr_zf(unsigned int a, unsigned int b, unsigned int a1,unsigned int b1, unsigned int d,unsigned int e, unsigned char g, unsigned char *f); 
extern void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e) ;
extern unsigned char *num_pub(unsigned int a);

*/

/****************************************************************************
* 名    称：void ili9320_SetCursor(u16 x,u16 y)
* 功    能：设置屏幕座标
* 入口参数：x      行座标
*           y      列座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetCursor(10,10);
****************************************************************************/
void ili9320_SetCursor(u16 x,u16 y)
{				
  LCD_WriteReg(32, y);
  LCD_WriteReg(33, x);
}

/****************************************************************************
* 名    称：void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
* 功    能：设置窗口区域
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetWindows(0,0,100,100)；
****************************************************************************/
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
  LCD_WriteReg(0x0050, StartY); // Horizontal GRAM Start Address
  LCD_WriteReg(0x0051, EndX); // Horizontal GRAM End Address
  LCD_WriteReg(0x0052, StartX); // Vertical GRAM Start Address
  LCD_WriteReg(0x0053, EndY); // Vertical GRAM Start Address	  
}

/****************************************************************************
* 名    称：void ili9320_Clear(u16 dat)
* 功    能：将屏幕填充成指定的颜色，如清屏，则填充 0xffff
* 入口参数：dat      填充值
* 出口参数：无
* 说    明：
* 调用方法：ili9320_Clear(0xffff);
****************************************************************************/
void ili9320_Clear(u16 dat)
{
  u32 i;
  LCD_WriteReg(0x0050, 0); // Horizontal GRAM Start Address
  LCD_WriteReg(0x0051, 239); // Horizontal GRAM End Address
  LCD_WriteReg(0x0052, 0); // Vertical GRAM Start Address
  LCD_WriteReg(0x0053, 319); // Vertical GRAM Start Address	 
  LCD_WriteReg(32, 0);
  LCD_WriteReg(33, 0);
  LCD_WriteIndex(34);
  for(i=0;i<76800;i++) LCD_WriteRAM(dat);  
}

/****************************************************************************
* 名    称：u16 ili9320_GetPoint(u16 x,u16 y)
* 功    能：获取指定座标的颜色值
* 入口参数：x      行座标
*           y      列座标
* 出口参数：当前座标颜色值
* 说    明：
* 调用方法：i=ili9320_GetPoint(10,10);
****************************************************************************/
/*u16 ili9320_GetPoint(u16 x,u16 y)
{ 
  	ili9320_SetCursor(x,y);
  	LCD_WriteIndex(34);
  	return (ili9320_BGR2RGB(ili9320_ReadData()));
}  */

/****************************************************************************
* 名    称：void ili9320_SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
  LCD_WriteReg(32, y);
  LCD_WriteReg(33, x);
  LCD_WriteIndex(34);
  LCD_WriteRAM(point);  
}

/****************************************************************************
* 名    称：void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
* 调用方法：ili9320_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u16  i;
  ili9320_SetWindows(StartX,StartY,EndX,EndY);
  ili9320_SetCursor(StartX,StartY);	    
  for (i=0;i<(EndX*EndY);i++) LCD_WriteRAM(*pic++);
}

/****************************************************************************
* 名    称：void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* 功    能：在指定座标显示一个8x16点阵的ascii字符
* 入口参数：x          行座标
*           y          列座标
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示范围限定为可显示的ascii码
* 调用方法：ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  u8 tmp_char=0;
  		
	for (i=0;i<16;i++)
	{
		    tmp_char=ascii_8x16[((c-0x20)*16)+i];
		    for (j=0;j<8;j++)
		    {
		      if ( (tmp_char >> 7-j) & 0x01 == 0x01)
		        {
		          ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色
		        }
		        else
		        {
		          ili9320_SetPoint(x+j,y+i,bkColor); // 背景颜色/
		        }
		    }
	}
   
}
/** 
* @brief put chars size 33 * 16 to LCD
* @author 
* 
* @param x
* @param y
* @param z
* @param len
* @param charColor
* @param bkColor
*/
void ili9320_PutChars_S3316(u16 x,u16 y,u8 *z,u8 len,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  u8 kk = 0;
  u16 w=0;
  u8 c=0;
  unsigned int dd;
  u8 tmp_char=0;
  address_set(0,0,239,319);
  for (w=0;w<len;w++)
  {
	c=*z;
	z=z++;
  		for (i=0;i<33;i++)
		  {
		    
			for(kk = 0; kk<2;kk++)
			{
				if(c == '-')
						tmp_char=ASCII_Km[10*66+kk+2*i];
			//	else if(c == ' ')
					//	tmp_char=ASCII_Km[11*66+kk+2*i];
				

				else  tmp_char=ASCII_Km[(c-'0')*66+kk+2*i];
				
							
			    for (j=0;j<8;j++)
			    {
			      if ( (tmp_char >> 7-j) & 0x01 == 0x01)
			        {
			          ili9320_SetPoint(x+j+kk*8,y+i,charColor); // 字符颜色
	
			        }
			        else
			        {
			           //ili9320_SetPoint(x+j+kk*8,y+i,bkColor); // 背景颜色/

				
						dd=(0x00|gImage_x[((x+j+kk*8)+(y+i)*320)*2+1])<<8;
						dd=dd|gImage_x[((x+j+kk*8)+(y+i)*320)*2];
						
					
		          		ili9320_SetPoint(x+j+kk*8,y+i,dd); // 背景颜色/
	
			        }
			    }	 
				}
		  }
		  x=x+16;
   }
}


/****************************************************************************
* 名    称：void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
* 功    能：在指定座标显示一个8x16点阵的ascii字符串
* 入口参数：x          行座标
*           y          列座标
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示范围限定为可显示的ascii码
* 调用方法：ili9320_PutChar(10,10,'a',0x0000,0xffff);
****************************************************************************/
void ili9320_PutChars_S816(u16 x,u16 y,uc8 *z,u8 len,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  u16 w=0;
  u8 c=0;
  u8 tmp_char=0;
  address_set(0,0,239,319);
  for (w=0;w<len;w++)
  {
	c=*z;
	z=z++;
  		for (i=0;i<16;i++)
		  {
		    tmp_char=ascii_8x16[((c-0x20)*16)+i];
		    for (j=0;j<8;j++)
		    {
		      if ( (tmp_char >> 7-j) & 0x01 == 0x01)
		        {
		          ili9320_SetPoint(x+j,y+i,charColor); // 字符颜色

		        }
		        else
		        {
		          ili9320_SetPoint(x+j,y+i,bkColor); // 背景颜色/

		        }
		    }
		  }
		  	x=x+8;
   }
}

/** 
* @brief put chars size 32 * 64 to LCD
* 
* @author 
* @param x
* @param y
* @param z
* @param len
* @param charColor
* @param bkColor
*/
void ili9320_PutChars_S3264(u16 x,u16 y,char *z,u8 len,u16 charColor,u16 bkColor)
{
      u16 i=0;
      u16 j=0;
      u8 kk = 0;
      u16 w=0;
      u8 c=0;
      unsigned int dd;
      u8 tmp_char=0;
      address_set(0,0,239,319);
      for (w=0;w<len;w++)
      {
        c=*z;
        z=z++;
        for (i=0;i<64;i++)
        {
            for(kk = 0; kk<4;kk++)
            {
                if(c-'0'==-2)
                    tmp_char=ASCII_Data[(11*256)+kk+4*i];
                else if(c - '0' == -16)
                    tmp_char=ASCII_Data[(12*256)+kk+4*i];

                else
                    tmp_char=ASCII_Data[((c-'0')*256)+kk+4*i];
                for (j=0;j<8;j++)
                {
                  if ( (tmp_char >> 7-j) & 0x01 == 0x01)
                    {
                      ili9320_SetPoint(x+j+kk*8,y+i,charColor); // 字符颜色
                    }
                    else
                    {
                        dd=(0x00|gImage_x[((x+j+kk*8)+(y+i)*320)*2+1])<<8;
                        dd=dd|gImage_x[((x+j+kk*8)+(y+i)*320)*2];
                        ili9320_SetPoint(x+j+kk*8,y+i,dd); 
                    }
                }
            }
        }
        x=x+32;
       }
}

/****************************************************************************
* 名    称：void ili9320_Test()
* 功    能：测试液晶屏
* 入口参数：无
* 出口参数：无
* 说    明：显示彩条，测试液晶屏是否正常工作
* 调用方法：ili9320_Test();
****************************************************************************/
void ili9320_Test()
{
  u16 i,j;
  address_set(0,0,239,319);
  for(i=0;i<320;i++)
    for(j=0;j<240;j++)
    {
      if(i>279)LCD_WriteRAM(0x0000);
      else if(i>239)LCD_WriteRAM(0x001f);
      else if(i>199)LCD_WriteRAM(0x07e0);
      else if(i>159)LCD_WriteRAM(0x07ff);
      else if(i>119)LCD_WriteRAM(0xf800);
      else if(i>79)LCD_WriteRAM(0xf81f);
      else if(i>39)LCD_WriteRAM(0xffe0);
      else LCD_WriteRAM(0xffff);
    }
  
}

/****************************************************************************
* 名    称：u16 ili9320_BGR2RGB(u16 c)
* 功    能：RRRRRGGGGGGBBBBB 改为 BBBBBGGGGGGRRRRR 格式
* 入口参数：c      BRG 颜色值
* 出口参数：RGB 颜色值
* 说    明：内部函数调用
* 调用方法：
****************************************************************************/
/*u16 ili9320_BGR2RGB(u16 c)
{
  u16  r, g, b;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  return( (b<<11) + (g<<5) + (r<<0) );
}	*/

/****************************************************************************
* 名    称：void ili9320_WriteIndex(u16 idx)
* 功    能：写 ili9320 控制器寄存器地址
* 入口参数：idx   寄存器地址
* 出口参数：无
* 说    明：调用前需先选中控制器，内部函数
* 调用方法：ili9320_WriteIndex(0x0000);
****************************************************************************/
void ili9320_WriteIndex(u16 idx)
{
  LCD_WriteIndex(idx);
}

/****************************************************************************
* 名    称：void ili9320_WriteData(u16 dat)
* 功    能：写 ili9320 寄存器数据
* 入口参数：dat     寄存器数据
* 出口参数：无
* 说    明：向控制器指定地址写入数据，调用前需先写寄存器地址，内部函数
* 调用方法：ili9320_WriteData(0x1030)
****************************************************************************/
void ili9320_WriteData(u16 dat)
{
  LCD_WriteRAM(dat);
}

/****************************************************************************
* 名    称：u16 ili9320_ReadData(void)
* 功    能：读取控制器数据
* 入口参数：无
* 出口参数：返回读取到的数据
* 说    明：内部函数
* 调用方法：i=ili9320_ReadData();
****************************************************************************/
/*u16 ili9320_ReadData(void)
{
  u16 val=0;
  val=LCD_RD_Data();
  return val;
}
*/
/****************************************************************************
* 名    称：u16 ili9320_ReadRegister(u16 index)
* 功    能：读取指定地址寄存器的值
* 入口参数：index    寄存器地址
* 出口参数：寄存器值
* 说    明：内部函数
* 调用方法：i=ili9320_ReadRegister(0x0022);
****************************************************************************/
u16 ili9320_ReadRegister(u16 index)
{
  u16 tmp;
  tmp= *(volatile unsigned int *)(0x60000000);
  
  return tmp;
}
/** 
* @brief Put chars size 56 * 64 to the LCD
* 
* @author 姚明月
* @param x
* @param y
* @param z
* @param id
* @param charColor
* @param bkColor
*/
void ili9320_PutCharz_S5664(u16 x,u16 y,u8 z,u8 id,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  u16 kk=0;
  u16 tmp_char=0;
  unsigned int dd;
  uc16  *hz;
  hz=&ASCII_Wel[id*448];
  
  while(z--)
  {
		for (i=0;i<56;i++)
	    {
		  	for(kk=0;kk<8;kk++)
			{
				tmp_char=*hz;
			    for (j=0;j<8;j++)
			    {
			      if ( (tmp_char >>7-j) & 0x01 == 0x01)
			        {
			          ili9320_SetPoint(x+j+kk*8,y+i,charColor); // 字符颜色
			        }
			        else
			        {
						dd=(0x00|gImage_x[((x+j+kk*8)+(y+i)*320)*2+1])<<8;
						dd=dd|gImage_x[((x+j+kk*8)+(y+i)*320)*2];
		          		ili9320_SetPoint(x+j+kk*8,y+i,dd); 
					}
			    }
				hz=hz++;
			}
	   }
	   x=x+64;
    }
}
/** 
* @brief put char size 40 * 35 to the LCD
* 
* @author 李小龙
* @param x
* @param y
* @param z
* @param id
* @param charColor
* @param bkColor
*/
void ili9320_PutCharz_S4035(u16 x,u16 y,u8 z,u8 id,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  u16 kk=0;
  u16 tmp_char=0;
  unsigned int dd;
  uc16  *hz;
  hz=&ASCII_Safe[id*175];
  
  while(z--)
  {
 
		for (i=0;i<35;i++)
	    {
		  	for(kk=0;kk<5;kk++)
			{
				tmp_char=*hz;
			    for (j=0;j<8;j++)
			    {
			      if ( (tmp_char >>7-j) & 0x01 == 0x01)
			        {
			          ili9320_SetPoint(x+j+kk*8,y+i,charColor); // 字符颜色
			        }
			        else
			        {
						dd=(0x00|gImage_x[((x+j+kk*8)+(y+i)*320)*2+1])<<8;
						dd=dd|gImage_x[((x+j+kk*8)+(y+i)*320)*2];
		          		ili9320_SetPoint(x+j+kk*8,y+i,dd); 
					}
			    }
				hz=hz++;
			}
	       
	   }
	   x=x+40;
    }

}
/** 
* @brief put chars to the LCD
* 
* @author 高金龙
* @param x x postion
* @param y y postion
* @param z length of the chars
* @param id id
* @param charColor front color
* @param bkColor back color
*/
void ili9320_PutCharz(u16 x,u16 y,u8 z,u8 id,u16 charColor,u16 bkColor)
{
  u16 i=0;
  u16 j=0;
  u16 kk=0;
  u16 tmp_char=0;
  unsigned int dd;
  uc16  *hz;
  hz=&ASCII_Table[id*128];
  while(z--)
  {
		for (i=0;i<33;i++)
	    {
		  	for(kk=0;kk<4;kk++)
			{
				tmp_char=*hz;
			    for (j=0;j<8;j++)
			    {
			      if ( (tmp_char >>7-j) & 0x01 == 0x01)
			        {
			          ili9320_SetPoint(x+j+kk*8,y+i,charColor);
			        }
			        else
			        {
						dd=(0x00|gImage_x[((x+j+kk*8)+(y+i)*320)*2+1])<<8;
						dd=dd|gImage_x[((x+j+kk*8)+(y+i)*320)*2];
		          		ili9320_SetPoint(x+j+kk*8,y+i,dd); 
					}
			    }
				hz=hz++;
			}
	       
	   }
	   x=x+32;
    }

}
/** 
* @brief print KM to the LCD
* 
* @author: 范振平
* @param x x position
* @param y y position
* @param charColor color of the char
* @param bkColor   backcolor of the char
*/
void ili9320_Put_Km(u16 x,u16 y,u16 charColor,u16 bkColor)
{
     u16 i=0;
     u16 j=0;
     u16 kk=0;
     u8 z = 2;
     u16 tmp_char=0;
     unsigned int dd;
     uc16  *hz;
     hz=ASCII_km;
     address_set(0,0,239,319);
     while(z--)
     {
        for (i=0;i<33;i++)
        {
            for(kk=0;kk<2;kk++)
            {
                tmp_char=*hz;
                for (j=0;j<8;j++)
                {
                  if ( (tmp_char >>7-j) & 0x01 == 0x01)
                    {
                      ili9320_SetPoint(x+j+kk*8,y+i,charColor);
                    }
                    else
                    {
                        dd=(0x00|gImage_x[((x+j+kk*8)+(y+i)*320)*2+1])<<8;
                        dd=dd|gImage_x[((x+j+kk*8)+(y+i)*320)*2];
                        ili9320_SetPoint(x+j+kk*8,y+i,dd); 
                    }
                }
                hz=hz++;
            }
       }
       x=x+16;
     }
}


/** 
* @brief calculate the passager should pay
* 
* @author 姚明月 
* @param distance distance during the way
* @param wait_time total waittime
* @param day day or night
* @return the money should pay
*/
int cal_money(float distance,long wait_time, u8 day)
{
    float money;
	int mm;
    wait_time = wait_time / 300;
    distance = distance + wait_time;
    if(day)
    {
       money = distance < 3 ? 10 : (distance - 3) * 2 + 10 ; 
       if(distance > 15)
       money = money + (distance - 15) * 1;
      
    }
    else
    {
       money = distance < 3 ? 11 : (distance - 3) * 2.4 + 11 ; 
       if(distance > 15)
           money = money + (distance - 15) * 1.2;
      
    }
	 mm = money*10;
	 return mm;
}

/** 
* @brief Startup LOGO
*
* @author 李小龙
*/
void Logo(void)
{
		u32 i;
		unsigned int dd;
		address_set(0,0,239,319);
		for(i=0;i<76800;i++)
		{
			dd=(0x00|gImage_x[i*2+1])<<8;
			dd=dd|gImage_x[i*2];
			LCD_WriteRAM(dd);	
		}
}
void Wel_Logo(void)
{
	
		Logo();
		ili9320_PutCharz_S5664(30,30,4,0,Red,Green);
		ili9320_PutCharz_S4035(60,150,6,0,Red,Green);
	
}
extern void RTC_GO(void);

/** 
* @brief Display Function
*
* @author 李小龙
*/
void test(void)
{
 	unsigned char tab_time[8]="22:12:24";
 	unsigned char tab_date[11]="4011-1-10";
	unsigned char tab_wait_time[5]="00-00";
    char tab_speedsize[1]="2";
	int speedd;

 	Logo();
	ili9320_PutCharz(60,20,2,0,Red,Green);	//历程
	ili9320_PutCharz(60,20+32+20+10,2,2,Red,Green);	//经俄
	ili9320_Put_Km(60+32*7,20,Red,Green);  //km

	ili9320_PutChars_S3264(60+32*5,64,tab_fee_float,2,Red,Green); //.0
	ili9320_PutCharz(60+32*7,20+32+20+10,1,4,Red,Green);	  //元
	
	sprintf(tab_date,"20%02d-%02d-%02d",11,1,10);
	while(key1 == 1)
	{
        RTC_GO();
        if(key1 ==1)
        {
            money=cal_money(distance,wait_time,1);
            
            sprintf(tab_distance_calc,"%5.1f",(double)distance);
	}
	ili9320_PutChars_S3264(60+32*2,0,tab_distance_calc,5,Red,Green);	 //licheng
 
	sprintf(tab_fee_calc,"%3d",money/10);
	ili9320_PutChars_S3264(60+32*2,64,tab_fee_calc,3,Red,Green);// jine
	
	sprintf(tab_wait_time,"%02d-%02d",wait_time/3600,wait_time/60);
	ili9320_PutChars_S3316(200,200,tab_wait_time,5,Red,Green);//dengdai
	
	speedd = speed;
	sprintf(tab_speedsize,"%d",key2);
	ili9320_PutChars_S3264(50,150,tab_speedsize,1,Red,Green);	 //speed

	sprintf(tab_time,"%02d-%02d-%02d",THH,TMM,TSS);
		  
	ili9320_PutChars_S3316(180,128,tab_time,8,Red,Green); //time
	ili9320_PutChars_S3316(145,160,tab_date,10,Red,Green); //date

	}
}
/*---------------------------------E N D--------------------------------------*/


