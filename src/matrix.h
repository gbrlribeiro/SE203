#ifndef MATRIX_H
#define MATRIX_H
#include "stm32l475xx.h"
#include <stdint.h>


typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color ;

//#define FCK 80000000

void matrix_init();
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void test_pixels();
void init_bank0();
void send_byte(uint8_t val, int bank);
void mat_set_row(int row, const rgb_color *val);
void init_bank0();
void test_pixels();



#define RST(x) do{ if(x) { GPIOC->BSRR = GPIOC->BSRR | GPIO_BSRR_BS3; } else GPIOC->BSRR = GPIOC->BSRR | GPIO_BSRR_BR3; }while(0);
#define LAT(x) do{ if(x) { GPIOC->BSRR = GPIOC->BSRR | GPIO_BSRR_BS4; }else GPIOC->BSRR = GPIOC->BSRR | GPIO_BSRR_BR4; }while(0);
#define  SB(x) do{ if(x) { GPIOC->BSRR = GPIOC->BSRR | GPIO_BSRR_BS5; }else GPIOC->BSRR = GPIOC->BSRR | GPIO_BSRR_BR5; }while(0);
#define SCK(x) do{ if(x) { GPIOB->BSRR = GPIOB->BSRR | GPIO_BSRR_BS1; }else GPIOB->BSRR = GPIOB->BSRR | GPIO_BSRR_BR1; }while(0);
#define SDA(x) do{ if(x) { GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BS4; }else GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BR4; }while(0);
#define  C0(x) do{ if(x) { GPIOB->BSRR = GPIOB->BSRR | GPIO_BSRR_BS2; }else GPIOB->BSRR = GPIOB->BSRR | GPIO_BSRR_BR2; }while(0);
#define  C1(x) do{ if(x) { GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BS15;} else GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BR15; }while(0);
#define  C2(x) do{ if(x) { GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BS2; }else GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BR2; }while(0);
#define  C3(x) do{ if(x) { GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BS7; }else GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BR7; }while(0);
#define  C4(x) do{ if(x) { GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BS6; }else GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BR6; }while(0);
#define  C5(x) do{ if(x) { GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BS5; }else GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BR5; }while(0);
#define  C6(x) do{ if(x) { GPIOB->BSRR = GPIOB->BSRR | GPIO_BSRR_BS0; }else GPIOB->BSRR = GPIOB->BSRR | GPIO_BSRR_BR0; }while(0);
#define  C7(x) do{ if(x) { GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BS3; }else GPIOA->BSRR = GPIOA->BSRR | GPIO_BSRR_BR3; }while(0);

#define ROW0(x) do{ if(x) {C0(1) C1(0) C2(0) C3(0) C4(0) C5(0) C6(0) C7(0); } else ROWoff; }while(0);
#define ROW1(x) do{ if(x) {C0(0) C1(1) C2(0) C3(0) C4(0) C5(0) C6(0) C7(0); } else ROWoff; }while(0);
#define ROW2(x) do{ if(x) {C0(0) C1(0) C2(1) C3(0) C4(0) C5(0) C6(0) C7(0); } else ROWoff; }while(0);
#define ROW3(x) do{ if(x) {C0(0) C1(0) C2(0) C3(1) C4(0) C5(0) C6(0) C7(0); } else ROWoff; }while(0);
#define ROW4(x) do{ if(x) {C0(0) C1(0) C2(0) C3(0) C4(1) C5(0) C6(0) C7(0); } else ROWoff; }while(0);
#define ROW5(x) do{ if(x) {C0(0) C1(0) C2(0) C3(0) C4(0) C5(1) C6(0) C7(0); } else ROWoff; }while(0);
#define ROW6(x) do{ if(x) {C0(0) C1(0) C2(0) C3(0) C4(0) C5(0) C6(1) C7(0); } else ROWoff; }while(0);
#define ROW7(x) do{ if(x) {C0(0) C1(0) C2(0) C3(0) C4(0) C5(0) C6(0) C7(1); } else ROWoff; }while(0);
#define ROWoff  do{ C0(0); C1(0); C2(0); C3(0); C4(0); C5(0); C6(0); C7(0); }while(0);

#endif //MATRIX_H