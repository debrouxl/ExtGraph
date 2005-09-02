| C prototype: char PixCollideX16_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),register short wordwidth asm("%d4"),short height asm("%a1"),unsigned short *sprite asm("%a0")) __attribute__((__regparm__(7)));
|
| Based on a routine programmed on the TIGCC/TICT message board by several users
| (Jesse Frey - jessef, Samuel Stearley, someone else).
| Modified by Lionel Debroux:
| * changed calling convention and registers.
| Modified by Jesse Frey:
| * made it take X8 sprites instead of 8
| Modified by Lionel Debroux:
| * derived from PixCollideX8_R.

|	x0 = x coordinate of point to test
|	y0 = y coordinate of point to test
|	x1 = x coordinate of sprite
|	y1 = y coordinate of sprite
|	bytewidth = bytewidth of sprite
|	height = height of sprite
|	plane = sprite data, assumed to be (bytewidth*height) bytes

.text
.globl PixCollideX16_R
.even

PixCollideX16_R:
    sub.w    %d2,%d0		|%d0=x0-x1
    blt.s    0f			|if(x0<x1) return 0

				|calculate sprite width
    move.w   %d4,%d2		|%d2=wordwidth
    lsl.w    #4,%d2		|%d2*=16
    subq.w   #1,%d2		|%d2-=1

    sub.w    %d0,%d2		|%d2=x_diff-pixWidth
    blt.s    0f			|if(%d0<0) return 0

    sub.w    %d3,%d1		|%d1=y0-y1
    blt.s    0f			|if(%d1<0) return 0

    cmp.w    %a1,%d1
    bge.s    0f
				|calculate offset
    move.w   %d2,%d0		|%d0=x pix ofset
    lsr.w    #3,%d0		|%d0/=8 (%d0 is now x offset in bytes)
    mulu.w   %d4,%d1		|%d1*=wordwidth
    add.w    %d1,%d1            |%d1*=2 (%d1 is now y offset in bytes)
    add.w    %d0,%d1		|%d1+=x offset

    andi.w   #7,%d2		|%d2=bit num

    btst.b   %d2,0(%a0,%d1.w)	|test the calculated bit in the sprite
    sne.b    %d0		|return (is bit set)?0xFF:0
    rts

0:
    clr.w    %d0	|return 0
    rts