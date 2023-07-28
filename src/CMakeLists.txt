project(${CMAKE_PROJECT_NAME})

set(SOURCES	
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/startup_stm32f411xe.s
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/system_stm32f4xx.c
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/segger_fault_handler.c
	bootloader.c
)

add_executable( bootloader.elf 
	${SOURCES}
)

target_include_directories(bootloader.elf  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/)
target_include_directories(bootloader.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/bootloader/)
target_include_directories(bootloader.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/llcm4/include/llcm/)

target_link_options(bootloader.elf  PRIVATE 
    ${arch_flags} 
    ${common_flags}
    ${link_flags}
    -T ${CMAKE_CURRENT_LIST_DIR}/bootloader.ld
)

target_link_libraries(bootloader.elf
	llcm
	usart
	flash
)
