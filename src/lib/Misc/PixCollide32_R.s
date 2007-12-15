| C prototype: char PixCollide32_R(short x0 asm("%d0"), short y0 asm("%d1"), short x1 asm("%d2"), short y1 asm("%d3"), short height asm("%a1"), const unsigned long * sprite asm("%a0")) __attribute__((__regparm__(6)));
|
| Based on a routine programmed on the TIGCC/TICT message board by several users
| (Jesse Frey - jessef, Samuel Stearley).
| Modified by Lionel Debroux:
| * changed the calling convention and registers.
| Bugfix by Jesse Frey
| * changed to a PixCollideX8 with a hardcoded bytewidth
| Modified by Jesse Frey
| * now works more like PixCollide8 by moving sprite data to a register

.text
.globl PixCollide32_R
.even


PixCollide32_R:
    sub.w    %d2,%d0
    blt.s    0f

    moveq    #31,%d2
    sub.w    %d0,%d2
    blt.s    0f

    sub.w    %d3,%d1
    blt.s    0f

    cmp.w    %a1,%d1
    bge.s    0f

    lsl.w    #2,%d1		| y-offset to byte offset (y*4)
    move.l   0(%a0,%d1.w),%d0	| we must use a register because that is all btst.l can deal with
    btst.l   %d2,%d0
    sne.b    %d0
    rts

0:
    clr.b    %d0		|return 0
    rts
