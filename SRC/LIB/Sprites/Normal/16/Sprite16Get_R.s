| C prototype: void Sprite16Get_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register void* src asm("%a0"),register unsigned short* dest asm("%a1"));
|
| This routine is faster (about 10%) than the previous C routine, because the
| algorithm was changed.
| An optimization (4 clocks) was made by Ximoon, jackiechan told me about it.

.text
.globl Sprite16Get_R
.even

Sprite16Get_R:
    dbf      %d2,0f
    rts

0:
    swap     %d2

    move.w   %d1,%d2
    lsl.w    #4,%d1
    sub.w    %d2,%d1

    move.w   %d0,%d2
    lsr.w    #4,%d0
    add.w    %d1,%d0
    add.w    %d0,%d0

    adda.w   %d0,%a0

    andi.w   #0xF,%d2
    moveq    #16,%d1
    sub.w    %d2,%d1

    swap     %d2

1:
    move.l   (%a0),%d0
    lsr.l    %d1,%d0
    move.w   %d0,(%a1)+
    lea      30(%a0),%a0
    dbf      %d2,1b

    rts
