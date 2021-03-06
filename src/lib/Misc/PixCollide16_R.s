| C prototype: char PixCollide16_R(short x0 asm("%d0"), short y0 asm("%d1"), short x1 asm("%d2"), short y1 asm("%d3"), unsigned short height asm("%a1"), const unsigned short *sprite asm("%a0")) __attribute__((__regparm__(6)));
|
| Based on a routine programmed on the TIGCC/TICT message board by several users
| (Jesse Frey - jessef, Samuel Stearley).
| Modified by Lionel Debroux:
| * changed the calling convention and registers.
| Bugfix by Jesse Frey
| * changed to a PixCollideX8 with a hardcoded bytewidth

.text
.globl PixCollide16_R
.even


PixCollide16_R:
    sub.w    %d2,%d0		|%d0=x0-x1
    blt.s    0f			|if(x0<x1) return 0

    cmp.w    #16,%d0		|if(%d0>16)
    bge      0f			|return 0

    sub.w    %d3,%d1		|%d1=y0-y1
    blt.s    0f			|if(%d1<0) return 0

    cmp.w    %a1,%d1		|if(%d1>height)
    bge.s    0f			|return 0

				|calculate offset
    move.w   %d0,%d2		|save %d0
    lsr.w    #3,%d0		|%d0/=8 (%d0 is now x offset in bytes)
    add.w    %d1,%d1		|%d1*=2(bytewidth)
    add.w    %d0,%d1		|%d1+=x offset

    not.w    %d2		|%d2=bit num

    btst.b   %d2,0(%a0,%d1.w)	|test the calculated bit in the sprite
    sne.b    %d0		|return (is bit set)?0xFF:0
    rts

0:
    clr.w    %d0	|return 0
    rts
