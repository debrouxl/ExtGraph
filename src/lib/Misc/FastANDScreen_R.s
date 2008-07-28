| C prototype: void FastANDScreen_R(void* src asm("%a0"), void* dest asm("%a1")) __attribute__((__regparm__(2)));

.text
.globl FastANDScreen_R
.even
FastANDScreen_R:
    .include "Misc/FastScreenMacros.s"
    FastScreenMacro and
