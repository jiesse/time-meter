/**
  @page USART_DMA_Interrupt USART_DMA_Interrupt
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file USART/DMA_Interrupt/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the USART DMA Interrupt Example.
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

This example provides a basic communication between USART1 and USART2 using DMA 
capability, flags and interrupts.

First, the DMA transfers data from TxBuffer2 buffer to USART2 Transmit data register,
then this data is sent to USART1. Data received by USART1 is transferred using 
RXNE flag and stored in RxBuffer1 then compared with the sent ones and
the result of this comparison is stored in the "TransferStatus1" variable.
 
In the same time, the DMA transfers data from TxBuffer1 buffer to USART1 Transmit
data register, then this data is sent to USART2. Data received by USART2 is
transferred using Receive interrupt and stored in RxBuffer2 then compared with
the sent ones and the result of this comparison is stored in the "TransferStatus2"
variable. 

USART1 and USART2 configured as follow:
  - BaudRate = 230400 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled       
        
@par Directory contents 

  - USART/DMA_Interrupt/platform_config.h    Evaluation board specific configuration file
  - USART/DMA_Interrupt/stm32f10x_conf.h     Library Configuration file
  - USART/DMA_Interrupt/stm32f10x_it.h       Interrupt handlers header file
  - USART/DMA_Interrupt/stm32f10x_it.c       Interrupt handlers
  - USART/DMA_Interrupt/main.c               Main program

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
    - Connect a null-modem female/female RS232 cable between CN12 and CN8.
    
  - STM3210B-EVAL Set-up
    - Connect a null-modem female/female RS232 cable between CN5 and CN6.
      In this case USART2 Tx and Rx pins are remapped by software on PD.05 and 
      PD.06 respectively. 
  
@par How to use it ? 

In order to make the program work, you must do the following :
- Create a project and setup all project configuration
- Add the required Library files :
  - stm32f10x_dma.c 
  - stm32f10x_gpio.c 
  - stm32f10x_rcc.c 
  - stm32f10x_usart.c
  - misc.c
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
