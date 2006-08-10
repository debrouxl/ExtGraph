| C prototype: void SlowerSpriteX8_OR_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),short w asm("%d3"),unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));

.text
.globl SlowerSpriteX8_OR_R
.even

SlowerSpriteX8_OR_R:
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

0:	| beginning of line if odd adress
 	movea.l	%a0,%a2
	move.w	%d3,%d4

1:
	moveq.l	#0,%d0
	move.b	(%a1)+,%d0		| first odd byte
	dbf	%d4,2f			| goto if it is not the last one

	lsl.l	%d1,%d0
	or.l	%d0,(%a2)
	lea.l	30(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d5/%a2
	rts

2:
	lsl.w	#8,%d0
	move.b	(%a1)+,%d0		| second byte
	lsl.l	%d5,%d0
	or.l	%d0,(%a2)
	addq.l	#2,%a2
	dbf	%d4,1b

	lea.l	30(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d5/%a2
	rts
