# stm-bootloader
The Bootloader for the STM32F411 microcontroller written entirely using CMSIS and llcm4 library.

# Bootloader features

- The size of the bootloader < 4 KiB 
- Written completely with CMSIS
- easy to customize
- FLASH protection
- Communication is done via USART (USART2)
- Load user firmware after a specific condition (button press, incoming command, etc.)
- FLASH erasing
- FLASH programming


# Details
The bootloader can boot into one user application right after specific condition (button press, incoming message, etc).
The bootloader is located at the sector 0 of the internal FLASH memory of the STM32 with address space from 0x0800_0000 to 0x0800_3FFF.

After the bootloader is written to the STM32, it can process the incoming stream from PC via USART2 (PA2-TX, PA3-RX). The whole data stream will be saved to the MPU internal memory and after the completion it will be transfered to the internal FLASH memory of the microcontroller. The firmware starts from SECTOR 1 with the address 0x0800_4000. 

Right after the flashing is done, microcontroller continues to operate and can be used to start new firmware.

# Build
* Make sure you have installed arm toolcahin, cmake.
    ```
    $ arm-none-eabi-gcc -v
    $ cmake --version
    ```
 * if none of previous commands led to errors then you can try to compile library using the cmake template.
	```
	$ cd <path-of-this-repo>
    $ git submodule update --init
	$ mkdir build && cd build
	$ cmake -Darm-toolchain-path=<path-to-arm-toolcahin> -DCMAKE_TOOLCHAIN_FILE=../arm-toolchain.cmake -DBUILD_EXAMPLES=OFF ..
	$ cmake --build .
    $ arm-none-eabi-objcopy -O binary src/bootloader.elf bootloader.bin
	```
* after that the build directory will contain the binary file with bootloader which has to be flashed at the address 0x8000000

