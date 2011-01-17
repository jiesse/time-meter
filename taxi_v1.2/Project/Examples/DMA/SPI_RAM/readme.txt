/**
  @page DMA_SPI_RAM DMA_SPI_RAM
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file DMA/SPI_RAM/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the DMA SPI example.
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

This example provides a description of how to use four DMA channels to transfer a 
data buffer from memory to SPI2 through SPI1 and a second data buffer from memory
to SPI1 through SPI2 in ful-duplex mode.

The NSS pins are configured by software to set SPI1 as master and SPI2 as slave.
DMA1 Channel2 and Channel4 are configured to store, respectively, the data
received by SPI1 into the SPI1_Buffer_Rx and the data received by SPI2 into the
SPI2_Buffer_Rx. 
DMA1 Channel3 is configured to transfer data from the SPI1_Buffer_Tx to	the
SPI1_DR register for transmission to SPI2. DMA1 Channel5 is configured to transfer
data from the SPI2_Buffer_Tx to the SPI2_DR register for transmission to SPI1.

As soon as the two SPIs TxDMAEN and RxDMAEN bits are set in the SPI1_CR2 and
SPI2_CR2 registers, DMA1 Channel3 and Channel5 start transmitting, respectively,
the SPI1 and SPI2 Tx buffers at the same time. At the same moment, the data received
on SPI1 and SPI2 are stored by DMA1 Channel2 and Channel4 to the SPI1 and SPI2
Rx buffers, respectively.

A polling on all Transfer complete flags are done for all used DMA channels to
check the end of all DMA channels transfers. The last received data on SPI1 and
SPI2 are the CRC values sent by each SPI to the other. The transmitted and received
buffers are compared to check that all data have been correctly transferred.

@par Directory contents 

  - DMA/SPI_RAM/stm32f10x_conf.h  Library Configuration file
  - DMA/SPI_RAM/stm32f10x_it.c    Interrupt handlers
  - DMA/SPI_RAM/stm32f10x_it.h    Interrupt handlers header file
  - DMA/SPI_RAM/main.c            Main program

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

@note On STM3210E-EVAL board, the jumper 14 (USB Disconnect) must be set in 
      position 1<->2 in order to not interfer with SPI2 MISO pin PB14.
      
  - STM3210B-EVAL Set-up 
    - Connect SPI1 SCK pin (PA.05) to SPI2 SCK pin	(PB.13)
    - Connect SPI1 MISO pin (PA.06) to SPI2 MISO pin (PB.14)
    - Connect SPI1 MOSI pin (PA.07) to SPI2 MOSI pin (PB.15)    

@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_dma.c 
  - stm32f10x_rcc.c 
  - stm32f10x_spi.c 
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
