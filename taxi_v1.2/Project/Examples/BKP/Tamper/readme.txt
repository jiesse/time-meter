/**
  @page BKP_Tamper BKP_Tamper
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file BKP/Tamper/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the BKP Tamper Example.
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

This example shows how to write/read data to/from Backup data registers and 
demonstrates the Tamper detection feature.

The associated firmware performs the following:

1. It configures the ANTI_TAMP pin to be active low, and enables the Tamper interrupt.

2. It writes the data to all Backup data registers, then check whether the data were
correctly written. If yes, the LED connected to GPIO_LED Pin 6 turns on, otherwise
the LED connected to GPIO_LED Pin7 turns on.

3. On applying a low level on the ANTI_TAMP pin (PC.13), the Backup data registers
are reset and the Tamper interrupt is generated. The corresponding ISR then checks
whether the Backup data registers are cleared. If yes, the LED connected to
GPIO_LED Pin8 turns on, otherwise the LED connected to GPIO_LED Pin9 turns on.

@par Directory contents 

  - BKP/Tamper/platform_config.h  Evaluation board specific configuration file
  - BKP/Tamper/stm32f10x_conf.h   Library Configuration file
  - BKP/Tamper/stm32f10x_it.h     Interrupt handlers header file
  - BKP/Tamper/stm32f10x_it.c     Interrupt handlers
  - BKP/Tamper/main.h             Main header file
  - BKP/Tamper/main.c             Main program

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
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, 
      PF.08 and PF.09 pins
    - Use the Tamper push-button connected to pin PC.13   

  - STM3210B-EVAL Set-up  
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, 
      PC.08 and PC.09 pins
    - Use the Tamper push-button connected to pin PC.13
         
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_pwr.c 
  - stm32f10x_bkp.c 
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
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
