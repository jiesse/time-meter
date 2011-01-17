
/**
 ***********************************************
 * LCD为带触摸，2.4寸液晶屏，驱动IC为ILI9325   *
 * 9325的资料很多，光盘里有9325的指令中文版    *
 * *********************************************
 */


#include "fsmc_sram.h"
#include "lcdconf.h"
														 
unsigned long color1=0;						
void LCD_9325_Init(void);
void LCD_WriteIndex(unsigned int index);
void LCD_WriteReg(unsigned int index,unsigned int val);

void LCD_WriteRAM(unsigned int val);
void LCD_clear(unsigned int p);
void ini(void);
void Delay(volatile uint32_t nCount);
void lcd_wr_zf(unsigned int a, unsigned int b, unsigned int a1,unsigned int b1, unsigned int d,unsigned int e, unsigned char g, unsigned char *f); 
void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e) ;
unsigned char *num_pub(unsigned int a);

unsigned int color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};

unsigned int LCD_RD_Data(void);
extern void Delay(volatile uint32_t nCount);

/**
 * 写寄存器地址
 */
void LCD_WriteIndex(unsigned int index)
{
	*(volatile uint16_t *) (LCD_Reg_Addr)= index;
}

/**
 * 写数据准备
 */
void LCD_WriteRAM_Prepare(void)   
{
	LCD_WriteIndex(0x022);
}

/**
 * 写数据完成
 */
#define  LCD_WriteRAM_Ready() {LCD_CS;}


/**
 * 写寄存器函数
 */
void LCD_WriteReg(unsigned int LCD_Reg, unsigned int LCD_RegValue)
{	
	//LCD_nCS;
	*(volatile uint16_t *) (LCD_Reg_Addr) = LCD_Reg;
	*(volatile uint16_t *) (LCD_Data_Addr) = LCD_RegValue;
	//LCD_CS;
}


/**
 * 写数据函数
 */
void LCD_WriteRAM(unsigned int val)
{   
	*(volatile uint16_t *) (LCD_Data_Addr)= val; 	
}

/**
 * 读数据函数
 */
unsigned int LCD_RD_Data(void)
{
	unsigned int temp,i=0;

	for(; i < 1; i++){
		temp = (*(volatile uint16_t *) (LCD_Data_Addr)); 
	}
	return( temp );	
}


/**
 * 延迟函数
 */
void Delay(volatile uint32_t Count)
{
	int i;
  for(i = 0; i < Count; i++);
}


/**
 * LCD TFT 9325 Init函数
 */
void LCD_9325_Init(void)
{
    GPIO_SetBits(GPIOC, GPIO_Pin_1 );			 
	Delay(0xAFFF);
    GPIO_ResetBits(GPIOC, GPIO_Pin_1);
    Delay(0xAFFF);					   
    GPIO_SetBits(GPIOC, GPIO_Pin_1 );			 
	Delay(0xAFFF);
		
	LCD_WriteReg(0x00E3, 0x3008); // Set internal timing
	LCD_WriteReg(0x00E7, 0x0012); // Set internal timing
	LCD_WriteReg(0x00EF, 0x1231); // Set internal timing
	LCD_WriteReg(0x0000, 0x0001); // Start Oscillation
	LCD_WriteReg(0x0001, 0x0100); // set SS and SM bit			 ****
	LCD_WriteReg(0x0002, 0x0700); // set 1 line inversion		 ****

	LCD_WriteReg(0x0003, 0x1030); // set GRAM write direction and BGR=0,262K colors,1 transfers/pixel.
	LCD_WriteReg(0x0004, 0x0000); // Resize register
	LCD_WriteReg(0x0008, 0x0202); // set the back porch and front porch
	LCD_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
	LCD_WriteReg(0x000A, 0x0000); // FMARK function
	LCD_WriteReg(0x000C, 0x0000); // RGB interface setting
	LCD_WriteReg(0x000D, 0x0000); // Frame marker Position
	LCD_WriteReg(0x000F, 0x0000); // RGB interface polarity
  
	LCD_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
	LCD_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	Delay(200);  
	LCD_WriteReg(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(0x0011, 0x0227); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	Delay(50);  
	LCD_WriteReg(0x0012, 0x001C); // External reference voltage= Vci;
	Delay(50);  
	LCD_WriteReg(0x0013, 0x1800); // R13=1200 when R12=009D;VDV[4:0] for VCOM amplitude
	LCD_WriteReg(0x0029, 0x001C); // R29=000C when R12=009D;VCM[5:0] for VCOMH
	LCD_WriteReg(0x002B, 0x000D); // Frame Rate = 91Hz
	Delay(50);  
	LCD_WriteReg(0x0020, 0x0000); // GRAM horizontal Address
	LCD_WriteReg(0x0021, 0x0000); // GRAM Vertical Address
 //
	LCD_WriteReg(0x0030, 0x0007);
	LCD_WriteReg(0x0031, 0x0302);
	LCD_WriteReg(0x0032, 0x0105);
	LCD_WriteReg(0x0035, 0x0206);
	LCD_WriteReg(0x0036, 0x0808);
	LCD_WriteReg(0x0037, 0x0206);
	LCD_WriteReg(0x0038, 0x0504);
	LCD_WriteReg(0x0039, 0x0007);
	LCD_WriteReg(0x003C, 0x0105);
	LCD_WriteReg(0x003D, 0x0808);
 //
	LCD_WriteReg(0x0050, 0x0000); // Horizontal GRAM Start Address
	LCD_WriteReg(0x0051, 0x00EF); // Horizontal GRAM End Address
	LCD_WriteReg(0x0052, 0x0000); // Vertical GRAM Start Address
	LCD_WriteReg(0x0053, 0x013F); // Vertical GRAM Start Address
	LCD_WriteReg(0x0060, 0xA700); // Gate Scan Line
	LCD_WriteReg(0x0061, 0x0001); // NDL,VLE, REV
	LCD_WriteReg(0x006A, 0x0000); // set scrolling line
 
	LCD_WriteReg(0x0080, 0x0000);
	LCD_WriteReg(0x0081, 0x0000);
	LCD_WriteReg(0x0082, 0x0000);
	LCD_WriteReg(0x0083, 0x0000);
	LCD_WriteReg(0x0084, 0x0000);
	LCD_WriteReg(0x0085, 0x0000);
 
	LCD_WriteReg(0x0090, 0x0010);
	LCD_WriteReg(0x0092, 0x0000);
	LCD_WriteReg(0x0093, 0x0003);
	LCD_WriteReg(0x0095, 0x0110);
	LCD_WriteReg(0x0097, 0x0000);
	LCD_WriteReg(0x0098, 0x0000);
	LCD_WriteReg(0x0007, 0x0133); // 262K color and display ON	
}


/**
 * 功能：LCD写字符子程序
 * @x_start：
 * @y_start：
 * @x_end:
 * @y_end:
 * @ 尺寸
 * @ 颜色
 * @方向
 * @数据
 */
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

/**
 * LCD写字符子程序
 */
void lcd_wr_pixel(unsigned int a, unsigned int b, unsigned int e)    
// X， Y，颜色
{
	LCD_WriteReg(0x20, a);
    LCD_WriteReg(0x21, b);
	LCD_WriteRAM(e);
}



/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
