/**
  @page TIM_PWM_Output TIM_PWM_Output
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file TIM/PWM_Output/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the TIM PWM_Output example.
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

This example shows how to configure the TIM peripheral in PWM (Pulse Width Modulation) 
mode.
The TIMxCLK frequency is set to 36 MHz, the Prescaler is 0 so the TIM3 counter clock is
36 MHz. 

The TIM3 is running at 36 KHz: TIM3 Frequency = TIM3 counter clock/(ARR + 1)

The TIM3 CCR1 register value is equal to 500, so the TIM3 Channel 1 generates a 
PWM signal with a frequency equal to 36 KHz and a duty cycle equal to 50%:
TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR + 1)* 100 = 50%

The TIM3 CCR2 register value is equal to 375, so the TIM3 Channel 2 generates a 
PWM signal with a frequency equal to 36 KHz and a duty cycle equal to 37.5%:
TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR + 1)* 100 = 37.5%

The TIM3 CCR3 register value is equal to 250, so the TIM3 Channel 3 generates a 
PWM signal with a frequency equal to 36 KHz and a duty cycle equal to 25%:
TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR + 1)* 100 = 25%

The TIM3 CCR4 register value is equal to 125, so the TIM3 Channel 4 generates a 
PWM signal with a frequency equal to 36 KHz and a duty cycle equal to 12.5%:
TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR + 1)* 100 = 12.5%

The PWM waveform can be displayed using an oscilloscope.

@par Directory contents 

  - TIM/PWM_Output/stm32f10x_conf.h  Library Configuration file
  - TIM/PWM_Output/stm32f10x_it.c    Interrupt handlers
  - TIM/PWM_Output/stm32f10x_it.h    Interrupt handlers header file
  - TIM/PWM_Output/main.c            Main program 

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
        - PA.06: (TIM3_CH1)
        - PA.07: (TIM3_CH2)
        - PB.00: (TIM3_CH3)
        - PB.01: (TIM3_CH4)  
  
@par How to use it ? 

In order to make the program work, you must do the following:
- Create a project and setup all project configuration
- Add the required Library files:
  - stm32f10x_flash.c  
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
  - stm32f10x_tim.c
    
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
