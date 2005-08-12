	.text
	xdef RefreshGrayAnimatedBuffer16W

| Réaffiche le plan de 272x160 pixels

| Input :
| a0.l : adresse du tableau de tiles (words), positionnée vers le premier tile à afficher
| a1.l : adresse du buffer de 5440 octets
| a2.l : adresse du tableau de sprites
| a3.l : adresse du tableau d'animations (positionné sur l'étape courante)
| d2.w : largeur de la map

| Dértuit : d0-d2/a0-a1

RefreshGrayAnimatedBuffer16W:
    movem.l  %d3/%a4,-(%a7)

    add.w    %d2,%d2

    moveq.l  #16,%d3
PutPlane_RefreshGrayAnimatedBuffer16W:
    moveq.l  #9,%d1
PutCol_RefreshGrayAnimatedBuffer16W:
    move.w   (%a0),%d0		| d0 = num_anim
    add.w    %d0,%d0		| (anim est un tableau de words)
    move.w   0(%a3,%d0.w),%d0	| d0 = num_sprt
    lsl.w    #6,%d0		| d0 *= 16*2*2
    lea.l    0(%a2,%d0.w),%a4	| a4 = sprt

    moveq.l  #3,%d0
PutTile_RefreshGrayAnimatedBuffer16W:
    move.w   (%a4)+,(%a1)
    move.w   (%a4)+,5440(%a1)

    move.w   (%a4)+,34*1(%a1)
    move.w   (%a4)+,34*1+5440(%a1)

    move.w   (%a4)+,34*2(%a1)
    move.w   (%a4)+,34*2+5440(%a1)

    move.w   (%a4)+,34*3(%a1)
    move.w   (%a4)+,34*3+5440(%a1)

    lea.l    34*4(%a1),%a1

    dbf      %d0,PutTile_RefreshGrayAnimatedBuffer16W

    adda.w   %d2,%a0
    dbf      %d1,PutCol_RefreshGrayAnimatedBuffer16W

    lea.l    -5440+2(%a1),%a1	| next column
    move.w   %d2,%d1
    lsl.w    #3,%d1
    add.w    %d2,%d1
    add.w    %d2,%d1
    subq.w   #2,%d1		| d1 = larg_map*10 - 2
    suba.l   %d1,%a0		| map -= larg_map*10 - 2

    dbf      %d3,PutPlane_RefreshGrayAnimatedBuffer16W

    movem.l  (%a7)+,%d3/%a4
    rts
