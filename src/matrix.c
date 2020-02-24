#include "matrix.h"
#include <stdint.h>
#include "led.h"


void matrix_init(){

    //Set PORT A, B, C clocks.

    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN;


    //Set PORT A2, A3, A4, A5, A6, A7 to Output
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2) | GPIO_MODER_MODE2_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3) | GPIO_MODER_MODE3_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4) | GPIO_MODER_MODE4_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5) | GPIO_MODER_MODE5_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6) | GPIO_MODER_MODE6_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7) | GPIO_MODER_MODE7_0;
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15) | GPIO_MODER_MODE15_0;


    //Set PORT B0, B1, B2 to Output
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0) | GPIO_MODER_MODE0_0;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1) | GPIO_MODER_MODE1_0;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2) | GPIO_MODER_MODE2_0;

    //Set PORT C3, C4, C5 to Output
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3) | GPIO_MODER_MODE3_0;
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4) | GPIO_MODER_MODE4_0;
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5) | GPIO_MODER_MODE5_0;


    //Set A Ports to HIGH SPEED
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED2) & ~GPIO_OSPEEDR_OSPEED2_0;
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED3) & ~GPIO_OSPEEDR_OSPEED3_0;
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED4) & ~GPIO_OSPEEDR_OSPEED4_0;
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED5) & ~GPIO_OSPEEDR_OSPEED5_0;
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED6) & ~GPIO_OSPEEDR_OSPEED6_0;
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED7) & ~GPIO_OSPEEDR_OSPEED7_0;
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED15) & ~GPIO_OSPEEDR_OSPEED15_0;

    //Set B Ports to HIGH SPEED
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED0) & ~GPIO_OSPEEDR_OSPEED0_0;
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED1) & ~GPIO_OSPEEDR_OSPEED1_0;
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED2) & ~GPIO_OSPEEDR_OSPEED2_0;

    //Set C Ports to HIGH SPEED
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR | GPIO_OSPEEDR_OSPEED3) & ~GPIO_OSPEEDR_OSPEED3_0;
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR | GPIO_OSPEEDR_OSPEED4) & ~GPIO_OSPEEDR_OSPEED4_0;
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR | GPIO_OSPEEDR_OSPEED5) & ~GPIO_OSPEEDR_OSPEED5_0;


    RST(0);
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);
    C0(0);
    C1(0);
    C2(0);
    C3(0);
    C4(0);
    C5(0);
    C6(0);
    C7(0);


    for(long int i=0; i < 100*80000/5000; i++){
        asm volatile("nop");
    }

    RST(1);

    init_bank0();
}



void pulse_SCK(){
    SCK(0);
    for(int i=0;i<2;i++){
        asm volatile("nop");
    }
    SCK(1);
     
    for(int i=0;i<2;i++){
        asm volatile("nop");
    }
    
    SCK(0);

    for(int i=0;i<2;i++){
        asm volatile("nop");
    }
    
}




void pulse_LAT(){
    LAT(1);
    for(int i=0;i<2;i++){
        asm volatile("nop");
    }
    LAT(0);
     
    for(int i=0;i<2;i++){
        asm volatile("nop");
    }
    
    LAT(1);

    for(int i=0;i<2;i++){
        asm volatile("nop");
    }
    
}




void deactivate_rows(){
    ROWoff; //Turns off all lignes; Macro defined in matrix.h
}





void activate_row(int row){
    switch(row){
        case 0:
            ROW0(1);
        break;

        case 1:
            ROW1(1);
        break;

        case 2:
            ROW2(1);
        break;

        case 3:
            ROW3(1);
        break;

        case 4:
            ROW4(1);
        break;

        case 5:
            ROW5(1);
        break;

        case 6:
            ROW6(1);
        break;

         case 7:
            ROW7(1);
        break;

        default:
            ROWoff;
    }
}




void send_byte(uint8_t val, int bank){
    SB(bank);
    int k;
    for(int i = 7; i >= 0; i--){
        k = (val & (1 << i)) >> i;
        SDA(k);
        pulse_SCK();
    }
}


void mat_set_row(int row, const rgb_color *val){
    for(int i = 7; i>=0; i--){
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);
    }
    
    deactivate_rows();
    delay(100);
    pulse_LAT();
    activate_row(row);

}



void init_bank0(){
    SB(0);
    SDA(1);
    for(int i = 144; i>=0; i--){
        pulse_SCK();
    }
    pulse_LAT();
}




//Cycling between blue, green and red dégradé.
//Has a big delay between colors so we can properly see the dégradé
void test_pixels(){

    rgb_color val[8];

    

    for(int i=7; i>=0; i--){
        val[i].b = 255 - (32)*i;
        val[i].g = 0;
        val[i].r = 0;
    }


    for(int j=0; j<1000; j++){
        for(int i=7; i>=0; i--){
            mat_set_row(i, val);

        }
    }
    
    
    ROWoff;

    for(int i=7; i>=0; i--){
        val[i].g = 255 - (32)*i;
        val[i].b = 0;
        val[i].r = 0;
    }

    for(int j=0; j<1000; j++){
        for(int i=7; i>=0; i--){
            mat_set_row(i, val);
        }
    }

    
    ROWoff;

    for(int i=7; i>=0; i--){
        val[i].r = 255 - (32)*i;
        val[i].g = 0;
        val[i].b = 0;
    }

    for(int j=0; j<1000; j++){
        for(int i=7; i>=0; i--){
            mat_set_row(i, val);
        }
    }
    ROWoff;
}




