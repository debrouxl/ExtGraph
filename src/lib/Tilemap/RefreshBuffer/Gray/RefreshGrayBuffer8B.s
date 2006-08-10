	.text
	xdef RefreshGrayBuffer8B

| Réaffiche le plan de 272x160 pixels

| Input :
| a0.l : adresse du tableau de tiles (bytes), positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de 3840*2 octets
| a2.l : adresse du tableau de sprites 8x8
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

RefreshGrayBuffer8B:
    movem.l  %d3/%a2-%a3,-(%a7)

    moveq.l  #33,%d3
PutPlane_RefreshGrayBuffer8B:
    moveq.l  #19,%d1
PutCol_RefreshGrayBuffer8B:
    clr.w    %d0
    move.b   (%a0),%d0		| d0 = num_sprt
    lsl.w    #4,%d0		| d0 *= 8*2
    lea.l    0(%a2,%d0.w),%a3	| a3 = sprt

    moveq.l  #1,%d0
PutTile_RefreshGrayBuffer8B:
    move.b   (%a3)+,(%a1)
    move.b   (%a3)+,5440(%a1)

    move.b   (%a3)+,34(%a1)
    move.b   (%a3)+,34+5440(%a1)

    move.b   (%a3)+,34*2(%a1)
    move.b   (%a3)+,34*2+5440(%a1)

    move.b   (%a3)+,34*3(%a1)
    move.b   (%a3)+,34*3+5440(%a1)

    lea.l    34*4(%a1),%a1

    dbf      %d0,PutTile_RefreshGrayBuffer8B

    adda.w   %d2,%a0
    dbf      %d1,PutCol_RefreshGrayBuffer8B

    lea.l    -5440+1(%a1),%a1	| next column
    move.w   %d2,%d1
    lsl.w    #3,%d1
    add.w    %d2,%d1
    add.w    %d2,%d1
    add.w    %d1,%d1
    subq.w   #1,%d1		| d1 = larg_map*20 - 1
    suba.l   %d1,%a0

    dbf      %d3,PutPlane_RefreshGrayBuffer8B

    movem.l  (%a7)+,%d3/%a2-%a3
    rts
