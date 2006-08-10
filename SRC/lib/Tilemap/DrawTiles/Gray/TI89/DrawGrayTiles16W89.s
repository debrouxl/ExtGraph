	.text
	xdef DrawGrayTiles16W89

| Affiche directement les tiles dans un buffer de 3840*2 octets
| Ne remplit que la partie visible par une TI-89 (160x96 pixels)

| Input :
| a0.l : adresse du tableau de tiles, positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de 3840*2 octets
| a2.l : adresse du tableau de sprites
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

DrawGrayTiles16W89:
    movem.l  %d3/%a2-%a3,-(%a7)

    add.w    %d2,%d2		| (parce qu'on a un tableau de words)

    moveq.l  #10-1,%d3
PutPlane_DrawGrayTiles16W89:
    moveq.l  #6-1,%d1
PutCol_DrawGrayTiles16W89:
    move.w   (%a0),%d0		| d0 = num_sprt
    lsl.w    #6,%d0		| d0 *= 16*2*2
    lea.l    0(%a2,%d0.w),%a3	| a3 = sprt

    moveq.l  #3,%d0
PutTile_DrawGrayTiles16W89:
    move.w   (%a3)+,(%a1)
    move.w   (%a3)+,3840(%a1)

    move.w   (%a3)+,30(%a1)
    move.w   (%a3)+,30+3840(%a1)

    move.w   (%a3)+,30*2(%a1)
    move.w   (%a3)+,30*2+3840(%a1)

    move.w   (%a3)+,30*3(%a1)
    move.w   (%a3)+,30*3+3840(%a1)

    lea.l    30*4(%a1),%a1

    dbf      %d0,PutTile_DrawGrayTiles16W89

    adda.w   %d2,%a0
    dbf      %d1,PutCol_DrawGrayTiles16W89

    lea.l    -2880+2(%a1),%a1	| next column
    move.w   %d2,%d1
    add.w    %d1,%d1
    add.w    %d2,%d1
    add.w    %d1,%d1
    subq.w   #2,%d1		| d1 = larg_map*6-2
    suba.l   %d1,%a0

    dbf      %d3,PutPlane_DrawGrayTiles16W89

    movem.l  (%a7)+,%d3/%a2-%a3
    rts
