#include <stm32f411xe.h>
#include <bootloader.h>
int main(){
  while (1) {
    uint32_t* firmware = (uint32_t*)_sfirmware;
    __disable_irq();
    SCB->VTOR = (uint32_t)firmware;
    __set_MSP(firmware[0]);
    __enable_irq();
    void (*Reset_Handler)(void) = (void(*)())(firmware[1]);
    Reset_Handler();
  }
  return 0;
}