| C prototype: void FastSprite32_MIRROR_H_R (short h asm("%d2"), unsigned long *sprt asm("%a0"), unsigned long *dest asm("%a1"));

.text
.globl FastSprite32_MIRROR_H_R
.even

FastSprite32_MIRROR_H_R:
    subq.w   #1,%d2
    bmi.s    0f

    move.l   %a2,-(%sp)
    lea.l    FastSpriteX_MIRROR_H_table,%a2
    addq.l   #4,%a1
    moveq    #0,%d0
    
1:
    move.b   (%a0)+,%d0 | 8
    move.b   0(%a2,%d0.w),-(%a1) | 18
    
    move.b   (%a0)+,%d0 | 8
    move.b   0(%a2,%d0.w),-(%a1) | 18

    move.b   (%a0)+,%d0 | 8
    move.b   0(%a2,%d0.w),-(%a1) | 18

    move.b   (%a0)+,%d0 | 8
    move.b   0(%a2,%d0.w),-(%a1) | 18

    addq.l   #8,%a1 | 8
| Total: 4 * (8 + 18) + 8 = 112 clocks.

    dbf      %d2,1b
    
    move.l   (%sp)+,%a2
0:
    rts
