| C prototype: void FastCopyScreen160to240NC_R(unsigned short height asm("%d0"), void* src asm("%a0"), void* dest asm("%a1")) __attribute__((__regparm__(3)));

.text
.globl FastCopyScreen160to240NC_R
.even
FastCopyScreen160to240NC_R:
    movem.l  %d3-%d5,-(%sp)
    moveq    #100,%d1
    sub.w    %d0,%d1

    subq.w   #1,%d0
    blt.s    1f

    lsr.w    #1,%d1
    addi.w   #14,%d1
    add.w    %d1,%d1
    move.w   %d1,%d2
    lsl.w    #4,%d2
    sub.w    %d1,%d2
    lea      32/8(%a0,%d2.w),%a0
0:
    movem.l  (%a0)+,%d1-%d5
    movem.l  %d1-%d5,(%a1)
    lea      30(%a1),%a1
    dbf      %d0,0b

1:
    movem.l  (%sp)+,%d3-%d5
    rts
