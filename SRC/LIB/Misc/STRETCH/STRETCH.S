| Assembly Source File
| Created 29/12/2004; 15:26:32

| Routine courtesy of GoldenCrystal.
| Modified by Lionel Debroux:
| * optimized for size (it's already big enough, there's no need to unroll
|   the loops !), replace copy&paste with macros.
| * changed calling convention (the macros made it easier).

	.global screen_stretch

.macro STRETCH_LINE
	| Procédure pour écrire trois octets de destination en partant de deux octets source
	| Sera répétée 10 fois pour écrire une ligne
	move.w (%a1)+,%d2 | Charge le premier mot dans d2
	move.w %d2,%d3 | Copie vers d3
	andi.w #0x3F,%d3 | Conserve uniquement les 6 derniers bits de d3
	move.b (0,%d3.w,%a4),(%a0) | Ecrit le troisième octet
	lsr.w #5,%d2 | Décale d2 de 5 bits vers la droite
	move.w %d2,%d3 | Copie d2 vers d3
	andi.w #0x3F,%d3
	move.b (0,%d3.w,%a3),-(%a0) | Ecrit le deuxième octet
	lsr.w #6,%d2 | Décale d2 de 6 bits vers la droite
	move.b (0,%d2.w,%a2),-(%a0) | Ecrit le premier octet
	addq.w #5,%a0 | Incrémente le pointeur de 5 pour le bloc suivant
.endm

.macro NEXT_LINE
	subq.w #2,%a0 | Décrémente le pointeur destination de 2, passage à la ligne suivante
	lea (10, %a1),%a1 | Incrémente le pointeur source de 10, passage à la ligne suivante
.endm

.macro COPY_LINE
	| On copie la ligne précedente ici
	movem.l (-30,%a0),%d2-%d7/%a5
	movem.l %d2-%d7/%a5,(%a0)
	move.w (-2,%a0),%d2
	lea (28,%a0),%a0
	move.w %d2,(%a0)+
.endm


.macro MAKE_LINE
	addq.w #2,%a0

	moveq #10-1,%d4
0:
	STRETCH_LINE
	
	dbf %d4,0b
	
	NEXT_LINE
.endm

screen_stretch:
	movem.l %d3-%d7/%a2-%a5,-(%a7)
	lea 7f(%pc),%a2
	lea 8f(%pc),%a3
	lea 9f(%pc),%a4
	| On va écrire des blocs de 32 lignes (3 blocs de 9 lignes et un bloc de 5), il faudra répéter l'opération 4 fois
	| Le redimensionnement 100 -> 128 est moins répétitif que le redimensionnement 160 -> 240
	| Il se décompose de façon primaire en 4 répétitions identiques
	| Dans chacune de ces répétitions il y a 2 types de sous-répétitions
	| Une ligne double suivie de deux lignes simples
	| Une ligne double suivie de trois lignes simples
	| On enchaîne 3 répétitions 211-2111 puis une répétition 2111
	moveq #4-1,%d0
2:
	moveq #3-1,%d1
1:
	MAKE_LINE
	COPY_LINE

	MAKE_LINE

	MAKE_LINE
	

	MAKE_LINE
	COPY_LINE
	
	MAKE_LINE

	MAKE_LINE

	MAKE_LINE

	dbf %d1,1b


	MAKE_LINE
	COPY_LINE
	
	MAKE_LINE
	
	MAKE_LINE

	MAKE_LINE

	dbf %d0,2b
	
	movem.l (%a7)+,%d3-%d7/%a2-%a5
	rts

7:
.byte 0x00, 0x03, 0x04, 0x07, 0x18, 0x1B, 0x1C, 0x1F, 0x20, 0x23, 0x24, 0x27, 0x38, 0x3B, 0x3C, 0x3F, 0xC0, 0xC3, 0xC4, 0xC7, 0xD8, 0xDB, 0xDC, 0xDF, 0xE0, 0xE3, 0xE4, 0xE7, 0xF8, 0xFB, 0xFC, 0xFF

8:
.byte 0x00, 0x01, 0x02, 0x03, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x1C, 0x1D, 0x1E, 0x1F, 0x60, 0x61, 0x62, 0x63, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x9C, 0x9D, 0x9E, 0x9F, 0xE0, 0xE1, 0xE2, 0xE3, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xFC, 0xFD, 0xFE, 0xFF

9:
.byte 0x00, 0x01, 0x06, 0x07, 0x08, 0x09, 0x0E, 0x0F, 0x30, 0x31, 0x36, 0x37, 0x38, 0x39, 0x3E, 0x3F, 0x40, 0x41, 0x46, 0x47, 0x48, 0x49, 0x4E, 0x4F, 0x70, 0x71, 0x76, 0x77, 0x78, 0x79, 0x7E, 0x7F, 0x80, 0x81, 0x86, 0x87, 0x88, 0x89, 0x8E, 0x8F, 0xB0, 0xB1, 0xB6, 0xB7, 0xB8, 0xB9, 0xBE, 0xBF, 0xC0, 0xC1, 0xC6, 0xC7, 0xC8, 0xC9, 0xCE, 0xCF, 0xF0, 0xF1, 0xF6, 0xF7, 0xF8, 0xF9, 0xFE, 0xFF
