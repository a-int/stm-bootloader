# stm-bootloader
The Bootloader for the STM32F411 microcontroller written entirely using CMSIS and llcm4 library.

# Details
The bootloader can boot into one user application right after specific condition (button press, incoming message, etc).
The bootloader is located at the sector 0 of the internal FLASH memory of the STM32 with address space from 0x0800_0000 to 0x0800_3FFF.

After the bootloader is written to the STM32, it can process the incoming stream from PC via USART2 (PA2-TX, PA3-RX). The whole data stream will be saved to the MPU internal memory and after the completion it will be transfered to the internal FLASH memory of the microcontroller. The firmware starts from SECTOR 1 with the address 0x0800_4000. 

Right after the flashing is done, microcontroller continues to operate and can be used to start new firmware.
