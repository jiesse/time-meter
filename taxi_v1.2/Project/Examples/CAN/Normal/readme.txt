/**
  @page CAN_Normal CAN_Normal
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file CAN/Normal/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the CAN example.
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

This example shows how to configure the CAN peripheral to send and receive 
CAN frames in normal mode. The sent frames are used to control Leds by presseing 
key push button.
	
The CAN serial communication link is a bus to which a number of units may be
connected. This number has no theoretical limit. Practically the total number
of units will be limited by delay times and/or electrical loads on the bus line.

@note This example is tested with a bus of 3 units. The same program example is 
loaded in all units to send and receive frames.
	
	The CAN is configured as follow:
    - Bit Rate   = 1 Mbit/s  
    - CAN Clock  = external clock (HSE)
		- ID Filter  = All identifiers are allowed
		- RTR = Data
		- DLC = 1 byte
		- Data: Led number that should be turned ON

@par Directory contents 

  - CAN/Normal/platform_config.h    Hardware configuration header file
  - CAN/Normal/stm32f10x_conf.h     Library Configuration file
  - CAN/Normal/stm32f10x_it.c       Interrupt handlers
  - CAN/Normal/stm32f10x_it.h       Interrupt handlers header file
  - CAN/Normal/main.c               Main program

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
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - Use Push Button connected to PG8
    - Connect a female/female CAN cable between at least 2 EVAL CAN connectors 
      (on STM3210B-EVAL (CN2)/ STM3210E-EVAL (CN4) boards)
       - Connector 1 DB9_PIN2 to Connector 2 DB9_PIN2  (CAN_L)
		   - Connector 1 DB9_PIN5 to Connector 2 DB9_PIN5  ( GND )
		   - Connector 1 DB9_PIN7 to Connector 2 DB9_PIN7  (CAN_H) 

  - STM3210B-EVAL Set-up  
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins
    - Use Push Button connected to PB9      
    - Connect a female/female CAN cable between at least 2 EVAL CAN connectors 
      (on STM3210B-EVAL (CN2)/ STM3210E-EVAL (CN4) boards) 
      - Connector 1 DB9_PIN2 to Connector 2 DB9_PIN2  (CAN_L)
		  - Connector 1 DB9_PIN5 to Connector 2 DB9_PIN5  ( GND )
		  - Connector 1 DB9_PIN7 to Connector 2 DB9_PIN7  (CAN_H) 

@note Any unit in the CAN bus may play the role of sender (by pressing on the 
      key) or receiver.
      
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_can.c 
  - stm32f10x_rcc.c 
  - stm32f10x_gpio.c 
  - misc.c
  - system_stm32f10x.c 
       
- Edit stm32f10x.h file to select the device you are working on.
  
@b Tip: You can tailor the provided project template to run this example, for 
        more details please refer to "stm32f10x_stdperiph_lib_um.chm" user 
        manual; select "Peripheral Examples" then follow the instructions 
        provided in "How to proceed" section.   
- Link all compiled files and load your image into target memory
- Run the example
- In the first time the all leds are OFF.
- By Pressing on Key Button : LD1 turn ON and all other Leds are OFF, on the N
  eval-boards connected to the bus. 
- Press on Key Button again to send CAN Frame to command LDn+1 ON, all other Leds 
  are OFF on the N eval-boards.

@note
 - Low-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 16 and 32 Kbytes.
 - Medium-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 32 and 128 Kbytes.
 - High-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.
   
 * <h3><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h3>
 */
