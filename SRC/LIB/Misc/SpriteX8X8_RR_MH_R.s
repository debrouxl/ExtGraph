| C prototype: void SpriteX8X8_RR_MH_R(short h asm("%d0"),unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));

.text
.globl SpriteX8X8_RR_MH_R
.even

SpriteX8X8_RR_MH_R:
    dbf      %d0,4f
    rts

4:
    movem.l  %d3-%d6/%a3,-(%sp)

    move.w   %d1,%d2
    mulu.w   %d0,%d2
    add.w    %d1,%d2
    lea      -1(%a1,%d2.w),%a3         | backupdest.
    adda.w   %d2,%a0
    
    move.w   %d1,%d2                   | backupbytewidth.
    move.w   %d1,%d3
    subq.w   #1,%d3                    | bytewidth-1.

0:
    move.w   %d3,%d1
    move.l   %a3,%a1

1:
    move.b   -(%a0),%d4

    moveq    #4-1,%d5
2:
    move.b   (%a1),%d6
    lsr.b    #1,%d4
    roxr.b   #1,%d6
    move.b   %d6,(%a1)
    suba.w   %d2,%a1

    move.b   (%a1),%d6
    lsr.b    #1,%d4
    roxr.b   #1,%d6
    move.b   %d6,(%a1)
    suba.w   %d2,%a1
    dbf      %d5,2b

    dbf      %d1,1b
    
    subq.w   #1,%d0
    blt.s    3f
    move.w   %d0,%d5
    addq.w   #1,%d5
    andi.w   #7,%d5
    bne.s    0b
    subq.w   #1,%a3
    bra.s    0b

3:
    movem.l  (%sp)+,%d3-%d6/%a3
    rts
