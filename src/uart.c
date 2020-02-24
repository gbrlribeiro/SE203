#include "uart.h"
#include "matrix.h"
#include <stdint.h>

volatile uint8_t frameimage[64*3]; //Declaring a vector instead of matrix guarantees memory zones allocated are continuous


void uart_init(int baudrate){

  
  
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

  //Configurate UART Ports to AF7
  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_0) | GPIO_MODER_MODE6_1;
  GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_0) | GPIO_MODER_MODE7_1;

  GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6) | GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_1 | GPIO_AFRL_AFSEL6_2;
  GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7) | GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_2;

  //Set USART CLK equal to PCLK
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  RCC->CCIPR = RCC->CCIPR & ~RCC_CCIPR_USART1SEL_1;

  //Reset to make sure it works
  RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
  RCC->APB2RSTR  = RCC->APB2RSTR & ~RCC_APB2RSTR_USART1RST;


  //Set BAUD
  USART1->BRR = 80000000/baudrate;
  USART1->CR1 = 0;
  USART1->CR2 = 0;

  NVIC_EnableIRQ(37);

  //Enable USART; Reception and Transmission // //Enable USART Interruption when something is received 
  USART1->CR1  |= USART_CR1_RXNEIE | USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;  

  
}


void uart_putchar(uint8_t c){
  while(!(USART1->ISR & USART_ISR_TXE)); //Waits for transmission
  
  USART1->TDR = c;
}


uint8_t uart_getchar(){
  while(!(USART1->ISR & USART_ISR_RXNE)); //Waits for reception

  return(uint8_t) USART1->RDR;

}


void uart_puts(const uint8_t *str){
  uint32_t k;

  for(k = 0; str[k] != '\0'; k++){
    uart_putchar(str[k]);
  }
  

  //Add line return and new line after sending chars;
  uart_putchar(0xd);
  uart_putchar('\n');
}


void uart_gets(uint8_t *str, size_t size){
  size_t i = 0;
  uint8_t c = uart_getchar();

  //Stop if end of line, new line or just second to last element reached.
  while (c!= '\n' && c != 0xd && i < size-1){
    str[i] = c;

    i++;
    c = uart_getchar();
  }


  str[i] = '\0';

}


//To check the sum one must convert the result from Decimal to Hex shown in GDB.
uint32_t checksum(int datasize){
  int i;
  uint32_t sum = 0;

  for(i=0; i< datasize; i++){
    sum += uart_getchar();
  }

  return sum;

}