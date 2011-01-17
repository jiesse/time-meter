/**
  @page TIM_OnePulse TIM_OnePulse
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file TIM/OnePulse/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the TIM OnePulse example.
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

This example shows how to use the TIM peripheral to generate a One pulse Mode 
after a Rising edge of an external signal is received in Timer Input pin.

The TIM2CLK frequency is set to 72 MHz, the Prescaler is 1 so the TIM2 counter
clock is 36 MHz. 
The Autoreload value is 65535 (TIM2->ARR), so the maximum frequency value to trigger 
the TIM2 input is 500 Hz.

The TIM2 is configured as follows: 
The One Pulse mode is used, the external signal is connected to TIM2 CH2 pin (PA.01), 
the Rising edge is used as active edge, the One Pulse signal is output 
on TIM2_CH1 (PA.00).

The TIM_Pulse defines the delay value, the delay value is fixed to 455.08 us:
delay =  CCR1/TIM2 counter clock = 455.08 us. 
The (TIM_Period - TIM_Pulse) defines the One Pulse value, the pulse value is fixed to 1.365ms:
One Pulse value = (TIM_Period - TIM_Pulse)/TIM2 counter clock = 1.365 ms.

@par Directory contents 

  - TIM/OnePulse/stm32f10x_conf.h  Library Configuration file
  - TIM/OnePulse/stm32f10x_it.c    Interrupt handlers
  - TIM/OnePulse/stm32f10x_it.h    Interrupt handlers header file
  - TIM/OnePulse/main.c            Main program 

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    and can be easily tailored to any other supported device and development 
    board.

  - STM3210E-EVAL and STM3210B-EVAL Set-up 
   - Connect the external signal to the TIM2_CH2 pin (PA.01)
   - Connect the TIM2_CH1 (PA.00) pin to an oscilloscope to monitor the waveform.   
  
@par How to use it ? 

In order to make the program work, you must do the following:
- Create a project and setup all project configuration
- Add the required Library files:
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
  - stm32f10x_tim.c
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
