#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include "stm32l475xx.h"
#include "cmsis_gcc.h"
#include "stm32l4xx.h"

void irq_init();

#define MAKE_DEFAULT_HANDLER(x) void __attribute__((weak)) x(void) { \
    __disable_irq(); \
    while(1); \
}


#endif //IRQ_H
