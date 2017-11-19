| C prototype: void GrayClipISpriteX16_XOR_R(short x asm("%d0"), short y asm("%d1"), unsigned short height asm("%d3"), const unsigned short *sprt, unsigned short wordwidth asm("%d2"), void *dest0 asm("%a0"), void *dest1 asm("%a1")) __attribute__((__stkparm__));
|
| Based on GrayClipISpriteX16_OR_R.
|
| The sprite format is a sequence of WORDS (not lines): light plane, dark plane (different from that of MASK).

.include "common.s"

.text
.globl GrayClipISpriteX16_XOR_R
.even

GrayClipISpriteX16_XOR_R:
    movem.l  %d3-%d7/%a2,-(%sp)
    move.l   4+24(%sp),%a2

    move.w   %d2,%d5
    add.w    %d5,%d5     | largeur*2 (en octets) du sprite

| Test clipping sur la bordure haute
    move.w   %d1,%d4
    bge.s    9f     | si y >= 0, le sprite n'a pas besoin d'être clippé sur la bordure haute
    add.w    %d1,%d3     | y + hauteur : nouvelle hauteur du sprite
    ble.w    0f     | si y + hauteur <= 0, le sprite n'est pas visible

    move.w   %d5,%d6     | pour ne pas perdre le contenu de %d5, réutilisé plus tard
    add.w    %d6,%d6     | *2 pour les niveaux de gris
    muls.w   %d6,%d1     | %d1 = -y * largeur (en octets)
    suba.w   %d1,%a2     | mise à jour du pointeur sur le sprite
    moveq.l  #0,%d1     | offset du à y = 0
    bra.s    10f

9:
| Test clipping sur la bordure basse
    add.w    %d3,%d4     | %d4 = y + hauteur
    subi.w   #PLANE_PIXEL_HEIGHT,%d4     | %d4 = y + hauteur - PLANE_PIXEL_HEIGHT
    bls.s    6f     | si y + hauteur <= PLANE_PIXEL_HEIGHT, le sprite n'a pas besoin d'être clippé
  | Le sprite doit être clippé sur la bordure basse de l'écran
    neg.w    %d4     | %d4 = PLANE_PIXEL_HEIGHT - hauteur - y
    add.w    %d4,%d3     | %d3 = PLANE_PIXEL_HEIGHT - y = nouvelle hauteur du sprite
    ble.w    0f     | si y >= PLANE_PIXEL_HEIGHT, le sprite n'est pas visible (FIXME : bls plutôt que ble ?)

6:
    COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d4

10:
    subq.w   #1,%d3     | hauteur - 1 (compteur de height_loop)

| Test clipping gauche
    moveq.l  #PLANE_BYTE_WIDTH,%d7
    sub.w    %d5,%d7     | %d7 = PLANE_BYTE_WIDTH - largeur (en octets) = incrément de la destination après avoir affiché une ligne
    |move.w   %d4,%a3 ???
    lsl.w    #3,%d5     | %d5 = largeur * 2 * 8 (en pixels)
    move.w   %d0,%d4     | %d4 = x
    blt.w    7f     | si x < 0, le sprite doit être clippé sur la bordure gauche

| Calcul de l'adresse de destination
    move.w   %d0,%d4
    lsr.w    #4,%d4
    add.w    %d4,%d1
    add.w    %d1,%d1     | %d1 = y*PLANE_BYTE_WIDTH * y + (x / 16) * 2

    adda.w   %d1,%a0     | a0 = Screen1 + Offset
    adda.w   %d1,%a1

| Test clipping droit
    add.w    %d0,%d5     | x + largeur en pixels
    sub.w    #PLANE_BYTE_WIDTH*8,%d5
    bhi.w    8f     | si x + largeur > PLANE_BYTE_WIDTH*8, il faut clipper à droite

    subq.w   #1,%d2     | largeur - 1 (compteur de width_loop)

    andi.w   #15,%d0
    beq.s    11f

    subq.w   #7,%d0
    blt.w    3f

    moveq.l  #16-7,%d1
    sub.w    %d0,%d1

| Boucle d'affichage si le sprite n'est pas clippé
1:
    move.w   %d2,%d6

2:
    moveq.l  #0,%d0
    move.w   (%a2)+,%d0     | sprite1
    lsl.l    %d1,%d0
    eor.l    %d0,(%a0)

    moveq.l  #0,%d0
    move.w   (%a2)+,%d0     | sprite2
    lsl.l    %d1,%d0
    eor.l    %d0,(%a1)

    addq.l   #2,%a0
    addq.l   #2,%a1
    dbf.w    %d6,2b

    adda.w   %d7,%a0
    adda.w   %d7,%a1

    dbf.w    %d3,1b

0:
    movem.l  (%sp)+,%d3-%d7/%a2
    rts

| Boucle d'affichage sans shifting
11:
1:
    move.w   %d2,%d6

