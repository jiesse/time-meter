/**
  @page PWR_STOP PWR_STOP
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file PWR/STOP/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the PWR STOP Example.
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

This example shows how to enter the system to STOP mode and wake-up using EXTI
Line interrupts. The EXTI Line sources are PB.09/PG.08 and RTC Alarm.

The EXTI line9/8 is configured to generate interrupt on falling edge.
The EXTI line17(RTC Alarm) is configured to generate interrupt on rising edge and
the RTC time base is set to 1 second using the external low speed oscillator(LSE).

The system clock is set to 72 MHz using the external high speed oscillator(HSE).

The system enters and exits STOP mode as following:
After 2 second from system start-up, the RTC is configured to generate an Alarm
event in 3 second then the system enters STOP mode. To wake-up from STOP mode you
have to apply a rising edge on EXTI line9/8, otherwise the  RTC Alarm will wake-up
the system within 3 second. After exit from STOP the system clock is reconfigured
to its previous state (as HSE and PLL are disabled in STOP mode).
Then after a delay the system will enter again in STOP mode and exit in the way
described above. This behavior is repeated in an infinite loop.

Four leds connected to GPIO_LED Pin6(LD1), Pin7(LD2) and Pin8(LD3) are used to
monitor the system state as following:
 - LD1 on: system in RUN mode
 - LD1 off: system in STOP mode
 - LD2 is toggled if EXTI Line9/8 is used to exit from STOP 
 - LD3 is toggled if EXTI line17(RTC Alarm) is used to exit from STOP 

@par Directory contents 

  - PWR/STOP/platform_config.h    Evaluation board specific configuration file
  - PWR/STOP/stm32f10x_conf.h     Library Configuration file
  - PWR/STOP/stm32f10x_it.c       Interrupt handlers
  - PWR/STOP/stm32f10x_it.h       Header for stm32f10x_it.c
  - PWR/STOP/main.c               Main program

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
    - Use LD1, LD2 and LD3 leds connected respectively to PF.06, PF0.7 and PF.08 pins
    - Use the Key push-button connected to pin PG.08 (EXTI Line8).

  - STM3210B-EVAL Set-up  
    - Use LD1, LD2 and LD3 leds connected respectively to PC.06, PC.07 and PC.08 pins
    - Use the Key push-button connected to pin PB.09 (EXTI Line9).

@note For power consumption measurement in STOP mode you have to: 
- Modify the example to configure all unused GPIO port pins in Analog Input mode
  (floating input trigger OFF). Refer to GPIO\IOToggle example for more details. 
- Replace jumper JP9 in the STM3210B-EVAL board or JP12 in the STM3210E-EVAL
  board by an ampermeter.
         
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_rcc.c 
  - stm32f10x_gpio.c 
  - stm32f10x_rtc.c   
  - stm32f10x_pwr.c   
  - stm32f10x_bkp.c 
  - stm32f10x_exti.c 
  - misc.c 
  - system_stm32f10x.c

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
