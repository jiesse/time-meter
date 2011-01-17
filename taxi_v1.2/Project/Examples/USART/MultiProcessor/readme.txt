/**
  @page USART_MultiProcessor USART_MultiProcessor
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file USART/MultiProcessor/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the USART Multi Processor Example.
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

This example provides a description of how to use the USART in multi-processor mode.
First, the USART1 and USART2 address are set to 0x1 and 0x2. The USART1 send 
continusouly the character 0x33 to the USART2. The USART2 toggle LD1, LD2, LD3 
and LD4 pins while receiving 0x33.

When a falling edge is applied on Key Button EXTI line, an interrupt is generated
and in the EXTI9_5_IRQHandler routine, the USART2 is entred in mute mode and still
in this mode (no LED toggling) until a rising edge is applied on EXTI Line 0.
In this interrupt routine the USART1 send the character of address mark (0x102)
to wakeup USART2. The LED restart toggling.

USART1 and USART2 configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 9 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled

@par Directory contents 

  - USART/MultiProcessor/platform_config.h    Evaluation board specific configuration file
  - USART/MultiProcessor/stm32f10x_conf.h     Library Configuration file
  - USART/MultiProcessor/stm32f10x_it.h       Interrupt handlers header file
  - USART/MultiProcessor/stm32f10x_it.c       Interrupt handlers
  - USART/MultiProcessor/main.c               Main program

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
    - Connect a null-modem female/female RS232 cable between CN12 and CN8.
    - Use Key push-button connected to pin PG.08 (EXTI Line8)
    - Use Wakeup push-button connected to pin PA.00 (EXTI Line0)
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - Make sure that the Jumper 4 (JP4) is in position 1<-->2. 

  - STM3210B-EVAL Set-up  
    - Connect a null-modem female/female RS232 cable between CN5 and CN6.
      @note in this case USART2 Tx and Rx pins are remapped by software on 
            PD.05 and PD.06 respectively. 
    - Use Key push-button connected to pin PB.09 (EXTI Line9)
    - Use Wakeup push-button connected to pin PA.00 (EXTI Line0)
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins             
   
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_exti.c
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
  - stm32f10x_usart.c 
  - misc.c 
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
