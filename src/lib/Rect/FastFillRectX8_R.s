| C prototype: void FastFillRectX8_R(void* plane asm("%a0"), unsigned short startcol asm("%d0"), unsigned short starty asm("%d1"), unsigned short lines asm("%d2"), unsigned short bytewidth asm("%d3")) __attribute__((__regparm__(5)));
.text
.globl FastFillRectX8_R
.even
FastFillRectX8_R:
    tst.w    %d3
    beq.s    2f

    move.l   %d4,%a1
    
    add.w    %d1,%d1
    move.w   %d1,%d4
    lsl.w    #4,%d4
    sub.w    %d1,%d4

    add.w    %d0,%d4
    adda.w   %d4,%a0

    moveq    #30,%d4
    sub.w    %d3,%d4
    subq.w   #1,%d3
    moveq    #-1,%d0
0:
    move.w   %d3,%d1
1:
    move.b   %d0,(%a0)+
    dbf      %d1,1b
    adda.w   %d4,%a0
    dbf      %d2,0b
    
    addq.w   #1,%d3                          | Don't forget to restore d3 !

    move.l   %a1,%d4
2:
    rts
