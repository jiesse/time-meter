/**
  @page RTC_Calendar RTC_Calendar
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file RTC/Calendar/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the RTC Calendar Example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Example Description 

This example demonstrates and explains how to use the RTC peripheral. 
As an application example, it demonstrates how to setup the RTC peripheral, in terms
of prescaler and interrupts, to be used to keep time and to generate Second interrupt. 

The Low Speed External (LSE) clock is used as RTC clock source. 
The RTC clock can be output on the Tamper pin (PC.13). To enable this functionality,
uncomment the corresponding line: #define RTCClockOutput_Enable in the main.c file.

The RTC is in the backup (BKP) domain, still powered by VBAT when VDD is switched off,
so the RTC configuration is not lost if a battery is connected to the VBAT pin. 
A key value is written in backup data register1 (BKP_DR1) to indicate if the RTC
is already configured.

The program behaves as follows:

1. After startup the program checks the backup data register1 value:
    - register1 value not correct: (BKP_DR1 value is not correct or has not yet
      been programmed when the program is executed for the first time) the RTC is
      configured and the user is asked to set the time (entered on HyperTerminal).
    
    - register1 value correct: this means that the RTC is configured and the time
      is displayed on HyperTerminal.

2. When an External Reset occurs the BKP domain is not reset and the RTC configuration
   is not lost.

3. When power on reset occurs:
    - If a battery is connected to the VBAT pin: the BKP domain is not reset and
      the RTC configuration is not lost.
      
    - If no battery is connected to the VBAT pin: the BKP domain is reset and the
      RTC configuration is lost.

In the RTC interrupt service routine, a specific GPIO pin toggles every 1 s.
The C library printf function is retargeted to the USART1, that is, the printf
message is output to the HyperTerminal using USART1.

 
@par Directory contents 

  - RTC/Calendar/platform_config.h    Evaluation board specific configuration file
  - RTC/Calendar/stm32f10x_conf.h     Library Configuration file
  - RTC/Calendar/stm32f10x_it.c       Interrupt handlers
  - RTC/Calendar/stm32f10x_it.h       Header for stm32f10x_it.c
  - RTC/Calendar/main.c               Main program

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    and can be easily tailored to any other supported device and development 
    board.
    To select the STMicroelectronics evaluation board used to run the example, 
    uncomment the corresponding line in platform_config.h file.
    
  - STM3210E-EVAL Set-up 
    - Use LD1 led connected to PF.06.
    - The USART1 signals (Rx, Tx) must be connected to a DB9 connector using a RS232
       transceiver.
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
       (CN12 on STM3210B-EVAL board) and PC serial port. 
    - Hyperterminal configuration:
       - Word Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - flow control: None
    - Connect a 3V battery on Vbat pin (already mounted on STM3210E-EVAL board)
    
  - STM3210B-EVAL Set-up   
    - Use LD1 led connected to PC.06.
    - The USART1 signals (Rx, Tx) must be connected to a DB9 connector using a RS232
       transceiver.
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
       (CN6 on STM3210B-EVAL board) and PC serial port.
    - Hyperterminal configuration:
       - Word Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - flow control: None
    - Connect a 3V battery on Vbat pin (already mounted on STM3210B-EVAL board)   
       
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
  - stm32f10x_rtc.c 
  - stm32f10x_bkp.c 
  - stm32f10x_pwr.c 
  - misc.c 
  - stm32f10x_usart.c
  - system_stm32f10x.c 
      
- Edit stm32f10x.h file to select the device you are working on.
  
@b Tip: You can tailor the provided project template to run this example, for 
        more details please refer to "stm32f10x_stdperiph_lib_um.chm" user 
        manual; select "Peripheral Examples" then follow the instructions 
        provided in "How to proceed" section.   
- Link all compiled files and load your image into target memory
- Run the example

@note
 - Low-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 16 and 32 Kbytes.
 - Medium-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 32 and 128 Kbytes.
 - High-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.
   
 * <h3><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h3>
 */
