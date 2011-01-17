/**
  @page USART_Printf USART_Printf
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file USART/Printf/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the USART Printf Example.
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

This example shows how to retarget the C library printf function to the USART. 
This implementation output the printf message on the Hyperterminal using USARTx.
USARTx can be USART1, USART2, USART3, UART4 or UART5; to select the USART 
interface to be used uncomment the '#define USE_USARTx' line in 'platform_config.h'
file.

The USARTx is configured as follow:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled

@par Directory contents 

  - USART/Printf/platform_config.h    Evaluation board specific configuration file
  - USART/Printf/stm32f10x_conf.h     Library Configuration file
  - USART/Printf/stm32f10x_it.h       Interrupt handlers header file
  - USART/Printf/stm32f10x_it.c       Interrupt handlers
  - USART/Printf/main.c               Main program

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    and can be easily tailored to any other supported device and development 
    board.
    To select the STMicroelectronics evaluation board used to run the example, 
    uncomment the corresponding line in platform_config.h file.
    
  - The USARTx signals (Rx, Tx) must be connected to a DB9 connector using a RS232 
    transceiver. 
 
  - Connect a null-modem female/female RS232 cable between the DB9 connector  
    and PC serial port. 

  - STM3210E-EVAL Set-up
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      (CN12 for USART1, CN8 for USART2 in the STM3210E-EVAL board) 
      and PC serial port.   
   
  - STM3210B-EVAL Set-up  
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      (CN6 for USART1, CN5 for USART2 in the STM3210B-EVAL board) 
      and PC serial port.
 
  - Hyperterminal configuration:
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - BaudRate = 115200 baud
    - flow control: None 

@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
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
