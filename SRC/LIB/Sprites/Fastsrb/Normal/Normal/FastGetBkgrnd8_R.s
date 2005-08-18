| C prototype: void FastGetBkgrnd8_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned short* dest asm("%a1"));
|
| This routine is a fast version of Sprite8Get_R, it must be used in conjunction
| with FastPutBkgrnd8_R.
| These routines are designed for programs where redrawing everything every frame
| is detrimental to speed.

.text
.globl FastGetBkgrnd8_R
.even

FastGetBkgrnd8_R:
    subq.w   #1,%d2
    blt.s    0f

    move.w   %d2,(%a1)+ | height
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
    move.w   %d0,(%a1)+ | offset

    andi.w   #0xF,%d2
    move.w   %d2,(%a1)+ | x&15
    cmpi.w   #8,%d2
    bgt.s    3f

    swap     %d2
    lsr.w    #1,%d2
    bcs.s    1f
    lea      -30(%a0),%a0
    bra.s    2f

1:
    move.w   (%a0),(%a1)+
2:
    move.w   30(%a0),(%a1)+
    lea      60(%a0),%a0
    dbf      %d2,1b

    rts


3:
    swap     %d2
    lsr.w    #1,%d2
    bcs.s    4f
    lea      -30(%a0),%a0
    bra.s    5f

4:
    move.l   (%a0),(%a1)+
5:
    move.l   30(%a0),(%a1)+
    lea      60(%a0),%a0
    dbf      %d2,4b

0:
    rts
