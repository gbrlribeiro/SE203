#include "led.h"

void led_init() {

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;
  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14) | GPIO_MODER_MODE14_0;
  GPIOC->MODER = GPIOC->MODER & ~GPIO_MODER_MODE9;

}


void led_g_on(){
  GPIOB->ODR |= GPIO_ODR_OD14;
}


void led_g_off(){
  GPIOB->ODR &= ~GPIO_ODR_OD14;
}

void led(enum state S) {
  switch(S) {
    case LED_YELLOW:
      GPIOC->MODER = (GPIOC->MODER &~GPIO_MODER_MODE9) | GPIO_MODER_MODE9_0;
      GPIOC->ODR |= GPIO_ODR_OD9;
      break;
    case LED_BLUE:
      GPIOC->MODER = (GPIOC->MODER &~GPIO_MODER_MODE9) | GPIO_MODER_MODE9_0;
      GPIOC->ODR &= ~GPIO_ODR_OD9;
      break;
    case LED_OFF:
      GPIOC->MODER = GPIOC->MODER & ~GPIO_MODER_MODE9;
      break;
    }
}

void delay(int temps){
  for(int i = 0; i < temps; i++)
    asm volatile("nop");
}

void gyb(int green, int yellow, int blue){
  
  led_g_on();
  delay(green*100000);
  led_g_off();

  led(LED_YELLOW);
  delay(yellow*100000);
  led(LED_YELLOW);

  led(LED_BLUE);
  delay(blue*100000);
  led(LED_OFF);
}

void byg(int blue, int yellow, int green){

  led(LED_BLUE);
  delay(blue*100000);
  led(LED_OFF);

  led(LED_YELLOW);
  delay(yellow*100000);
  led(LED_OFF);

  led_g_on();
  delay(green*100000);
  led_g_off();
}
