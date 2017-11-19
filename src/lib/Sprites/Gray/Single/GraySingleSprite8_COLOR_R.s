| C prototype: void GraySingleSprite8_COLOR_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprt, short color, void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));
| 
| This is a modified version of GraySprite8_XOR_R, made by David Randall.
| I (Lionel Debroux) switched to local label names and got rid of d3, like in several
| other simple routines; I switched to self-modifying code (but I'm not very
| satisfied with either solution, since the overhead of both SMC and
| always-jump-all-over-the-place is important on such a small routine).

.text
.globl GraySingleSprite8_COLOR_R
.even

GraySingleSprite8_COLOR_R:
    subq.w   #1,%d2
    blt.s    0f    

    pea      (%a2)
    pea      (%a3)

    swap     %d2

    move.w   %d1,%d2	| d2 = y
    lsl.w    #4,%d1	| d1 = 16*y
    sub.w    %d2,%d1	| d1 = 15*y

    move.w   %d0,%d2	| d2 = x
    lsr.w    #4,%d2	| d2 = x/16

    add.w    %d2,%d1	| d1 = 15*y + x/16
    add.w    %d1,%d1	| d1 = y*PLANE_BYTE_WIDTH + x/8
    adda.w   %d1,%a0	| a0 += offset
    adda.w   %d1,%a1	| a1 += offset

    move.w   4+12(%sp),%d2

| SMC.
| NOTE TO USERS: NEVER GIVE A VALUE OUTSIDE OF 0..3 FOR color !!
    add.w    %d2,%d2 |
    move.w   %d2,%d1 |
    add.w    %d2,%d2 |
    add.w    %d1,%d2 | d2 *= 6

    and.w    #0xF,%d0
    moveq    #8,%d1
    lea      3f(%pc),%a2
    lea      8f(%pc,%d2.w),%a3
    move.l   #0x4840E2B8,(%a2)+ | swap %d0; ror.l %d1,%d0
    sub.w    %d0,%d1
    blt.s    6f
    lea      9f-8f(%a3),%a3
    move.l   #0x4E71E368,-4(%a2) | nop; lsl.w %d1,%d0
6:
    move.l   (%a3)+,(%a2)+
    move.w   (%a3)+,(%a2)+

    move.l   4+8(%sp),%a2

    swap     %d2
    
    tst.w    %d1
    bge.s    1f
    
    neg.w    %d1
1:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
3:
| Will be patched.
    nop
    nop
    nop
    nop
    nop

    lea.l    PLANE_BYTE_WIDTH(%a0),%a0
    lea.l    PLANE_BYTE_WIDTH(%a1),%a1

    dbf      %d2,1b
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2

0:
    rts

8:
| White
    not.l    %d0
    and.l    %d0,(%a0)
    and.l    %d0,(%a1)
| LGray
    or.l     %d0,(%a0)
    not.l    %d0
    and.l    %d0,(%a1)
| DGray
    or.l     %d0,(%a1)
    not.l    %d0
    and.l    %d0,(%a0)
| Black
    or.l     %d0,(%a0)
    or.l     %d0,(%a1)
    nop

9:
| White
    not.w    %d0
    and.w    %d0,(%a0)
    and.w    %d0,(%a1)
| LGray
    or.w     %d0,(%a0)
    not.w    %d0
    and.w    %d0,(%a1)
| DGray
    or.w     %d0,(%a1)
    not.w    %d0
    and.w    %d0,(%a0)
| Black
    or.w     %d0,(%a0)
    or.w     %d0,(%a1)
    nop
