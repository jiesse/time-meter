/**
  @page WWDG_Example WWDG_Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file WWDG/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the WWDG Example.
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

This example shows how to update at regulate period the WWDG counter using the
Early Wakeup interrupt (EWI).

The WWDG timeout is set to 262 ms, the refresh window is set to 65 and the EWI is
enabled. When the WWDG counter reaches 64, the EWI is generated. In the WWDG ISR,
the counter is refreshed to prevent a WWDG reset and a specific GPIO pin is toggled.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the falling edge of the signal.
In the NVIC (nested vectored interrupt controller), the EXTI Line interrupt
vector is enabled with a priority equal to 0 and the WWDG interrupt vector is
enabled with a priority equal to 1 (EXTI IT > WWDG IT).

The EXTI Line is used to simulate a software failure: once the EXTI Line event 
occurs (by pressing the Key push-button on the STM3210B-EVAL or STM3210E-EVAL 
boards), the corresponding interrupt is served. In the ISR, the GPIO pin is reset 
and the EXTI Line pending bit is not cleared. So the CPU executes the EXTI Line 
ISR indefinitely and the WWDG ISR is never executed (the WWDG counter is not 
updated).
As a result, when the WWDG counter falls to 63, the WWDG reset occurs.
If the WWDG reset is generated, after the system resumes from reset, an other 
GPIO is set.

If the EXTI Line event does not occur, the WWDG counter is indefinitely refreshed
in the WWDG ISR, and there is no WWDG reset.

In this example the system is clocked by HSE, the high-speed external clock (8 MHz).

@par Directory contents 

  - WWDG/platform_config.h    Evaluation board specific configuration file
  - WWDG/stm32f10x_conf.h     Library Configuration file
  - WWDG/stm32f10x_it.c       Interrupt handlers
  - WWDG/stm32f10x_it.h       Header for stm32f10x_it.c
  - WWDG/main.c               Main program

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
    - Use LD1 and LD2 leds connected respectively to PF.06 and PF.07 pins, and the
      KEY push button connected to PG.08 pin.

  - STM3210B-EVAL Set-up  
    - Use LD1 and LD2 leds connected respectively to PC.06 and PC.07 pins, and the
      KEY push button connected to PB.09 pin.
     
@par How to use it ? 

In order to make the program work, you must do the following:
- Create a project and setup all project configuration
- Add the required Library files: 
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
  - misc.c 
  - stm32f10x_wwdg.c 
  - stm32f10x_flash.c 
  - stm32f10x_exti.c   
    
- Edit stm32f10x.h file to select the device you are working on.
  
@b Tip: You can tailor the provided project template to run this example, for 
        more details please refer to "stm32f10x_stdperiph_lib_um.chm" user 
        manual; select "Peripheral Examples" then follow the instructions 
        provided in "How to proceed" section.   
- Link all compiled files and load your image into target memory
- Run the example in standalone mode (without debugger connection)

@note
 - Low-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 16 and 32 Kbytes.
 - Medium-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 32 and 128 Kbytes.
 - High-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.
   
 * <h3><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h3>
 */
