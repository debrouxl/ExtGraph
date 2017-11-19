| C prototype: void GrayFastGetBkgrnd8_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const void* src1 asm("%a0"), const void* src2 asm("%a1"), unsigned short* dest asm("%a2"));
|
| This routine is a fast grayscale version of Sprite8Get_R, it must be used in
| conjunction with GrayFastPutBkgrnd8_R.
| These routines are designed for programs where redrawing everything every frame
| is detrimental to speed.

.text
.globl GrayFastGetBkgrnd8_R
.even

GrayFastGetBkgrnd8_R:
    move.l   %a2,-(%sp)

    subq.w   #1,%d2
    blt.s    0f

    move.w   %d2,(%a2)+ | height
    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

| RFS: cannot use the moveq #15,%d2; and.w %d0,%d2 trick because upper part of d2 is used !
    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0
    
    adda.w   %d0,%a0
    adda.w   %d0,%a1
    move.w   %d0,(%a2)+ | offset

    andi.w   #0xF,%d2
    move.w   %d2,(%a2)+ | x&15
    cmpi.w   #8,%d2
    bgt.s    3f

    swap     %d2
    lsr.w    #1,%d2
    bcs.s    1f
    lea      -PLANE_BYTE_WIDTH(%a0),%a0
    lea      -PLANE_BYTE_WIDTH(%a1),%a1
    bra.s    2f

1:
    move.w   (%a0),(%a2)+
    move.w   (%a1),(%a2)+
2:
    move.w   PLANE_BYTE_WIDTH(%a0),(%a2)+
    move.w   PLANE_BYTE_WIDTH(%a1),(%a2)+
    lea      2*PLANE_BYTE_WIDTH(%a0),%a0
    lea      2*PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,1b

    move.l   (%sp)+,%a2
    rts


3:
    swap     %d2
    lsr.w    #1,%d2
    bcs.s    4f
    lea      -PLANE_BYTE_WIDTH(%a0),%a0
    lea      -PLANE_BYTE_WIDTH(%a1),%a1
    bra.s    5f

4:
    move.l   (%a0),(%a2)+
    move.l   (%a1),(%a2)+
5:
    move.l   PLANE_BYTE_WIDTH(%a0),(%a2)+
    move.l   PLANE_BYTE_WIDTH(%a1),(%a2)+
    lea      2*PLANE_BYTE_WIDTH(%a0),%a0
    lea      2*PLANE_BYTE_WIDTH(%a1),%a1
    dbf      %d2,4b

0:
    move.l   (%sp)+,%a2
    rts
