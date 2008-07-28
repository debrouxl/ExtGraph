| C prototype: void GrayFillScreen2B_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),unsigned long lcolor asm("%d0"),unsigned long dcolor asm("%d1")) __attribute__((__regparm__(4)));

.text
.globl GrayFillScreen2B_R
.even
GrayFillScreen2B_R:
    movem.l  %d3-%d7/%a2-%a5,-(%sp)

    lea      (0xf00,%a0),%a0
    move.l   %d0,%d2
    move.l   %d0,%d3
    move.l   %d0,%d4
    move.l   %d0,%d5
    move.l   %d0,%d6
    move.l   %d0,%a2
    move.l   %d0,%a3
    move.l   %d0,%a4
    move.l   %d0,%a5
    moveq    #11,%d7
0:  movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    movem.l  %d0/%d2-%d6/%a2-%a5,-(%a0)
    dbf      %d7,0b

    lea      (0xf00,%a1),%a1
    move.l   %d1,%d2
    move.l   %d1,%d3
    move.l   %d1,%d4
    move.l   %d1,%d5
    move.l   %d1,%d6
    move.l   %d1,%a2
    move.l   %d1,%a3
    move.l   %d1,%a4
    move.l   %d1,%a5
    moveq    #11,%d7
0:  movem.l  %d1-%d6/%a2-%a5,-(%a1)
    movem.l  %d1-%d6/%a2-%a5,-(%a1)
    movem.l  %d1-%d6/%a2-%a5,-(%a1)
    movem.l  %d1-%d6/%a2-%a5,-(%a1)
    movem.l  %d1-%d6/%a2-%a5,-(%a1)
    movem.l  %d1-%d6/%a2-%a5,-(%a1)
    movem.l  %d1-%d6/%a2-%a5,-(%a1)
    movem.l  %d1-%d6/%a2-%a5,-(%a1)
    dbf      %d7,0b

    movem.l  (%sp)+,%d3-%d7/%a2-%a5
    rts
