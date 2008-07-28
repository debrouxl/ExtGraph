| C prototype: void FastCopyScreen_R(void* src asm("%a0"), void* dest asm("%a1")) __attribute__((__regparm__(2)));

.text
.globl FastCopyScreen_R
.even
FastCopyScreen_R:
    moveq    #9,%d0
    movem.l  %d3-%d7/%a2-%a6,-(%sp)

0:  movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(%a1)

    movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(48,%a1)

    movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(96,%a1)

    movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(144,%a1)

    movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(192,%a1)

    movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(240,%a1)

    movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(288,%a1)

    movem.l  (%a0)+,%d1-%d7/%a2-%a6
    movem.l  %d1-%d7/%a2-%a6,(336,%a1)

    lea      (%a1,384),%a1
    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d7/%a2-%a6
    rts
