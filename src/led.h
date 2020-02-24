#ifndef LED_H
#define LED_H

#include <stdio.h>
#include "stm32l475xx.h"


enum state {LED_OFF, LED_YELLOW, LED_BLUE};
void led_init();
void led_g_on();
void led_g_off();
void led(enum state);
void delay(int);
void gyb(int, int, int);
void byg(int, int, int);

#endif //LED_H
