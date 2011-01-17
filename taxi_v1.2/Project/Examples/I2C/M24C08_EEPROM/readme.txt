/**
  @page I2C_M24C08_EEPROM I2C_M24C08_EEPROM
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file I2C/M24C08_EEPROM/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the I2C and M24C08 EEPROM communication example.
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

This example provides a basic example of how to use the I2C software library
and an associate I2C EEPROM driver to communicate with an M24C08 EEPROM.
I2C1 is configured in Master transmitter during write operation and in Master 
receiver during read operation from I2C EEPROM. 
The speed is set to the maximum frequency of 400kHz. This value is defined in 
the I2c_ee.c file, which could be in the range of 0 to 400KHZ.
One I2C EEPROM Block address where the program will write the buffer have to be
selected from the four address available and defined in the I2c_ee.h file. 
The EEPROM address where the program start the write and the read operations is
defined in the main.c file. 

First, the contents of Tx1_Buffer are written to the EEPROM_WriteAddress1 and the
written data are read. The written and the read buffers data are then compared.
Following the read operation, the program wait that the EEPROM reverts to its 
Standby state. A second write operation is, then, performed and this time, Tx2_Buffer
is written to EEPROM_WriteAddress2, which represents the address just after the last 
written one in the first write. After completion of the second write operation, the 
written data are read. The contents of the written and the read	buffers are compared.

@par Directory contents 

  - I2C/M24C08_EEPROM/stm32f10x_conf.h  Library Configuration file
  - I2C/M24C08_EEPROM/stm32f10x_it.c    Interrupt handlers
  - I2C/M24C08_EEPROM/stm32f10x_it.h    Interrupt handlers header file
  - I2C/M24C08_EEPROM/main.c            Main program
  - I2C/M24C08_EEPROM/i2c_ee.c          I2C EEPROM driver
  - I2C/M24C08_EEPROM/i2c_ee.h          Header for the i2c_ee.c file

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    with addition of the following hardware connection and can be easily 
    tailored to any other supported device and development board.

  - STM3210E-EVAL Set-up 
    - Connect I2C1 SCL pin (PB.06) to I2C EEPROM SCL (pin6)
    - Connect I2C1 SDA pin (PB.07) to I2C EEPROM SDA (pin5)
    - Check that a pull-up resistor (4.7K) is connected on one I2C SDA pin
    - Check that a pull-up resistor (4.7K) is connected on one I2C SCL pin
    - Connect I2C EEPROM Vcc (pin8) to Vdd
    - Connect I2C EEPROM Vss (pin4) to Vss

  - STM3210B-EVAL Set-up 
    - Connect I2C1 SCL pin (PB.06) to I2C EEPROM SCL (pin6)
    - Connect I2C1 SDA pin (PB.07) to I2C EEPROM SDA (pin5)
    - Check that a pull-up resistor (4.7K) is connected on one I2C SDA pin
    - Check that a pull-up resistor (4.7K) is connected on one I2C SCL pin
    - Connect I2C EEPROM Vcc (pin8) to Vdd
    - Connect I2C EEPROM Vss (pin4) to Vss    

@note The pull-up resitors are already implemented on the STM3210B-EVAL and
      STM3210E-EVAL evaluation boards.

@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_i2c.c 
  - stm32f10x_rcc.c 
  - stm32f10x_gpio.c
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
