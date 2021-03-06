	.text
	xdef DrawAnimatedPlane16W

| Affiche la map
| In : 
| d0.w : x
| d1.w : y
| a0.l : adresse d'une structure AnimatedPlane
| a1.l : destination
| a2.l : callback DrawBuffer

DrawAnimatedPlane16W:
    movem.l  %d3-%d4/%a2-%a4,-(%a7)

    move.l   %a0,%a4

| check if tiles need to be animated
    lea.l    4+2+4+4+4+4+2+4+2+2+2(%a4),%a3
    move.w   (%a3)+,%d2 | step lenght
    addq.w   #1,(%a3) | increment frame counter
    sub.w    (%a3),%d2
    bne.s    No_anim_DrawAnimatedPlane16W

    move.w   %d2,(%a3) | clear frame counter
    subq.l   #6,%a3
    move.w   (%a3)+,%d2 | step number
    addq.w   #1,(%a3) | increment step counter
    sub.w    (%a3),%d2
    bne.s    RefreshAnimatedBuffer_DrawAnimatedPlane16W
    move.w   %d2,(%a3) | clear step counter
    bra.s    RefreshAnimatedBuffer_DrawAnimatedPlane16W

No_anim_DrawAnimatedPlane16W:
| check if refreshing big_vscreen is asked
    tst.w    4+2+4+4+4+4(%a4) | test refresh_flag
    bne.s    RefreshAnimatedBuffer_DrawAnimatedPlane16W

| check if refreshing big_vscreen is needed
    move.w   4+2+4+4+4(%a4),%d2 | old x
    move.w   %d2,%d3
    sub.w    %d0,%d2 | old x - new x
    bpl.s    dx_pos_DrawAnimatedPlane16W
    neg.w    %d2
dx_pos_DrawAnimatedPlane16W:
    moveq.l  #32,%d4
    cmp.w    %d4,%d2 | old x - new x >= 32
    bge.s    RefreshAnimatedBuffer_DrawAnimatedPlane16W

    move.w   %d0,%d2
    and.w    %d4,%d2 | new x & 32
    and.w    %d4,%d3 | old x & 32
    eor.w    %d2,%d3
    bne.s    RefreshAnimatedBuffer_DrawAnimatedPlane16W

    move.w   4+2+4+4+4+2(%a4),%d2 | old y
    move.w   %d2,%d3
    sub.w    %d1,%d2 | old y - new y
    bpl.s    dy_pos_DrawAnimatedPlane16W
    neg.w    %d2
dy_pos_DrawAnimatedPlane16W:
    cmp.w    %d4,%d2 | old y - new y >= 32
    bge.s    RefreshAnimatedBuffer_DrawAnimatedPlane16W

    move.w   %d1,%d2
    and.w    %d4,%d2 | new y & 32
    and.w    %d4,%d3 | old y & 32
    eor.w    %d2,%d3
    beq.s    DrawBuffer_DrawAnimatedPlane16W

RefreshAnimatedBuffer_DrawAnimatedPlane16W:
    clr.w    4+2+4+4+4+4(%a4) | clear refresh_flag

    movea.l  (%a4)+,%a0 | matrix adress
    move.w   %d0,%d3
    move.w   %d1,%d4
    lsr.w    #5,%d3
    lsr.w    #5,%d4
    move.w   (%a4)+,%d2 | matrix width
    mulu.w   %d2,%d4 | multiply by map width
    add.w    %d3,%d4
    add.w    %d4,%d4
    add.w    %d4,%d4 | * sizeof(short)
    adda.w   %d4,%a0 | matrix of tiles

    move.l   %a2,%d4 | save callback adress
    move.l   (%a4)+,%a2 | array of sprites

    move.w   4+4+4+2+4(%a4),%d3 | number of animations
    mulu.w   4+4+4+2+4+2+2(%a4),%d3
    add.w    %d3,%d3 | (tabanim est un tableau de words)
    movea.l  4+4+4+2(%a4),%a3
    adda.w   %d3,%a3 | &tabanim[step]

    move.l   %a1,%d3 | save destination adress
    move.l   (%a4),%a1 | big_vscreen

    movem.l  %d0-%d1,-(%a7)

    bsr      RefreshAnimatedBuffer16W

    movem.l  (%a7)+,%d0-%d1

    move.l   %d3,%a1
    move.l   %d4,%a2
    lea.l    -10(%a4),%a4

DrawBuffer_DrawAnimatedPlane16W:
    move.l   4+2+4(%a4),%a0 | big_vscreen

    move.w   %d0,4+2+4+4+4(%a4) | save new x
    move.w   %d1,4+2+4+4+4+2(%a4) | and new y
    moveq.l  #31,%d2
    and.w    %d2,%d0 | x
    and.w    %d2,%d1 | y

    | a1 already contains destination's adress
    jsr      (%a2) | call a DrawBuffer_MODE function

    movem.l  (%a7)+,%d3-%d4/%a2-%a4
    rts
