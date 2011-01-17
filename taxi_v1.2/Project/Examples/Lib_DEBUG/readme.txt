/**
  @page Lib_DEBUG_Example Lib_DEBUG_Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file Lib_DEBUG/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the Lib_DEBUG Example.
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

This example demonstrates Demonstrates how to declare a dynamic peripherals 
pointers used for Debug mode.  

To use Debug mode you have to add the lib_dbg.c file to your application.
This creates a pointer to the peripheral structure in SRAM. Debugging consequently
becomes easier and all register settings can be obtained by dumping a peripheral 
variable.

When the "USE_FULL_ASSERT" label (stm32f10x_conf.h file)is uncommented,
the assert_param macro is expanded and run-time checking is enabled in the 
firmware library code. The run-time checking allows checking that all the library 
functions input value lies within the parameter allowed values.

The associated program simulates wrong parameter passed to library function and the
source of the error is printed on Hyperterminal (through USART1).

@note
The Debug mode increases the code size and reduces the code performance. For this
reason, it is recommended to used it only when debugging the application and to
remove it from the final application code.

@par Directory contents 

  - Lib_DEBUG/stm32f10x_conf.h  Library Configuration file
  - Lib_DEBUG/stm32f10x_it.c    Interrupt handlers
  - Lib_DEBUG/stm32f10x_it.h    Header for stm32f10x_it.c
  - Lib_DEBUG/main.c            Main program
  - Lib_DEBUG/lib_dbg.c         Peripherals pointers initialization
  - Lib_DEBUG/lib_dbg.h         Header for lib_dbg.c 
  
@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    and can be easily tailored to any other supported device and development 
    board.

  - STM3210E-EVAL Set-up 
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      CN12 and PC serial port.

  - STM3210B-EVAL Set-up  
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      CN6 and PC serial port.
 
  - Hyperterminal configuration:
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - BaudRate = 115200 baud
    - flow control: None
      
@par How to use it ? 

In order to make the program work, you must do the following:
- Create a project and setup all project configuration
- Add the required Library files:
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
