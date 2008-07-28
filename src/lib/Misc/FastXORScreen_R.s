| C prototype: void FastXORScreen_R(void* src asm("%a0"), void* dest asm("%a1")) __attribute__((__regparm__(2)));

.text
.globl FastXORScreen_R
.even
FastXORScreen_R:
    .include "Misc/FastScreenMacros.s"
    FastScreenMacro eor
