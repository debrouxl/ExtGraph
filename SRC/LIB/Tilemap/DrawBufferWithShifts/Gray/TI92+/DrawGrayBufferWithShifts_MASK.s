	.text
	xdef DrawGrayBufferWithShifts_MASK

| Affiche le buffer de 5440 octets sur un buffer de 3840 octets avec des tables de décalages

| Input :
| a0.l : adresse du buffer source
| a1.l : adresse du buffer destination
| a2.l : adresse de la table de décalage horizontal
| a3.l : adresse de la table de décalage vertical
| d0.w : décalage sur x (0 <= d0 < 16)
| d1.w : décalage sur y (0 <= d1 < 16)

| Détruit : d0-d2/a0-a1

DrawGrayBufferWithShifts_MASK:
    movem.l  %d3-%d7/%a2-%a4,-(%a7)

    add.w    %d1,%d1
    move.w   %d1,%d2
    lsl.w    #4,%d1
    add.w    %d2,%d1	| d1 = y*34
    adda.w   %d1,%a0	| scrolling vertical

    move.w   %d0,%d7	| sauvegarde le décalage initial

    lea.l    3840(%a1),%a4

    moveq.l  #127,%d6
LineStart_DrawGrayBufferWithShifts_MASK:

    moveq.l  #16,%d1
    move.w   %d7,%d0	| décalage initial
    add.b    (%a2),%d0	| Décalage horizontal
    cmp.w    %d1,%d0	| d0 < 16 ?
    blt.s    OK_DrawGrayBufferWithShifts_MASK
    addq.l   #2,%a0
    sub.w    %d1,%d0
OK_DrawGrayBufferWithShifts_MASK:

    moveq.l  #-1,%d1
    lsl.w    %d0,%d1	| d1 = mask1
    move.w   %d1,%d2
    not.w    %d2	| d2 = mask2

    move.l   (%a0)+,%d3
    lsl.l    %d0,%d3

    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    and.l    %d3,(%a1)+
    and.l    %d3,(%a4)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    and.l    %d4,(%a1)+
    and.l    %d4,(%a4)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    and.l    %d3,(%a1)+
    and.l    %d3,(%a4)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    and.l    %d4,(%a1)+
    and.l    %d4,(%a4)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    and.l    %d3,(%a1)+
    and.l    %d3,(%a4)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    and.l    %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    and.l    %d3,(%a1)+
    and.l    %d3,(%a4)+

    swap.w   %d4	| 16 derniers pixels
    and.w    %d4,(%a1)+
    and.w    %d4,(%a4)+

    move.w   %d7,%d0	| Décalage initial
    add.b    (%a2)+,%d0	| Décalage horizontal
    cmpi.w   #16,%d0	| d0 < 16 ?
    bge.s    OK2_DrawGrayBufferWithShifts_MASK
    addq.l   #2,%a0
OK2_DrawGrayBufferWithShifts_MASK:

    adda.w   (%a3)+,%a0	| décalage vertical

    dbf      %d6,LineStart_DrawGrayBufferWithShifts_MASK

    movem.l  (%a7)+,%d3-%d7/%a2-%a4
    rts
