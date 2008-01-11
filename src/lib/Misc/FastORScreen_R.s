| void FastORScreen_R(void* src asm("%a0"),void* dest asm("%a1")) __attribute__((__regparm__(2)));  // C prototype

.text
.globl FastORScreen_R
.even
FastORScreen_R:
    .include "Misc/FastScreenMacros.s"
    FastScreenMacro or
