| C prototype: void GrayFastGetBkgrnd16_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src1 asm("%a0"),void* src2 asm("%a1"),unsigned short* dest asm("%a2"));
|
| This routine is a fast grayscale version of Sprite16Get_R, it must be used in
| conjunction with GrayFastPutBkgrnd16_R.
| These routines are designed for programs where redrawing everything every frame
| is detrimental to speed.

.text
.globl GrayFastGetBkgrnd16_R
.even

GrayFastGetBkgrnd16_R:
    move.l   %a2,-(%sp)

    subq.w   #1,%d2
    blt.s    2f

    move.w   %d2,(%a2)+ | height
    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,(%a2)+ | x
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0
    
    adda.w   %d0,%a0
    adda.w   %d0,%a1
    move.w   %d0,(%a2)+ | offset

    swap     %d2
    lsr.w    #1,%d2
    bcs.s    0f
    lea      -30(%a0),%a0
    lea      -30(%a1),%a1
    bra.s    1f

0:
    move.l   (%a0),(%a2)+
    move.l   (%a1),(%a2)+
1:
    move.l   30(%a0),(%a2)+
    move.l   30(%a1),(%a2)+
    lea      60(%a0),%a0
    lea      60(%a1),%a1
    dbf      %d2,0b

2:
    move.l   (%sp)+,%a2
    rts
