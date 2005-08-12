	.section .text
	xdef DrawGrayBuffer89_MASK

| Affiche le buffer de 5440 octets sur un buffer de 3840 octets en faisant un AND

| Input :
| a0.l : adresse du buffer source
| a1.l : adresse du buffer destination
| d0.w : décalage sur x (0 <= d0 < 32)
| d1.w : décalage sur y (0 <= d1 < 32)

| Détruit : d0-d2/a0-a1

DrawGrayBuffer89_MASK:
    movem.l  %d3-%d6/%a2,-(%a7)

    add.w    %d1,%d1
    move.w   %d1,%d2
    lsl.w    #4,%d1
    add.w    %d2,%d1	| d1 = y*34
    adda.w   %d1,%a0	| scrolling vertical

    moveq.l  #16,%d1
    cmp.w    %d1,%d0	| d0 < 16 ?
    blt.s    OK_DrawGrayBuffer89_MASK
    addq.l   #2,%a0
    sub.w    %d1,%d0
OK_DrawGrayBuffer89_MASK:

    lea.l    3840(%a1),%a2

    moveq.l  #-1,%d1
    lsl.w    %d0,%d1	| d1 = mask1
    move.w   %d1,%d2
    not.w    %d2	| d2 = mask2

    moveq.l  #99,%d6
LineStart_DrawGrayBuffer89_MASK:
    move.l   (%a0)+,%d3
    lsl.l    %d0,%d3

    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    and.l    %d3,(%a1)+
    and.l    %d3,(%a2)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    and.l    %d4,(%a1)+
    and.l    %d4,(%a2)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    and.l    %d3,(%a1)+
    and.l    %d3,(%a2)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    and.l    %d4,(%a1)+
    and.l    %d4,(%a2)+

    and.w    %d1,%d3
    move.w   (%a0)+,%d4
    rol.w    %d0,%d4
    and.w    %d2,%d4
    or.w     %d4,%d3
    and.l    %d3,(%a1)+
    and.l    %d3,(%a2)+

    lea.l    10+2(%a0),%a0
    lea.l    10(%a1),%a1
    lea.l    10(%a2),%a2

    dbf      %d6,LineStart_DrawGrayBuffer89_MASK

    movem.l  (%a7)+,%d3-%d6/%a2
    rts
