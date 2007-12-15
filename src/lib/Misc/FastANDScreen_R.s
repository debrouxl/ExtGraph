| void FastANDScreen_R(void* src asm("%a0"),void* dest asm("%a1")) __attribute__((__regparm__(2)));  // C prototype

.text
.globl FastANDScreen_R
.even
FastANDScreen_R:
    move.w   #((3840/16)-1),%d0

0:  move.l   (%a0)+,%d1
    and.l    %d1,(%a1)+
    move.l   (%a0)+,%d1
    and.l    %d1,(%a1)+
    move.l   (%a0)+,%d1
    and.l    %d1,(%a1)+
    move.l   (%a0)+,%d1
    and.l    %d1,(%a1)+
    dbf      %d0,0b

    rts

