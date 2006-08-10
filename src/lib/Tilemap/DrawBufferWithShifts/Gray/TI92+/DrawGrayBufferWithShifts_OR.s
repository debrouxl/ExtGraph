	.text
	xdef DrawGrayBufferWithShifts_OR

| Affiche le buffer de 5440 octets sur un buffer de 3840 octets avec des tables de décalages

| Input :
| a0.l : adresse du buffer source
| a1.l : adresse du buffer destination
| a2.l : adresse de la table de décalage horizontal
| a3.l : adresse de la table de décalage vertical
| d0.w : décalage sur x (0 <= d0 < 16)
| d1.w : décalage sur y (0 <= d1 < 16)

| Détruit : d0-d2/a0-a1

DrawGrayBufferWithShifts_OR:
    movem.l  %d3-%d7/%a2-%a6,-(%a7)

    add.w    %d1,%d1
    move.w   %d1,%d2
    lsl.w    #4,%d1
    add.w    %d2,%d1	| d1 = y*34
    adda.w   %d1,%a0	| scrolling vertical

    lea.l    5440(%a0),%a4
    lea.l    3840(%a1),%a5

    movea.w  %d0,%a6 | sauve le shift initial

    moveq.l  #127,%d7

LineStart_DrawGrayBufferWithShifts_OR:

    moveq.l  #16,%d1
    move.w   %a6,%d0	| décalage initial
    add.b    (%a2),%d0	| Décalage horizontal
    cmp.w    %d1,%d0	| d0 < 16 ?
    blt.s    OK_DrawGrayBufferWithShifts_OR
    addq.l   #2,%a0
    addq.l   #2,%a4
    sub.w    %d1,%d0
OK_DrawGrayBufferWithShifts_OR:

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
    or.l     %d3,(%a1)+	| 1

    move.l   (%a4)+,%d5
    lsl.l    %d0,%d5

    move.l   (%a4)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d3
    and.w    %d2,%d3
    or.w     %d3,%d5
    or.l     %d5,(%a5)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+	| 2

    and.w    %d1,%d6
    move.l   (%a4)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d4
    and.w    %d2,%d4
    or.w     %d4,%d6
    or.l     %d6,(%a5)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d6
    and.w    %d2,%d6
    or.w     %d6,%d3
    or.l     %d3,(%a1)+	| 3

    and.w    %d1,%d5
    move.l   (%a4)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d3
    and.w    %d2,%d3
    or.w     %d3,%d5
    or.l     %d5,(%a5)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+	| 4

    and.w    %d1,%d6
    move.l   (%a4)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d4
    and.w    %d2,%d4
    or.w     %d4,%d6
    or.l     %d6,(%a5)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d6
    and.w    %d2,%d6
    or.w     %d6,%d3
    or.l     %d3,(%a1)+	| 5

    and.w    %d1,%d5
    move.l   (%a4)+,%d6
    rol.l    %d0,%d6
    move.w   %d6,%d3
    and.w    %d2,%d3
    or.w     %d3,%d5
    or.l     %d5,(%a5)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+	| 6

    and.w    %d1,%d6
    move.l   (%a4)+,%d5
    rol.l    %d0,%d5
    move.w   %d5,%d4
    and.w    %d2,%d4
    or.w     %d4,%d6
    or.l     %d6,(%a5)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    and.w    %d2,%d4
    or.w     %d4,%d3
    or.l     %d3,(%a1)+	| 7

    and.w    %d1,%d5
    move.l   (%a4)+,%d6
    rol.l    %d0,%d6
    and.w    %d2,%d6
    or.w     %d6,%d5
    or.l     %d5,(%a5)+

    swap.w   %d4
    swap.w   %d6

    or.w     %d4,(%a1)+
    or.w     %d6,(%a5)+

    move.w   %a6,%d0	| Décalage initial
    add.b    (%a2)+,%d0	| Décalage horizontal
    cmpi.w   #16,%d0	| d0 < 16 ?
    bge.s    OK2_DrawGrayBufferWithShifts_OR
    addq.l   #2,%a0
    addq.l   #2,%a4
OK2_DrawGrayBufferWithShifts_OR:

    adda.w   (%a3),%a0 | Décalage vertical
    adda.w   (%a3)+,%a4

    dbf      %d7,LineStart_DrawGrayBufferWithShifts_OR

    movem.l  (%a7)+,%d3-%d7/%a2-%a6
    rts
