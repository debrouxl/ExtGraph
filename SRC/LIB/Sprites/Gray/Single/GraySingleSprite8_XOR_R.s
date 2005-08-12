| C prototype: void GraySingleSprite8_XOR_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned char *sprt,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));
| 
| This is a modified version of GraySprite8_XOR_R, made by David Randall.
| I (Lionel Debroux) switched to local label names and got rid of d3, like in several
| other simple routines.

.text
.globl GraySingleSprite8_XOR_R
.even

GraySingleSprite8_XOR_R:
    dbf      %d2,0f
    rts

0:
    pea      (%a2)
    move.l   4+4(%sp),%a2

    swap     %d2

    move.w   %d1,%d2	| d2 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d2,%d1	| d1 = 15*y

    move.w   %d0,%d2	| d2 = x
    lsr.w    #4,%d2	| d2 = x/16

    add.w    %d2,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = 30*y + x/8
    adda.w   %d1,%a0	| a0 += offset
    adda.w   %d1,%a1	| a1 += offset

    swap     %d2

    andi.w   #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    2f

    neg.w    %d1
    
| White on Black and
| Black on White and
| Dk Gray on Lt Gray and
| Lt Gray on Dk Gray
1:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    eor.l    %d0,(%a0)
    eor.l    %d0,(%a1)

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,1b
    move.l   (%sp)+,%a2
    rts

3:
    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
2:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0
    eor.w    %d0,(%a0)
    eor.w    %d0,(%a1)

    dbf      %d2,3b

    move.l   (%sp)+,%a2
    rts
