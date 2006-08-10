| void FastCopyScreen160to240_R(short height asm("%d0"),void* src asm("%a0"),void* dest asm("%a1")) __attribute__((__regparm__(2)));  // C prototype

.text
.globl FastCopyScreen160to240_R
.even
FastCopyScreen160to240_R:
    subq.w   #1,%d0
    blt.s    1f

    movem.l  %d3-%d5,-(%sp)

0:
    movem.l  (%a0)+,%d1-%d5
    movem.l  %d1-%d5,(%a1)
    lea      30(%a1),%a1
    dbf      %d0,0b

    movem.l  (%sp)+,%d3-%d5
1:
    rts
