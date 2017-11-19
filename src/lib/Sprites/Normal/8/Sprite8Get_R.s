| C prototype: void Sprite8Get_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const void* src asm("%a0"), unsigned char* dest asm("%a1")) __attribute__((__regparm__));
|
| This routine is faster (about 20%) than the previous C routine, because the
| algorithm was changed.
| An optimization (4 clocks) was made by Ximoon, jackiechan told me about it.

.include "common.s"

.text
.globl Sprite8Get_R
.even

Sprite8Get_R:
    subq.w   #1,%d2
    blt.s    0f

    swap     %d2    

    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d2

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    adda.w   %d0,%a0

    andi.w   #0xF,%d2
    moveq    #8,%d1
    sub.w    %d2,%d1
    bge.s    3f

    neg.w    %d1
    swap     %d2
1:
    move.l   (%a0),%d0
    swap     %d0
    rol.l    %d1,%d0
    move.b   %d0,(%a1)+
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,1b
    
    rts

3:
    swap     %d2
2:
    move.w   (%a0),%d0
    lsr.w    %d1,%d0
    move.b   %d0,(%a1)+
    lea      PLANE_BYTE_WIDTH(%a0),%a0
    dbf      %d2,2b
0:
    rts
