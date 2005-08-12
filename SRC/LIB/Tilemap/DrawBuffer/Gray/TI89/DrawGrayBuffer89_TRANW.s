	.text
	xdef DrawGrayBuffer89_TRANW

| Affiche le buffer de 5440 octets sur un buffer de 3840 octets, la couleur blanche est transparente

| Input :
| a0.l : adresse du buffer source
| a1.l : adresse du buffer destination
| d0.w : décalage sur x (0 <= d0 < 32)
| d1.w : décalage sur y (0 <= d1 < 32)

| Détruit : d0-d2/a0-a1

DrawGrayBuffer89_TRANW:
    movem.l  %d3-%d7/%a2-%a3,-(%a7)

    add.w    %d1,%d1
    move.w   %d1,%d2
    lsl.w    #4,%d1
    add.w    %d2,%d1	| d1 = y*34
    adda.w   %d1,%a0	| scrolling vertical

    moveq.l  #16,%d1
    cmp.w    %d1,%d0	| d0 < 16 ?
    blt.s    OK_DrawGrayBuffer89_TRANW
    addq.l   #2,%a0
    sub.w    %d1,%d0
OK_DrawGrayBuffer89_TRANW:

    lea.l    5440(%a0),%a2
    lea.l    3840(%a1),%a3

    moveq.l  #99,%d2
    swap.w   %d2

    moveq.l  #-1,%d1
    lsl.w    %d0,%d1	| d1 = mask1
    move.w   %d1,%d2
    not.w    %d2	| d2 = mask2
    swap.w   %d2

LineStart_DrawGrayBuffer89_TRANW:
    swap.w   %d2

    move.l   (%a0)+,%d3
    lsl.l    %d0,%d3

    move.l   (%a2)+,%d5
    lsl.l    %d0,%d5

    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d7
    and.w    %d2,%d7
    or.w     %d7,%d3

    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d7
    and.w    %d2,%d7
    or.w     %d7,%d5

    move.l   %d5,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 1
    or.l     %d3,%d7
    move.l   %d7,(%a1)+

    not.l    %d3
    and.l    (%a3),%d3
    or.l     %d5,%d3
    move.l   %d3,(%a3)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d7
    and.w    %d2,%d7
    or.w     %d7,%d4

    and.w    %d1,%d6
    move.l   (%a2)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d7
    and.w    %d2,%d7
    or.w     %d7,%d6

    move.l   %d6,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 2
    or.l     %d4,%d7
    move.l   %d7,(%a1)+

    not.l    %d4
    and.l    (%a3),%d4
    or.l     %d6,%d4
    move.l   %d4,(%a3)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d7
    and.w    %d2,%d7
    or.w     %d7,%d3

    and.w    %d1,%d5
    move.l   (%a2)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d7
    and.w    %d2,%d7
    or.w     %d7,%d5

    move.l   %d5,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 3
    or.l     %d3,%d7
    move.l   %d7,(%a1)+

    not.l    %d3
    and.l    (%a3),%d3
    or.l     %d5,%d3
    move.l   %d3,(%a3)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d7
    and.w    %d2,%d7
    or.w     %d7,%d4

    and.w    %d1,%d6
    move.l   (%a2)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d7
    and.w    %d2,%d7
    or.w     %d7,%d6

    move.l   %d6,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 4
    or.l     %d4,%d7
    move.l   %d7,(%a1)+

    not.l    %d4
    and.l    (%a3),%d4
    or.l     %d6,%d4
    move.l   %d4,(%a3)+

    and.w    %d1,%d3
    move.w   (%a0)+,%d4
    rol.w    %d0,%d4
    and.w    %d2,%d4
    or.w     %d4,%d3

    and.w    %d1,%d5
    move.w   (%a2)+,%d6
    rol.w    %d0,%d6
    and.w    %d2,%d6
    or.w     %d6,%d5

    move.l   %d5,%d7
    not.l    %d7
    and.l    (%a1),%d7	| 5
    or.l     %d3,%d7
    move.l   %d7,(%a1)+

    not.l    %d3
    and.l    (%a3),%d3
    or.l     %d5,%d3
    move.l   %d3,(%a3)+

    lea.l    10+2(%a0),%a0
    lea.l    10+2(%a2),%a2
    lea.l    10(%a1),%a1
    lea.l    10(%a3),%a3

    swap.w   %d2
    dbf      %d2,LineStart_DrawGrayBuffer89_TRANW

    movem.l  (%a7)+,%d3-%d7/%a2-%a3
    rts
