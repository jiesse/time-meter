/**
  @page DAC_DualModeDMA_SineWave DAC_DualModeDMA_SineWave
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file DAC/DualModeDMA_SineWave/readme.txt 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Description of the DAC dual mode sine wave example.
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

This example describes how to use DAC dual channel mode with DMA to generate sine
waves on both DAC channels outpouts.

Both DAC channels conversions are configured to be triggered by TIM8 TRGO triggers
and without noise/triangle wave generation. 12bit right data alignement is selected
since we choose to acces DAC_DHR12RD register. DMA2 channel4 is configured to
transfer continuously, word by word, a 32-word buffer to the dual DAC register
DAC_DHR12RD.

The transfered 32buffer is made to have a sine wave generation on each DAC channel 
output. Both DAC channels are then enabled. Only DAC channel2 DMA capability is enabled.

Once TIM8 is enabled, each TIM8 TRGO update event generate a DMA request which
transfer data to the dual DAC register and DAC conversion is started. The sine
waves can be visualized by connecting both PA.04 and PA.05 pins to an oscilloscope.

@par Directory contents 

  - DAC/DualModeDMA_SineWave/stm32f10x_conf.h     Library Configuration file
  - DAC/DualModeDMA_SineWave/stm32f10x_it.c       Interrupt handlers
  - DAC/DualModeDMA_SineWave/stm32f10x_it.h       Header for stm32f10x_it.c
  - DAC/DualModeDMA_SineWave/main.c               Main program

@par Hardware and Software environment 

  - This example runs only on STM32F10x High-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) evaluation board and can be easily tailored to any other 
    supported device and development board.

  - STM3210E-EVAL Set-up 
    - Connect PA.04 and PA.05 pins to an oscilloscope
    
@par How to use it ? 

In order to make the program work, you must do the following:
- Create a project and setup all project configuration
- Add the required Library files:
  - stm32f10x_gpio.c
  - stm32f10x_dac.c 
  - stm32f10x_dma.c 
  - stm32f10x_rcc.c 
  - stm32f10x_tim.c
  - system_stm32f10x.c 
      
- Edit stm32f10x.h file to select the device you are working on (#define 
  STM32F10X_HD, in this case).
  
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
