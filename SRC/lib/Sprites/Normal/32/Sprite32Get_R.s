| C prototype: void Sprite32Get_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned long* dest asm("%a1"));
|
| This routine is faster (about 30%) than the previous C routine, because the
| algorithm was changed.

.text
.globl Sprite32Get_R
.even

Sprite32Get_R:
    subq.w   #1,%d2
    blt.s    0f

    move.w   %d3,-(%sp)
    move.w   %d4,-(%sp)

    move.w   %d1,%d3
    lsl.w    #4,%d1
    sub.w    %d3,%d1

    move.w   %d0,%d3
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    adda.w   %d0,%a0

    andi.w   #0xF,%d3

    moveq    #16,%d1
    sub.w    %d3,%d1
    
1:
    move.l   (%a0)+,%d0
    lsl.l    %d3,%d0
    move.w   (%a0),%d4
    lsr.w    %d1,%d4
    or.w     %d4,%d0
    move.l   %d0,(%a1)+
    lea      30-4(%a0),%a0
    dbf      %d2,1b

    move.w  (%sp)+,%d4
    move.w  (%sp)+,%d3
0:
    rts
