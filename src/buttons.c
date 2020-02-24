#include "stm32l475xx.h"
#include <stdint.h>
#include "buttons.h"
#include "led.h"

void button_init(void){

    // Activates clock of PORT C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    //Set port to Input
    GPIOC->MODER &= ~GPIO_MODER_MODE13;

    //Set Bit 13 to 1, enable interrupt
    EXTI->IMR1 |= EXTI_IMR1_IM13_Msk;

    //Clear Rising Edge detection
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13_Msk;

    //Enable falling edge detection
    EXTI->FTSR1 |= EXTI_FTSR1_FT13_Msk;

    //Enable EXTI lines from 10 to 15    
    NVIC_EnableIRQ(40);

    //Set Source input for EXTI13 as PC(13);
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13_Msk) | SYSCFG_EXTICR4_EXTI13_PC;

}




void EXTI15_10_IRQHandler(void){

    EXTI->PR1 = (EXTI->PR1 & ~EXTI_PR1_PIF13) | EXTI_PR1_PIF13;//Signals that interruption was executed

    static int flag = 0;
    if(!flag){
        led_g_on();
        flag = 1;
    }
    
    else{
        led_g_off();
        flag = 0;
    }

}

//We see the colored image from the last part while the interruption is handled
//Because the led is set as ON very quickly
