	.text
	xdef DrawTiles16B

| Affiche directement les tiles dans un buffer de 3840 octets

| Input :
| a0.l : adresse du tableau de tiles (bytes), positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de destination 3840 octets
| a2.l : adresse du tableau de sprites
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

DrawTiles16B:
    movem.l  %d3/%a2-%a3,-(%a7)

    moveq.l  #15-1,%d3
PutPlane_DrawTiles16B:
    moveq.l  #8-1,%d1
PutCol_DrawTiles16B:
    clr.w    %d0
    move.b   (%a0),%d0		| d0 = num_sprt
    lsl.w    #5,%d0		| d0 *= 16*2
    lea.l    0(%a2,%d0.w),%a3	| a3 = sprt

    moveq.l  #4-1,%d0
PutTile_DrawTiles16B:
    move.w   (%a3)+,(%a1)
    move.w   (%a3)+,30*1(%a1)
    move.w   (%a3)+,30*2(%a1)
    move.w   (%a3)+,30*3(%a1)

    lea.l    30*4(%a1),%a1

    dbf      %d0,PutTile_DrawTiles16B

    adda.w   %d2,%a0
    dbf      %d1,PutCol_DrawTiles16B

    lea.l    -3840+2(%a1),%a1	| next column
    move.w   %d2,%d1
    lsl.w    #3,%d1
    subq.w   #1,%d1		| d1 = larg_map*8 - 1
    suba.l   %d1,%a0		| map -= larg_map*8 - 1

    dbf      %d3,PutPlane_DrawTiles16B

    movem.l  (%a7)+,%d3/%a2-%a3
    rts
