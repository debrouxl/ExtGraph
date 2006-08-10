	.text
	xdef RefreshBuffer8W

| Réaffiche le plan de 272x160 pixels

| Input :
| a0.l : adresse du tableau de tiles, positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de 5440 octets
| a2.l : adresse du tableau de sprites 8x8
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

RefreshBuffer8W:
    movem.l  %d3/%a2-%a3,-(%a7)

    add.w    %d2,%d2		| (parce qu'on a un tableau de words)

    moveq.l  #33,%d3		| 32 columns (32*8=256)
PutPlane_RefreshBuffer8W:
    moveq.l  #19,%d1		| 18 rows (18*8=144)
PutCol_RefreshBuffer8W:
    move.w   (%a0),%d0		| d0 = num_sprt
    lsl.w    #3,%d0		| d0 *= 8
    lea.l    0(%a2,%d0.w),%a3	| a3 = sprt

PutTile_RefreshBuffer8W:
    move.b   (%a3)+,(%a1)
    move.b   (%a3)+,34*1(%a1)
    move.b   (%a3)+,34*2(%a1)
    move.b   (%a3)+,34*3(%a1)
    move.b   (%a3)+,34*4(%a1)
    move.b   (%a3)+,34*5(%a1)
    move.b   (%a3)+,34*6(%a1)
    move.b   (%a3)+,34*7(%a1)

    lea.l    34*8(%a1),%a1

    adda.w   %d2,%a0
    dbf      %d1,PutCol_RefreshBuffer8W

    lea.l    -5440+1(%a1),%a1	| next column
    move.w   %d2,%d1
    lsl.w    #3,%d1
    add.w    %d2,%d1
    add.w    %d2,%d1
    add.w    %d1,%d1
    subq.w   #2,%d1		| d1 = larg_map*20 - 2
    suba.l   %d1,%a0

    dbf      %d3,PutPlane_RefreshBuffer8W

    movem.l  (%a7)+,%d3/%a2-%a3
    rts
