	.text
	xdef RefreshAnimatedBuffer8W

| Réaffiche le plan de 272x160 pixels

| Input :
| a0.l : adresse du tableau de tiles (words), positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de 5440 octets
| a2.l : adresse du tableau de sprites
| a3.l : adresse du tableau d'animations (positionné sur l'étape courante)
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

RefreshAnimatedBuffer8W:
    movem.l  %d3/%a4,-(%a7)

    add.w    %d2,%d2

    moveq.l  #33,%d3
PutPlane_RefreshAnimatedBuffer8W:
    moveq.l  #19,%d1
PutCol_RefreshAnimatedBuffer8W:
    move.w   (%a0),%d0		| d0 = num_anim
    add.w    %d0,%d0		| (anim est un tableau de words)
    move.w   0(%a3,%d0.w),%d0	| d0 = num_sprt
    lsl.w    #4,%d0		| d0 *= 8*2
    lea.l    0(%a2,%d0.w),%a4	| a4 = sprt

PutTile_RefreshAnimatedBuffer8W:
    move.b   (%a4)+,(%a1)
    move.b   (%a4)+,34*1(%a1)
    move.b   (%a4)+,34*2(%a1)
    move.b   (%a4)+,34*3(%a1)
    move.b   (%a4)+,34*4(%a1)
    move.b   (%a4)+,34*5(%a1)
    move.b   (%a4)+,34*6(%a1)
    move.b   (%a4)+,34*7(%a1)

    lea.l    34*8(%a1),%a1

    adda.w   %d2,%a0
    dbf      %d1,PutCol_RefreshAnimatedBuffer8W

    lea.l    -5440+1(%a1),%a1	| next column
    move.w   %d2,%d1
    lsl.w    #3,%d1
    add.w    %d2,%d1
    add.w    %d2,%d1
    add.w    %d1,%d1
    subq.w   #2,%d1		| d1 = larg_map*20 - 2
    suba.l   %d1,%a0		| map -= larg_map*20 - 2

    dbf      %d3,PutPlane_RefreshAnimatedBuffer8W

    movem.l  (%a7)+,%d3/%a4
    rts
