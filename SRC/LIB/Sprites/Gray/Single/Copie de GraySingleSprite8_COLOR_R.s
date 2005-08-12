| C prototype: void GraySingleSprite8_COLOR_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned char *sprt,unsigned short color,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));
| 
| This is a modified version of GraySprite8_XOR_R, made by David Randall.
| I (Lionel Debroux) switched to local label names and got rid of d3, like in several
| other simple routines.

.text
.globl GraySingleSprite8_COLOR_R
.even

GraySingleSprite8_COLOR_R:
    dbf      %d2,0f
    rts

0:
    pea      (%a2)
    pea      (%a3)

    move.l   4+8(%sp),%a2

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

    move.w   4+12(%sp),%d2

| Since the drawing blocks are all 8 bytes and ordered properly,
| we can go that way.
| NOTE TO USERS: NEVER GIVE A VALUE OUTSIDE OF 0..3 FOR color !!
    lsl.w    #3,%d2
    lea      4f(%pc,%d2.w),%a3

    swap     %d2

    and.w    #0xF,%d0
    moveq    #8,%d1
    sub.w    %d0,%d1
    bge.s    2f

    neg.w    %d1
    
1:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    swap.w   %d0
    lsr.l    %d1,%d0
    
    jmp      (%a3)  | jump to White, LtGray, DkGray, or Black
4:
| White
    not.l    %d0
    and.l    %d0,(%a0)
    and.l    %d0,(%a1)
    bra.s    5f
| LtGray
    or.l     %d0,(%a0)
    not.l    %d0
    and.l    %d0,(%a1)
    bra.s    5f
| DkGray
    or.l     %d0,(%a1)
    not.l    %d0
    and.l    %d0,(%a0)
    bra.s    5f
| Black
    or.l     %d0,(%a0)
    or.l     %d0,(%a1)

5:

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1

    dbf      %d2,1b
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts

2:
    lea      6f-4b(%a3),%a3
3:
    moveq    #0,%d0
    move.b   (%a2)+,%d0
    lsl.w    %d1,%d0
    
    jmp      (%a3)  | jump to White, LtGray, DkGray, or Black
6:
| White
    not.w    %d0
    and.w    %d0,(%a0)
    and.w    %d0,(%a1)
    bra.s    7f
| LtGray
    or.w     %d0,(%a0)
    not.w    %d0
    and.w    %d0,(%a1)
    bra.s    7f
| DkGray
    or.w     %d0,(%a1)
    not.w    %d0
    and.w    %d0,(%a0)
    bra.s    7f
| Black
    or.w     %d0,(%a0)
    or.w     %d0,(%a1)

7:

    lea.l    30(%a0),%a0
    lea.l    30(%a1),%a1
    
    dbf      %d2,3b
    move.l   (%sp)+,%a3
    move.l   (%sp)+,%a2
    rts
