| void FastCopyScreen(void* src,void* dest) __attribute__((__stkparm__));  // C prototype

.text
.globl FastCopyScreen
.even
FastCopyScreen:
    move.l   4+0(%sp),%a0
    move.l   4+4(%sp),%a1
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
