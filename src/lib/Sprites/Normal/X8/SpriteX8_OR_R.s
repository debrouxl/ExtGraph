| C prototype: void SpriteX8_OR_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short h asm("%d2"), const unsigned char *sprt asm("%a1"), unsigned short bytewidth asm("%d3"), void *dest asm("%a0")) __attribute__((__regparm__));

.text
.globl SpriteX8_OR_R
.even

SpriteX8_OR_R:
	movem.l	%d3-%d5/%a2,-(%sp)

	move.w	%d1,%d4			| d4=d1
	lsl.w	#4,%d1			| d1*16
	sub.w	%d4,%d1			| d1=15y

	move.w	%d0,%d4	    		| d4=d0
	andi.w	#15,%d4			| d4=x%16

	lsr.w	#4,%d0			| d0/16
	add.w	%d1,%d0			| d0=15y+x/16
	add.w	%d0,%d0			| d0=30y+x/8 (even)

	adda.w	%d0,%a0			| align to the screen

 	moveq.l	#16,%d5
 	sub.w	%d4,%d5			| d5=16-d4

	move.w	%d5,%d1
	addq.w	#8,%d1

 	subq.w	#1,%d2			| h-1
	subq.w	#1,%d3			| w-1

	lea     r+3(%pc),%a2
| Test: width odd ?
	btst.b  #0,%d3
	beq.s   w
	moveq   #E0-(r+2),%d1
	bra.s   p
w:
	moveq   #O0-(r+2),%d1

p:
	move.b  %d1,(%a2)

	move.w	%d5,%d1
	addq.w	#8,%d1

| Test: width odd ?
	btst.b  #0,%d3
	beq.s   O0

E0:	| beginning of the line if the adress is even
 	movea.l	%a0,%a2
 	move.w	%d3,%d4			| width

E1:
	moveq.l	#0,%d0			| clear d0
 	move.w	(%a1)+,%d0		| get first byte
	dbf	%d4,E2			| goto the other semi-loop if that one's not the last byte on the line

	clr.b	%d0			| clear the remaining byte (not wanted)
	lsl.l	%d5,%d0
	or.l	%d0,(%a2)		| no need to increment (last byte)
	subq.l	#1,%a1			| re-align src
	lea	30(%a0),%a0
	dbf	%d2,O0			| next byte will at an odd adress

	movem.l	(%sp)+,%d3-%d5/%a2
 	rts

E2:	| if it's not the last byte we can draw two in a row
 	lsl.l	%d5,%d0			| shift
 	or.l	%d0,(%a2)		| print a word and increment
 	addq.l	#2,%a2
	dbf	%d4,E1			| next line if some remain

	lea.l	30(%a0),%a0
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts

O0:	| beginning of line if odd adress
 	movea.l	%a0,%a2
	move.w	%d3,%d4

O1:
	moveq.l	#0,%d0
	move.b	(%a1)+,%d0		| first odd byte
	dbf	%d4,O2			| goto if it is not the last one

	lsl.l	%d1,%d0
	or.l	%d0,(%a2)
	lea.l	30(%a0),%a0
r:
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts

O2:
	move.b  %d0,-(%sp)
	move.w  (%sp)+,%d0
|	lsl.w	#8,%d0
	move.b	(%a1)+,%d0		| second byte
	lsl.l	%d5,%d0
	or.l	%d0,(%a2)
	addq.l	#2,%a2
	dbf	%d4,O1

	lea.l	30(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts
