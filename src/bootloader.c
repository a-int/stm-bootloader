#include <bootloader.h>
#include <flash.h>
#include <llcm.h>
#include <usart.h>

void init_GPIO(); // initialize GPIO for button

volatile uint32_t delay_ms_time = 0;

#define USART_RX_DATA_MAX 4096

struct USART {
  uint8_t rx_data[USART_RX_DATA_MAX];
  uint32_t rx_data_counter;
};
struct USART huart2;

int main() {
  initSW();            // setup pins for Serial Wire debug
  init_clock_100();    // initialize MPU to work at 100 MHz
  init_SysTick(1000);  // initialize SysTick to work at ms
  init_GPIO();
  init_usart2_115200();
  while (1) {
    if (!(READ_BIT(GPIOA->IDR, (1 << 0)))) { //if the button at PA0 is pressed enter to firmware
      while (!(READ_BIT(GPIOA->IDR, (1 << 0)))) {} //what while pressed
      uint32_t* firmware = (uint32_t*)_sfirmware; //get the address of firmware start
      __disable_irq();
      SCB->VTOR = (uint32_t)firmware; //set up the Vector Table Offset
      __set_MSP(firmware[0]); // set stack pointer
      __enable_irq();
      void (*Reset_Handler)(void) = (void (*)())(firmware[1]);
      Reset_Handler(); //enter to firmware
    }
  }
}

void SysTick_Handler(void) {
  if (delay_ms_time > 0) {
    --delay_ms_time;
  }
}

void init_GPIO() {
  // set up for GPIOA0 (BUTTON)
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);     //enable GPIOA
  CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE0_Msk);  // set as input
  CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT0);      //select push-pull mode
  SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD0_0);      //select no push no pull mode
}

void USART2_IRQHandler(void) {
  if (READ_BIT(USART2->SR, USART_SR_RXNE)) {                         //if data may be read
    huart2.rx_data[huart2.rx_data_counter++] = (uint8_t)USART2->DR;  // copy recieved data
  }
  if (READ_BIT(USART2->SR, USART_SR_IDLE)) {
    USART2->DR;  // reset IDLE flag
    FLASH_unlock();
    FLASH_clear_section(1); //firmware at sector 1 : 0x0800_4000  -  0x0800_7fff
    FLASH_write((uint32_t*)huart2.rx_data, (uint32_t*)_sfirmware, huart2.rx_data_counter / 4);
    FLASH_lock();
  }
}
