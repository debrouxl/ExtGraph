	.section .text
	xdef DrawBufferWithShifts89_OR

| Affiche le buffer de 5440 octets sur un buffer de 3840 octets avec des tables de décalages

| Input :
| a0.l : adresse du buffer source
| a1.l : adresse du buffer destination
| a2.l : adresse de la table de décalage horizontal
| a3.l : adresse de la table de décalage vertical
| d0.w : décalage sur x (0 <= d0 < 16)
| d1.w : décalage sur y (0 <= d1 < 16)

| Détruit : d0-d2/a0-a1

DrawBufferWithShifts89_OR:
    movem.l  %d3-%d7/%a2-%a3,-(%a7)

    add.w    %d1,%d1
    move.w   %d1,%d2
    lsl.w    #4,%d1
    add.w    %d2,%d1	| d1 = y*34
    adda.w   %d1,%a0	| scrolling vertical

    move.w   %d0,%d7

    moveq.l  #99,%d6
LineStart_DrawBufferWithShifts89_OR:

    moveq.l  #16,%d1
    move.w   %d7,%d0	| Décalage initial
    add.b    (%a2),%d0	| Décalage horizontal
    cmp.w    %d1,%d0	| d0 < 16 ?
    blt.s    OK_DrawBufferWithShifts89_OR
    addq.l   #2,%a0
    sub.w    %d1,%d0
OK_DrawBufferWithShifts89_OR:

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
    or.l     %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+

    and.w    %d1,%d3
    move.l   (%a0)+,%d4
    rol.l    %d0,%d4
    move.w   %d4,%d5
    and.w    %d2,%d5
    or.w     %d5,%d3
    or.l     %d3,(%a1)+

    and.w    %d1,%d4
    move.l   (%a0)+,%d3
    rol.l    %d0,%d3
    move.w   %d3,%d5
    and.w    %d2,%d5
    or.w     %d5,%d4
    or.l     %d4,(%a1)+

    and.w    %d1,%d3
    move.w   (%a0)+,%d4
    rol.w    %d0,%d4
    and.w    %d2,%d4
    or.w     %d4,%d3
    or.l     %d3,(%a1)+

    moveq.l  #10,%d1

    move.w   %d7,%d0	| Décalage initial
    add.b    (%a2)+,%d0	| Décalage horizontal
    cmpi.w   #16,%d0	| d0 < 16 ?
    bge.s    OK2_DrawBufferWithShifts89_OR
    addq.w   #2,%d1
OK2_DrawBufferWithShifts89_OR:

    add.w    (%a3)+,%d1	| décalage vertical

    adda.w   %d1,%a0
    lea.l    10(%a1),%a1

    dbf      %d6,LineStart_DrawBufferWithShifts89_OR

    movem.l  (%a7)+,%d3-%d7/%a2-%a3
    rts