2:
    move.w   (%a2)+,%d0     | sprite1
    eor.w    %d0,(%a0)+

    move.w   (%a2)+,%d0     | sprite2
    eor.w    %d0,(%a1)+

    dbf.w    %d6,2b

    add.w    %d7,%a0				| Next row of screen 1
    add.w    %d7,%a1				| Next row of screen 2

    dbf.w    %d3,1b
    movem.l  (%sp)+,%d3-%d7/%a2
    rts

| Boucle d'affichage avec shifting à droite
3:
    addq.w   #7,%d0     | Fix the dec of the cmp
1:
    move.w   %d2,%d6

2:
    moveq.l  #0,%d1
    move.w   (%a2)+,%d1     | sprite1
    swap.w   %d1
    lsr.l    %d0,%d1
    eor.l    %d1,(%a0)

    moveq.l  #0,%d1
    move.w   (%a2)+,%d1     | sprite2
    swap.w   %d1
    lsr.l    %d0,%d1
    eor.l    %d1,(%a1)

    addq.l   #2,%a0
    addq.l   #2,%a1
    dbf.w    %d6,2b

    adda.w   %d7,%a0		| Next row of screen 1
    adda.w   %d7,%a1		| Next row of screen 2
    dbf.w    %d3,1b

0:
    movem.l  (%sp)+,%d3-%d7/%a2
    rts

| Clipping sur la bordure gauche de l'écran
7:
    add.w    %d4,%d5 | x + largeur
    ble.s    0b     | si x + largeur <= 0, le sprite n'est pas visible

    neg.w    %d4
    lsr.w    #4,%d4     | %d4 = -x / 16
    sub.w    %d4,%d2     | compteur de width_loop
    subq.w   #2,%d2     | -1 (pour le premier mot, clippé) + -1 (pour le dbf) = -2

    add.w    %d4,%d4     | *2 pour avoir des octets
    add.w    %d4,%d7     | incrément de la destination (y*PLANE_BYTE_WIDTH - largeur + %d4)
    addq.w   #2,%d7

    add.w    %d1,%d1     | %d1 = y*PLANE_BYTE_WIDTH * y
    adda.w   %d1,%a0     | a0 = dark_screen
    adda.w   %d1,%a1

    neg.w    %d0
    andi.w   #15,%d0

    add.w    %d4,%d4     | *2 pour les niveaux de gris
                         | offset à ajouter à l'adresse du sprite à chaque ligne

1:
    adda.w   %d4,%a2     | on avance dans la source

    move.w   (%a2)+,%d1     | sprite1
    lsl.w    %d0,%d1
    eor.w    %d1,(%a0)

    move.w   (%a2)+,%d1     | sprite2
    lsl.w    %d0,%d1
    eor.w    %d1,(%a1)

    move.w   %d2,%d6
    bmi.s    4f

2:
    moveq.l  #0,%d1
    move.w   (%a2)+,%d1     | sprite1
    lsl.l    %d0,%d1
    eor.l    %d1,(%a0)

    moveq.l  #0,%d1
    move.w   (%a2)+,%d1     | sprite2
    lsl.l    %d0,%d1
    eor.l    %d1,(%a1)

    addq.l   #2,%a0
    addq.l   #2,%a1
    dbf      %d6,2b
4:

    adda.w   %d7,%a0
    adda.w   %d7,%a1

    dbf      %d3,1b

0:
    movem.l  (%sp)+,%d3-%d7/%a2
    rts

| Clipping sur la bordure droite de l'écran
8:
    cmp.w    #PLANE_PIXEL_WIDTH,%d0
    bcc.s    0b     | si x >= PLANE_PIXEL_WIDTH, le sprite est en-dehors de l'écran

    lsr.w    #4,%d5     | ((x + largeur) - PLANE_PIXEL_WIDTH) / 16 => nombre de words du sprite en trop
    sub.w    %d5,%d2
    subq.w   #2,%d2     | compteur width_loop

    add.w    %d5,%d5     | *2 pour avoir des octets
    add.w    %d5,%d7

    add.w    %d5,%d5     | *2 pour les niveaux de gris...

    andi.w   #15,%d0

1:
    move.w   %d2,%d6
    bmi.s    4f

2:
    moveq.l  #0,%d1
    move.w   (%a2)+,%d1     | sprite1
    swap.w   %d1
    lsr.l    %d0,%d1
    eor.l    %d1,(%a0)

    moveq.l  #0,%d1
    move.w   (%a2)+,%d1     | sprite2
    swap.w   %d1
    lsr.l    %d0,%d1
    eor.l    %d1,(%a1)

    addq.l   #2,%a0
    addq.l   #2,%a1
    dbf      %d6,2b

4:
    move.w   (%a2)+,%d1     | sprite1
    lsr.w    %d0,%d1
    eor.w    %d1,(%a0)+

    move.w   (%a2)+,%d1     | sprite2
    lsr.w    %d0,%d1
    eor.w    %d1,(%a1)+

    adda.w   %d5,%a2

    adda.w   %d7,%a0
    adda.w   %d7,%a1

    dbf      %d3,1b

    movem.l  (%sp)+,%d3-%d7/%a2
    rts
