| C prototype: void GrayIShadowPlanesTo_R(register void *src0 asm("%a0"),register void *src1 asm("%a1"),void *dest0,void *dest1) __attribute__((__stkparm__));
|
| Derived from GrayShadowPlanesX16_R. Acts like a combination of 
| GrayShadowPlanesX16_R and FastCopyScreen_R (240x128 planes only).

.text
.globl GrayShadowPlanesTo_R
.even

GrayShadowPlanesTo_R:
    movem.l  %d3/%a2-%a3,-(%sp)

    move.w   #0xF00/4/2-1,%d0
    move.l   4+12(%sp),%a2
    move.l   4+12+4(%sp),%a3

0:
    move.l   (%a0)+,%d1
    move.l   (%a1)+,%d2

    move.l   %d1,%d3
    not.l    %d3
    or.l     %d2,%d3
    or.l     %d1,%d2

    move.l   %d3,(%a2)+
    move.l   %d2,(%a3)+


    move.l   (%a0)+,%d1
    move.l   (%a1)+,%d2

    move.l   %d1,%d3
    not.l    %d3
    or.l     %d2,%d3
    or.l     %d1,%d2

    move.l   %d3,(%a2)+
    move.l   %d2,(%a3)+

    dbf      %d0,0b

    movem.l  (%sp)+,%d3/%a2-%a3

    rts
