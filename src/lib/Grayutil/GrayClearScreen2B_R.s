| C prototype: void GrayClearScreen2B_R(void* lightplane asm("%a0"),void* darkplane asm("%a1")) __attribute__((__regparm__(2)));

.text
.globl GrayClearScreen2B_R
.even
GrayClearScreen2B_R:
    movem.l  %d3-%d7/%a2-%a4,-(%sp)
    lea      (0xf00,%a0),%a0
    lea      (0xf00,%a1),%a1
    moveq    #0,%d0
    moveq    #0,%d1
    moveq    #0,%d2
    moveq    #0,%d3
    moveq    #0,%d4
    moveq    #0,%d5
    moveq    #0,%d6
    moveq    #23,%d7
    movea.l  %d0,%a2
    movea.l  %d0,%a3
    movea.l  %d0,%a4
0:  movem.l  %d0-%d6/%a2-%a4,-(%a0)
    movem.l  %d0-%d6/%a2-%a4,-(%a1)
    movem.l  %d0-%d6/%a2-%a4,-(%a0)
    movem.l  %d0-%d6/%a2-%a4,-(%a1)
    movem.l  %d0-%d6/%a2-%a4,-(%a0)
    movem.l  %d0-%d6/%a2-%a4,-(%a1)
    movem.l  %d0-%d6/%a2-%a4,-(%a0)
    movem.l  %d0-%d6/%a2-%a4,-(%a1)
    dbf      %d7,0b
    movem.l  (%sp)+,%d3-%d7/%a2-%a4
    rts
