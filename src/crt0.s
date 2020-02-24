  .syntax unified
  .global _start
  .thumb
  .section .textrom, "ax", %progbits
  
  .thumb_func
_start:
  ldr sp, =_initsp
  bl init_text
  bl init_bss
  bl init_data
  bl main


_exit:
  bl _exit
