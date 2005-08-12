	.text
	xdef DrawGrayPlane8B

| Affiche la map
| In : 
| d0.w : x
| d1.w : y
| a0.l : adresse d'une structure Plane
| a1.l : destination
| a2.l : callback DrawBuffer

DrawGrayPlane8B:
    movem.l  %d3-%d4/%a2-%a3,-(%a7)

    move.l   %a0,%a3

| check if refreshing big_vscreen is necessary
    tst.w    4+2+4+4+4+4(%a3) | test refresh_flag
    bne.s    RefreshBuffer_DrawGrayPlane8B

    move.w   4+2+4+4+4(%a3),%d2 | old x
    move.w   %d2,%d3
    sub.w    %d0,%d2 | old x - new x
    bpl.s    dx_pos_DrawGrayPlane8B
    neg.w    %d2
dx_pos_DrawGrayPlane8B:
    moveq.l  #32,%d4
    cmp.w    %d4,%d2 | old x - new x >= 32
    bge.s    RefreshBuffer_DrawGrayPlane8B

    move.w   %d0,%d2
    and.w    %d4,%d2 | new x & 32
    and.w    %d4,%d3 | old x & 32
    eor.w    %d2,%d3
    bne.s    RefreshBuffer_DrawGrayPlane8B

    move.w   4+2+4+4+4+2(%a3),%d2 | old y
    move.w   %d2,%d3
    sub.w    %d1,%d2 | old y - new y
    bpl.s    dy_pos_DrawGrayPlane8B
    neg.w    %d2
dy_pos_DrawGrayPlane8B:
    cmp.w    %d4,%d2 | old y - new y >= 32
    bge.s    RefreshBuffer_DrawGrayPlane8B

    move.w   %d1,%d2
    and.w    %d4,%d2 | new y & 32
    and.w    %d4,%d3 | old y & 32
    eor.w    %d2,%d3
    beq.s    DrawBuffer_DrawGrayPlane8B

RefreshBuffer_DrawGrayPlane8B:
    clr.w    4+2+4+4+4+4(%a3) | clear refresh_flag

    move.l   (%a3)+,%a0 | matrix adress
    move.w   %d0,%d3
    move.w   %d1,%d4
    lsr.w    #5,%d3
    lsr.w    #5,%d4
    move.w   (%a3)+,%d2 | matrix width
    mulu.w   %d2,%d4 | multiply by map width
    add.w    %d3,%d4
    add.w    %d4,%d4
    add.w    %d4,%d4
    adda.w   %d4,%a0 | matrix of tiles

    move.l   %a2,%d4 | save callback adress
    move.l   (%a3)+,%a2 | array of sprites

    move.l   %a1,%d3 | save destination adress
    move.l   (%a3),%a1 | big_vscreen

    movem.l  %d0-%d1,-(%a7)

    bsr      RefreshGrayBuffer8B

    movem.l  (%a7)+,%d0-%d1

    move.l   %d3,%a1
    move.l   %d4,%a2
    lea.l    -10(%a3),%a3

DrawBuffer_DrawGrayPlane8B:
    move.l   4+2+4(%a3),%a0 | big_vscreen
    move.w   %d0,4+2+4+4+4(%a3) | save new x
    move.w   %d1,4+2+4+4+4+2(%a3) | and new y
    moveq.l  #31,%d2
    and.w    %d2,%d0 | x
    and.w    %d2,%d1 | y

    | a1 already contains destination's adress
    jsr      (%a2) | call a DrawBuffer_MODE function

    movem.l  (%a7)+,%d3-%d4/%a2-%a3
    rts
