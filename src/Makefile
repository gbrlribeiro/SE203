CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
ASFLAGS = -mcpu=cortex-m4
CFLAGS = -Wall -Werror -Wextra -c -std=gnu99 -g -O1 -nostdlib -mthumb \
				 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m4
CPPFLAGS = -ICMSIS/Device/ST/STM32L4xx/Include -ICMSIS/Include
LDFLAGS = -T ld_ram.lds -nostdlib
DISPOSABLE_OBJS = main.o crt0.o init.o led.o uart.o matrix.o image.o buttons.o irq.o clocks.o
OBJS = $(DISPOSABLE_OBJS)

.PHONY : startdebug clean

main : main.o crt0.o init.o led.o clocks.o uart.o matrix.o image.o buttons.o irq.o
image.o : image.raw
	arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm image.raw image.o


startdebug:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD-speed auto -ir -LocalhostOnly

clean:
			rm -f main
			rm -f $(DISPOSABLE_OBJS)
