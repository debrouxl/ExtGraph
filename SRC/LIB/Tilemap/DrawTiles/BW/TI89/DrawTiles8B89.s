	.text
	xdef DrawTiles8B89

| Affiche directement les tiles dans un buffer de 3840 octets
| Ne remplit que la partie visible par une TI-89 (160x96 pixels)

| Input :
| a0.l : adresse du tableau de tiles (bytes), positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de 3840 octets
| a2.l : adresse du tableau de sprites 8x8
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

DrawTiles8B89:
    movem.l  %d3/%a2-%a3,-(%a7)

    moveq.l  #20-1,%d3
PutPlane_DrawTiles8B89:
    moveq.l  #12-1,%d1
PutCol_DrawTiles8B89:
    clr.w    %d0
    move.b   (%a0),%d0		| d0 = num_sprt
    lsl.w    #3,%d0		| d0 *= 8
    lea.l    0(%a2,%d0.w),%a3	| a3 = sprt

PutTile_DrawTiles8B89:
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
    dbf      %d1,PutCol_DrawTiles8B89

    lea.l    -2880+1(%a1),%a1	| next column
    move.w   %d2,%d1
    add.w    %d1,%d1
    add.w    %d2,%d1
    add.w    %d1,%d1
    add.w    %d1,%d1
    subq.w   #1,%d1		| d1 = larg_map*12 - 1
    suba.l   %d1,%a0

    dbf      %d3,PutPlane_DrawTiles8B89

    movem.l  (%a7)+,%d3/%a2-%a3
    rts
