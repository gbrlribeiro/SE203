#include <stdint.h>

extern uint8_t _bstart, _bend, _text, _etext,
               _data, _edata;
extern uint8_t scr1, scr2, scr3;

void init_bss(){
  uint8_t *dst = &_bstart;
  for (dst = &_bstart; dst < &_bend; dst++)
  *dst = 0;
}

__attribute__((section(".textrom"))) void init_text(){
  uint8_t *dst = &_text;
  uint8_t *src = &scr1;
  while (dst < &_etext){
    *dst++ = *src++;
  }
}

void init_data(){
  uint8_t *dst = &_data;
  uint8_t *src = &scr2;
  while (dst < &_edata){
    *dst++ = *src++;
  }
}


