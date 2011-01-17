SET RVCT40INC=C:\Keil\ARM\RV31\INC
SET RVCT40LIB=C:\Keil\ARM\RV31\LIB
SET CPU_TYPE=STM32F103VE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=STM32_RTC
SET CPU_CLOCK=0x00000000
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\main.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\rtc_init.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\bill.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\lcd.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\lcd_init.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_it.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_rcc.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_gpio.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\misc.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_bkp.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_crc.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_exti.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_flash.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_fsmc.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_pwr.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_rtc.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_sdio.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_spi.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_tim.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_usart.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_wwdg.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\system_stm32f10x.__i"
"C:\Keil\ARM\BIN40\ArmCC" --Via ".\obj\core_cm3.__i"
"C:\Keil\ARM\BIN40\ArmAsm" --Via ".\obj\startup_stm32f10x_hd._ia"
"C:\Keil\ARM\BIN40\ArmLink" --Via ".\Obj\STM32_RTC.lnp"
C:\Keil\ARM\BIN40\fromelf.exe ".\Obj\STM32_RTC.axf" --i32combined --output ".\Obj\STM32_RTC.hex"
