| C prototype: void FastGetBkgrnd16_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const void* src asm("%a0"), unsigned short* dest asm("%a1"));
|
| This routine is a fast version of Sprite16Get_R, it must be used in conjunction
| with FastPutBkgrnd16_R.
| These routines are designed for programs where redrawing everything every frame
| is detrimental to speed.

.text
.globl FastGetBkgrnd16_R
.even

FastGetBkgrnd16_R:
    subq.w   #1,%d2
    blt.s    0f

    move.w   %d2,(%a1)+ | height
    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,(%a1)+ | x
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0
    
    adda.w   %d0,%a0
    move.w   %d0,(%a1)+ | offset

    swap     %d2
    lsr.w    #1,%d2
    bcs.s    2f
    lea      -PLANE_BYTE_WIDTH(%a0),%a0
    bra.s    1f

2:
    move.l   (%a0),(%a1)+
1:
    move.l   PLANE_BYTE_WIDTH(%a0),(%a1)+
    lea      2*PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,2b

0:
    rts
