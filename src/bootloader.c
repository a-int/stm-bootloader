#include <bootloader.h>
#include <llcm.h>

void init_GPIO();

int main() {
  initSW();            // initialize serial wire
  init_clock_100();    // initialize MPU to work at 100 MHz
  init_SysTick(1000);  // initialize SysTick to work at ms
  while (1) {
    if (!(READ_BIT(GPIOA->IDR, (1 << 0)))) {       // if button at PA0 is pressed enter to firmware
      uint32_t* firmware = (uint32_t*)_sfirmware;  //get the address of firmware start
      __disable_irq();
      SCB->VTOR = (uint32_t)firmware;  //set up Vector table Offset
      __set_MSP(firmware[0]);          // set up stack pointer
      __enable_irq();
      void (*Reset_Handler)(void) = (void (*)())(firmware[1]);
      Reset_Handler();  // start firmware
    }
  }
  return 0;
}
void init_GPIO() {
  // set up for GPIOA0 (BUTTON)
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);     //enable GPIOA
  CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE0_Msk);  // set as input
  CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT0);      //select push-pull mode
  SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD0_0);      //select no push no pull mode
}
