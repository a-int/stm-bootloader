#include <bootloader.h>
#include <llcm.h>

int main() {
  initSW();            // initialize serial wire
  init_clock_100();    // initialize MPU to work at 100 MHz
  init_SysTick(1000);  // initialize SysTick to work at ms
  while (1) {
    uint32_t* firmware = (uint32_t*)_sfirmware;  //get the address of firmware start
    __disable_irq();
    SCB->VTOR = (uint32_t)firmware;  //set up Vector table Offset
    __set_MSP(firmware[0]);          // set up stack pointer
    __enable_irq();
    void (*Reset_Handler)(void) = (void (*)())(firmware[1]);
    Reset_Handler();  // start firmware
  }
  return 0;
}