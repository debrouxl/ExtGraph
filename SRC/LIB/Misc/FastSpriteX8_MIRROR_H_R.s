| C prototype: void FastSpriteX8_MIRROR_H_R (register short h asm("%d2"), register short bytewidth asm("%d1"), register void *sprt asm("%a0"), register void *dest asm("%a1"));

.text
.globl FastSprite8_MIRROR_H_R
.even

FastSprite8_MIRROR_H_R:
    dbf      %d2,0f
    rts

0:
    adda.w   %d1,%a1
    dbf      %d1,1f
    rts

1:
    move.l   %a2,-(%sp)
    move.w   %d3,-(%sp)
    lea.l    FastSpriteX_MIRROR_H_table,%a2
    move.w   %d1,%d3
    moveq    #0,%d0
    
2:
    move.b   (%a0)+,%d0 | 8
    move.b   0(%a2,%d0.w),-(%a1) | 18

    dbf      %d1,2b
    lea      1(%a1,%d3.w),%a1
    move.w   %d3,%d1
    dbf      %d2,2b
    
    move.w   (%sp)+,%d3
    move.l   (%sp)+,%a2
    rts
