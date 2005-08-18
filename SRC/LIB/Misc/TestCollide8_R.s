| C prototype: short TestCollide8_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height,unsigned char* data0 asm("%a0"),unsigned char* data1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl TestCollide8_R
.even

TestCollide8_R:
    move.l   %d3,-(%sp)

/*
    dx = x1-x0;
    if (dx < 0) {
        // if sprite 0 is right of sprite 1 just exchange
        // all necessary variables so we can still assume
        // sprite 0 is left of sprite 1 ...
        dx = -dx;
        EXT_XCHG(data0,data1);
        EXT_XCHG(y0,y1);
    }
*/
    sub.w    %d0,%d2
    bge.s    __nonegd2_TC8_R
    neg.w    %d2
    exg      %a0,%a1
    exg      %d1,%d3
__nonegd2_TC8_R:
    clr.w    %d0

|    if (dx>=8) return 0; // cannot overlap in this case (x difference too large)
    cmpi.w   #8,%d2
    bge.s    2f

/*
    dy = y1-y0;
    if (dy > 0) {
        data0+=dy;
    }
    else {
        dy = -dy;
        data1+=dy;
    }
*/    
    sub.w    %d1,%d3
    bge.s    __nonegd3_TC8_R
    neg.w    %d3
    adda.w   %d3,%a1
    bra.s    4f
__nonegd3_TC8_R:
    adda.w   %d3,%a0

/*
    for (short i=dy;i<height;i++,data0++,data1++) {
        // Let's shift the data of sprite 0 to the left and AND it with
        // the data of sprite 1. If this results in at least one bit set,
        // we have a collision
        if (((unsigned short)*data1) & (((unsigned short)*data0) << dx)) return 1;
    }

    // if we come here we have found no collision!
    return 0;
*/
4:
    move.w   %d4,-(%sp)
    move.w   4+6(%sp),%d4
    sub.w    %d3,%d4
    subq.w   #1,%d4
|    ble.s    0f
    blt.s    1f
3:
    move.b   (%a1)+,%d0 | (unsigned short)*data1
    clr.w    %d1
    move.b   (%a0)+,%d1
    lsl.w    %d2,%d1 | ((unsigned short)*data0) << dx
    and.w    %d0,%d1
    dbne     %d4,3b | Good old decrement and branch

    tst.w    %d1 | Why did we come here ?
| If d3 != 0, there's a collision, therefore return non-zero (0 otherwise).
    sne      %d0
    ext.w    %d0
1:
    move.w   (%sp)+,%d4
2:
    move.l   (%sp)+,%d3
    rts
