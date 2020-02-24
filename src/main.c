#include "led.h"
#include "clocks.h"
#include "uart.h"
#include <stdint.h>
#include "matrix.h"
#include "buttons.h"
#include "irq.h"




void test_static_image(rgb_color *image);
void display_image(rgb_color *image);
void USART1_IRQHandler(void);

volatile uint8_t frameimage[64*3]; //Declaring a vector instead of matrix guarantees memory zones allocated are continuous
extern uint8_t _binary_image_raw_start;
extern uint8_t _binary_image_raw_end;

void USART1_IRQHandler(void){

  static int index;
  uint8_t frame = uart_getchar();

  
  if(frame == 0xFF || index==192){
    index = 0;
    USART1->ICR = USART1->ICR | (USART_ICR_FECF | USART_ICR_ORECF); //Clears the error bits
  }
  else{
    if(!(USART1->ISR & USART_ISR_FE) && !(USART1->ISR & USART_ISR_ORE)){  //If no error ocurred, show frame normally
      frameimage[index++] = frame;
    }
  }
}

void display_image(rgb_color *image){
  static int row;
  for(row=0; row<8; row++){
     mat_set_row(row, &(image[row*8]));
  }
}

void test_static_image(rgb_color *image){
  uint8_t *octet;
  int row = 0;
  for(octet = &_binary_image_raw_start; octet < &_binary_image_raw_end;){
    for(int led = 0; led < 8; led++){
      image[row*8 + led].r = *octet;
      octet++;
      image[row*8 + led].g = *octet;
      octet++;
      image[row*8 + led].b = *octet;
      octet++;
    }
    row++;
  }
}

int main() {
  irq_init();
  clocks_init();
  uart_init(38400);
  button_init();
  led_init();
  matrix_init();
  rgb_color *image = (rgb_color *)frameimage;
  test_static_image(image);
  while(1){
    display_image(image);
  }
  return 0;
} 

