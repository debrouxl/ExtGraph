| void FastClearScreen_R(void *plane asm("%a0"));

.text
.globl FastClearScreen_R
.even
FastClearScreen_R:
    movem.l  %d3-%d7/%a2-%a3,-(%sp)
    lea      (0xf00,%a0),%a0
    moveq    #0,%d0
    moveq    #0,%d1
    moveq    #0,%d2
    moveq    #0,%d3
    moveq    #0,%d4
    moveq    #0,%d5
    moveq    #0,%d6
    moveq    #23,%d7
    movea.l  %d0,%a1
    movea.l  %d0,%a2
    movea.l  %d0,%a3
0:  movem.l  %d0-%d6/%a1-%a3,-(%a0)
    movem.l  %d0-%d6/%a1-%a3,-(%a0)
    movem.l  %d0-%d6/%a1-%a3,-(%a0)
    movem.l  %d0-%d6/%a1-%a3,-(%a0)
    dbf      %d7,0b
    movem.l  (%sp)+,%d3-%d7/%a2-%a3
    rts
