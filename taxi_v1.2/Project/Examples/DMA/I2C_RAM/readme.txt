/**
  @page DMA_I2C_RAM DMA_I2C_RAM
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file DMA/I2C_RAM/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the DMA I2C example.
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

This example provides a description of how to use two DMA channels to transfer a 
data buffer from memory to I2C2 through I2C1.
I2C1 is set as the master transmitter and I2C2 as the slave receiver. DMA1 Channel5 is
configured to store the data received from I2C2 into the Rx buffer (reception buffer).
DMA1 Channel6 is configured to transfer data from the Tx buffer (transmission buffer) to
the I2C1 DR register. After the generation of the Start condition and once the slave
address has been acknowledged, DMA capability is enabled for both I2C1 and I2C2. As soon as the
two I2C DMAEN bits are set in the I2C1_CR2 and I2C2_CR2 registers, the transmission of
the Tx buffer is started by DMA1 Channel5 and at the same time the data received on
I2C2 is stored in Rx buffer using DMA1 Channel6 . The transmitted and the received buffers
are compared to check that all data have been correctly transferred.

@par Directory contents 

  - DMA/I2C_RAM/stm32f10x_conf.h  Library Configuration file
  - DMA/I2C_RAM/stm32f10x_it.c    Interrupt handlers
  - DMA/I2C_RAM/stm32f10x_it.h    Interrupt handlers header file
  - DMA/I2C_RAM/main.c            Main program

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    and can be easily tailored to any other supported device and development 
    board.

  - STM3210E-EVAL Set-up 
    - Connect I2C1 SCL pin (PB.06) to I2C2 SCL pin (PB.10)
    - Connect I2C1 SDA pin (PB.07) to I2C2 SDA pin	(PB.11)
    - Check that a pull-up resistor is connected on one I2C SDA pin
    - Check that a pull-up resistor is connected on one I2C SCL pin

  - STM3210B-EVAL Set-up 
    - Connect I2C1 SCL pin (PB.06) to I2C2 SCL pin (PB.10)
    - Connect I2C1 SDA pin (PB.07) to I2C2 SDA pin	(PB.11)
    - Check that a pull-up resistor is connected on one I2C SDA pin
    - Check that a pull-up resistor is connected on one I2C SCL pin    
      

@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_dma.c 
  - stm32f10x_rcc.c 
  - stm32f10x_i2c.c 
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
