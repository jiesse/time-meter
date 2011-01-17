/**
  @page TIM_OCToggle TIM_OCToggle
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file TIM/OCToggle/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the TIM OCToggle example.
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

This example shows how to configure the TIM2 peripheral to generate four different 
signals with four different frequencies.

The TIM2CLK frequency is set to 36 MHz, the Prescaler is set to 2, and used in 
Output Compare Toggle Mode.

TIM2 counter clock = TIMxCLK / (Prescaler +1) = 12 MHz 

The TIM2 CCR1 register value is equal to 32768: 
CC1 update rate = TIM2 counter clock / CCR1_Val = 366.2 Hz,
so the TIM2 Channel 1 generates a periodic signal with a frequency equal to 183.1 Hz.

The TIM2 CCR2 register is equal to 16384:
CC2 update rate = TIM2 counter clock / CCR2_Val = 732.4 Hz
so the TIM2 channel 2 generates a periodic signal with a frequency equal to 366.3 Hz.

The TIM2 CCR3 register is equal to 8192:
CC3 update rate = TIM2 counter clock / CCR3_Val = 1464.8 Hz
so the TIM2 channel 3 generates a periodic signal with a frequency equal to 732.4 Hz.

The TIM2 CCR4 register is equal to 4096:
CC4 update rate = TIM2 counter clock / CCR4_Val =  2929.6 Hz
so the TIM2 channel 4 generates a periodic signal with a frequency equal to 1464.8 Hz.

@par Directory contents 

  - TIM/OCToggle/stm32f10x_conf.h  Library Configuration file
  - TIM/OCToggle/stm32f10x_it.c    Interrupt handlers
  - TIM/OCToggle/stm32f10x_it.h    Interrupt handlers header file
  - TIM/OCToggle/main.c            Main program

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    and can be easily tailored to any other supported device and development 
    board.

  - STM3210E-EVAL and STM3210B-EVAL Set-up 
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
       - PA.00 (TIM2_CH1)
       - PA.01 (TIM2_CH2)
       - PA.02 (TIM2_CH3)
       - PA.03 (TIM2_CH4) 
  
@par How to use it ? 

In order to make the program work, you must do the following:
- Create a project and setup all project configuration
- Add the required Library files:
  - stm32f10x_flash.c
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
  - stm32f10x_tim.c
  - misc.c   
    
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
