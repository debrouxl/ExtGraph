| C prototype: short TestCollide16(short x0,short y0,short x1,short y1,short height,unsigned short* data0, unsigned short* data1) __attribute__((__stkparm__));

.text
.globl TestCollide16
.even

TestCollide16:
    move.l   %d3,-(%sp)
    move.w   %d4,-(%sp)
    lea      4+6(%sp),%a1
    move.w   (%a1)+,%d0
    move.w   (%a1)+,%d1
    move.w   (%a1)+,%d2
    move.w   (%a1)+,%d3
    move.w   (%a1)+,%d4
    move.l   (%a1)+,%a0
    move.l   (%a1),%a1
    
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
    bge.s    __nonegd2_TC16
    neg.w    %d2
    exg      %a0,%a1
    exg      %d1,%d3
__nonegd2_TC16:
    clr.w    %d0

|    if (dx>=16) return 0; // cannot overlap in this case (x difference too large)
    cmpi.w   #16,%d2
    bge.s    1f

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
    bge.s    __nonegd3_TC16
    neg.w    %d3
    adda.w   %d3,%a1
    adda.w   %d3,%a1
    bra.s    4f
__nonegd3_TC16:
    adda.w   %d3,%a0
    adda.w   %d3,%a0

/*
    for (short i=dy;i<height;i++,data0++,data1++) {
        // Let's shift the data of sprite 0 to the left and AND it with
        // the data of sprite 1. If this results in at least one bit set,
        // we have a collision
        if (((unsigned long)*data1) & (((unsigned long)*data0) << dx)) return 1;
    }

    // if we come here we have found no collision!
    return 0;
*/
4:
    sub.w    %d3,%d4
    subq.w   #1,%d4
|    ble.s    0f
    blt.s    1f
3:
    move.w   (%a1)+,%d0 | (unsigned short)*data1
    moveq    #0,%d1
    move.w   (%a0)+,%d1
    lsl.l    %d2,%d1 | ((unsigned short)*data0) << dx
    and.l    %d0,%d1
    dbne     %d4,3b | Good old decrement and branch

    move.l   %d1,%d3 | Why did we come here (speed optimization from tst.l %d3) ?
| If d1 != 0, there's a collision, therefore return non-zero (0 otherwise).
    sne      %d0
    ext.w    %d0
1:
    move.w   (%sp)+,%d4
    move.l   (%sp)+,%d3
    rts
