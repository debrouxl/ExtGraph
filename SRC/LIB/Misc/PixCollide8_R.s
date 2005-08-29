| C prototype: char PixCollide8_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height asm("%a1"),void *plane asm("%a0")) __attribute__((__regparm__(6)));
|
| Based on a routine programmed on the TIGCC/TICT message board by several users
| (Jesse Frey - jessef, Samuel Stearley).
| Modified by Lionel Debroux:
| * changed calling convention and registers.

.text
.globl PixCollide8_R
.even


PixCollide8_R:
    sub.w    %d2,%d0
    blt.s    0f

    moveq    #7,%d2
    sub.w    %d0,%d2
    blt.s    0f

    sub.w    %d3,%d1
    blt.s    0f

    cmp.w    %a1,%d1
    bge.s    0f

    btst.b   %d2,0(%a0,%d1.w)
    sne.b    %d0
    rts

0:
    clr.b    %d0
    rts
