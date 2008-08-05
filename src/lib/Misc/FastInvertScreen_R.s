| C prototype: void FastInvertScreen_R(const void* src asm("%a0")) __attribute__((__regparm__(1)));

.text
.globl FastInvertScreen_R
.even
FastInvertScreen_R:
    move.w   #((3840/16)-1),%d0

0:  not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    not.l    (%a0)+
    dbf      %d0,0b

    rts
