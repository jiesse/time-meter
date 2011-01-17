/**
  @page SPI_FullDuplex_SoftNSS SPI_FullDuplex_SoftNSS
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file SPI/FullDuplex_SoftNSS/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the SPI FullDuplex_SoftNSS Example.
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

This example provides a description of how to set a communication between the two
SPIs in full-duplex mode and performs a transfer from Master to Slave and then 
Slave to Master in the same application with software NSS management.
Both SPIs are configured with 8bit data frame and a 9Mbit/s communication speed.
In the first phase, the master SPI1 starts the SPI1_Buffer_Tx transfer while the 
slave SPI2 transmit SPI2_Buffer_Tx. Once the transfer is completed a comparison 
is done and TransferStatus1 and TransferStatus2 gives the data transfer status for
each data transfer direction where it is PASSED if transmitted and received data 
are the same otherwise it is FAILED.
As the NSS pin is managed by software, this permit to SPI1 to become slave and SPI2
to become master whithout hardware modification
In the second step, the slave SPI1 starts the SPI1_Buffer_Tx transfer while the 
master SPI2 transmit SPI2_Buffer_Tx. Once the transfer is completed a comparison 
is done and TransferStatus3 and TransferStatus4 gives the data transfer status for
each data transfer direction where it is PASSED if transmitted and received data 
are the same otherwise it is FAILED.

@par Directory contents 

  - SPI/FullDuplex_SoftNSS/stm32f10x_conf.h  Library Configuration file
  - SPI/FullDuplex_SoftNSS/stm32f10x_it.c    Interrupt handlers
  - SPI/FullDuplex_SoftNSS/stm32f10x_it.h    Interrupt handlers header file
  - SPI/FullDuplex_SoftNSS/main.c            Main program

@par Hardware and Software environment 

  - This example runs on STM32F10x High-Density, STM32F10x Medium-Density and
    STM32F10x Low-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) and STM3210B-EVAL (STM32F10x Medium-Density) evaluation boards 
    and can be easily tailored to any other supported device and development 
    board.

  - STM3210E-EVAL Set-up 
    - Connect SPI1 SCK pin (PA.05) to SPI2 SCK pin	(PB.13)
    - Connect SPI1 MISO pin (PA.06) to SPI2 MISO pin (PB.14)
    - Connect SPI1 MOSI pin (PA.07) to SPI2 MOSI pin (PB.15)

@note In STM3210E-EVAL board, the jumper 14 (USB Disconnect) must be set in 
      position 1<->2 in order to not interfer with SPI2 MISO pin PB14.

  - STM3210B-EVAL Set-up 
    - Connect SPI1 SCK pin (PA.05) to SPI2 SCK pin	(PB.13)
    - Connect SPI1 MISO pin (PA.06) to SPI2 MISO pin (PB.14)
    - Connect SPI1 MOSI pin (PA.07) to SPI2 MOSI pin (PB.15)
    
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_flash.c
  - stm32f10x_gpio.c  
  - stm32f10x_rcc.c 
  - stm32f10x_spi.c 
        
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
