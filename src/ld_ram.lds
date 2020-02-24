ENTRY(_start)

MEMORY
  {
    rom (rx) : ORIGIN = 0x00000000, LENGTH = 1M
    sram1 (wx): ORIGIN = 0x20000000, LENGTH = 96K
    sram2 (w): ORIGIN = 0x10000000, LENGTH = 32K
  }

SECTIONS
{

  .irq : {
    *(.irq)
  } > rom

 .textrom : {
    _textrom = . ;
    *(.textrom)
    _etextrom = . ;
  } > rom

  .text : {
    _text = . ;
    *(.text)
    _etext = . ;
  } > sram1 AT > rom


  .rodata : {
    *(.rodata)
    _erodata = . ;
  } > rom


  .data  : {
    _data = . ;
    *(.data)
    _edata = . ;
  } > sram1 AT > rom


  .bss : {
    _bstart = . ;
    *(.bss) *(COMMON)
    _bend = . ;
  } > sram1
}


_initsp = ORIGIN(sram2) + LENGTH(sram2);

scr1 = LOADADDR(.text);

scr2 = LOADADDR(.data);

scr3 = LOADADDR(.irq);

