| C prototype: extern void Sprite8Get(short x,short y,short h,void* src,unsigned char* dest)
|
| This routine is faster (about 20%) than the previous C routine, because the
| algorithm was changed.

.text
.globl Sprite8Get
.even

Sprite8Get:
    move.w   0+4+0(%sp),%d0
    move.w   0+4+2(%sp),%d1
    movea.l  0+4+10(%sp),%a1

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    movea.w  %d0,%a0
    adda.l   0+4+6(%sp),%a0

    andi.w   #0xF,%d2
    moveq    #8,%d1
    sub.w    %d2,%d1

    move.w   0+4+4(%sp),%d2
    beq.s    0f
    subq.w   #1,%d2

    tst.w    %d1
    bge.s    2f

    neg.w    %d1
1:
    move.l   (%a0),%d0
    swap     %d0
    rol.l    %d1,%d0
    move.b   %d0,(%a1)+
    lea      30(%a0),%a0
    dbf      %d2,1b
    rts

2:
    move.l   (%a0),%d0
    swap     %d0
    lsr.w    %d1,%d0
    move.b   %d0,(%a1)+
    lea      30(%a0),%a0
    dbf      %d2,2b

0:
    rts
