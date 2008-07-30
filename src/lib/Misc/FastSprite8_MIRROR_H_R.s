| C prototype: void FastSprite8_MIRROR_H_R(unsigned short height asm("%d2"), unsigned char *sprt asm("%a0"), unsigned char *dest asm("%a1"));

.text
.globl FastSprite8_MIRROR_H_R
.even

FastSprite8_MIRROR_H_R:
    subq.w   #1,%d2
    bmi.s    0f

    move.l   %a2,-(%sp)
    lea.l    FastSpriteX_MIRROR_H_table,%a2
    moveq    #0,%d0
    
1:
    move.b   (%a0)+,%d0 | 8
    move.b   0(%a2,%d0.w),(%a1)+ | 18

    dbf      %d2,1b
    
    move.l   (%sp)+,%a2
0:
    rts
