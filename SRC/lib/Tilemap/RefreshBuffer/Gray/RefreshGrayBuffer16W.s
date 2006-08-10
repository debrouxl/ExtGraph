	.text
	xdef RefreshGrayBuffer16W

| Réaffiche le plan de 272x160 pixels

| Input :
| a0.l : adresse du tableau de tiles, positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de 5440*2 octets
| a2.l : adresse du tableau de sprites
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

RefreshGrayBuffer16W:
    movem.l  %d3/%a2-%a3,-(%a7)

    add.w    %d2,%d2		| (parce qu'on a un tableau de words)

    moveq.l  #16,%d3
PutPlane_RefreshGrayBuffer16W:
    moveq.l  #9,%d1
PutCol_RefreshGrayBuffer16W:
    move.w   (%a0),%d0		| d0 = num_sprt
    lsl.w    #6,%d0		| d0 *= 16*2*2
    lea.l    0(%a2,%d0.w),%a3	| a3 = sprt

    moveq.l  #3,%d0
PutTile_RefreshGrayBuffer16W:
    move.w   (%a3)+,(%a1)
    move.w   (%a3)+,5440(%a1)

    move.w   (%a3)+,34(%a1)
    move.w   (%a3)+,34+5440(%a1)

    move.w   (%a3)+,34*2(%a1)
    move.w   (%a3)+,34*2+5440(%a1)

    move.w   (%a3)+,34*3(%a1)
    move.w   (%a3)+,34*3+5440(%a1)

    lea.l    34*4(%a1),%a1

    dbf      %d0,PutTile_RefreshGrayBuffer16W

    adda.w   %d2,%a0
    dbf      %d1,PutCol_RefreshGrayBuffer16W

    lea.l    -5440+2(%a1),%a1	| next column
    move.w   %d2,%d1
    lsl.w    #3,%d1
    add.w    %d2,%d1
    add.w    %d2,%d1
    subq.w   #2,%d1		| d1 = larg_map*10-2
    suba.l   %d1,%a0

    dbf      %d3,PutPlane_RefreshGrayBuffer16W

    movem.l  (%a7)+,%d3/%a2-%a3
    rts
