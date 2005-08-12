	.text
	xdef DrawTiles8W89

| Affiche directement les tiles dans un buffer de 3840 octets
| Ne remplit que la partie visible par une TI-89 (160x96 pixels)

| Input :
| a0.l : adresse du tableau de tiles, positionn�e vers le premier tile � afficher
| a1.l : adresse du buffer de 3840 octets
| a2.l : adresse du tableau de sprites 8x8
| d2.w : largeur de la map

| D�rtuit : d0-d2/a0-a1

DrawTiles8W89:
    movem.l  %d3/%a2-%a3,-(%a7)

    add.w    %d2,%d2		| (parce qu'on a un tableau de words)

    moveq.l  #20-1,%d3		| 20 columns (20*8=160)
PutPlane_DrawTiles8W89:
    moveq.l  #12-1,%d1		| 12 rows (12*8=96)
PutCol_DrawTiles8W89:
    move.w   (%a0),%d0		| d0 = num_sprt
    lsl.w    #3,%d0		| d0 *= 8
    lea.l    0(%a2,%d0.w),%a3	| a3 = sprt

PutTile_DrawTiles8W89:
    move.b   (%a3)+,(%a1)
    move.b   (%a3)+,30*1(%a1)
    move.b   (%a3)+,30*2(%a1)
    move.b   (%a3)+,30*3(%a1)
    move.b   (%a3)+,30*4(%a1)
    move.b   (%a3)+,30*5(%a1)
    move.b   (%a3)+,30*6(%a1)
    move.b   (%a3)+,30*7(%a1)

    lea.l    30*8(%a1),%a1

    adda.w   %d2,%a0
    dbf      %d1,PutCol_DrawTiles8W89

    lea.l    -2880+1(%a1),%a1	| next column
    move.w   %d2,%d1
    add.w    %d1,%d1
    add.w    %d2,%d1
    add.w    %d1,%d1
    add.w    %d1,%d1
    subq.w   #2,%d1		| d1 = larg_map*12 - 2
    suba.l   %d1,%a0

    dbf      %d3,PutPlane_DrawTiles8W89

    movem.l  (%a7)+,%d3/%a2-%a3
    rts
