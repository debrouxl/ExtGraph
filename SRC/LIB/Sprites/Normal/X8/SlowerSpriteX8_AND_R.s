| C prototype: void SlowerSpriteX8_AND_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),unsigned char *sprt asm("%a1"),short w asm("%d3"),void *dest asm("%a0")) __attribute__((__regparm__));
| see SpriteX8_OR_R for comments

.text
.globl SlowerSpriteX8_AND_R
.even

SlowerSpriteX8_AND_R:
	movem.l	%d3-%d5/%a2,-(%sp)

	move.w	%d1,%d4
	lsl.w	#4,%d1
	sub.w	%d4,%d1

	move.w	%d0,%d4
	andi.w	#15,%d4

	lsr.w	#4,%d0
	add.w	%d1,%d0
	add.w	%d0,%d0

	adda.w	%d0,%a0

 	moveq.l	#16,%d5
 	sub.w	%d4,%d5

	move.w	%d5,%d1
	addq.w	#8,%d1

 	subq.w	#1,%d2
	subq.w	#1,%d3

0:
 	movea.l	%a0,%a2
	move.w	%d3,%d4

1:
	moveq.l	#-1,%d0
	move.b	(%a1)+,%d0
	dbf	%d4,2f

	rol.l	%d1,%d0
	and.l	%d0,(%a2)
	lea	30(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d5/%a2

	rts

2:
	rol.w	#8,%d0
	move.b	(%a1)+,%d0
	rol.l	%d5,%d0
	and.l	%d0,(%a2)
	addq.l	#2,%a2
	dbf	%d4,1b

	lea	30(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d5/%a2

	rts
