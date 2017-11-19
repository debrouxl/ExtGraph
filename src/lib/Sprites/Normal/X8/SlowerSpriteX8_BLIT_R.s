| C prototype: void SlowerSpriteX8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt asm("%a1"),unsigned char *maskval,short w asm("%d3"),void *dest asm("%a0")) __attribute__((__stkparm__));
| see SpriteX8_OR_R for comments

.include "common.s"

.text
.globl SlowerSpriteX8_BLIT_R
.even

SlowerSpriteX8_BLIT_R:
	movem.l	%d3-%d6/%a2-%a4,-(%sp)

	move.l  28+4(%sp),%a2

	COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d4

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
 	movea.l	%a0,%a3
	move.w	%d3,%d4
	movea.l	%a2,%a4

1:
	moveq.l	#0,%d0
	moveq.l	#-1,%d6

	move.b	(%a1)+,%d0
	move.b	(%a4)+,%d6

	dbf	%d4,2f

	lsl.l	%d1,%d0
	rol.l	%d1,%d6

	and.l	%d6,(%a3)
	or.l	%d0,(%a3)

	lea	PLANE_BYTE_WIDTH(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d6/%a2-%a4
	rts

2:
	rol.w	#8,%d6
	lsl.w	#8,%d0

	move.b	(%a4)+,%d6
	move.b	(%a1)+,%d0

 	lsl.l	%d5,%d0
 	rol.l	%d5,%d6

 	and.l	%d6,(%a3)
 	or.l	%d0,(%a3)

 	addq.l	#2,%a3
	dbf	%d4,1b

	lea	PLANE_BYTE_WIDTH(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d6/%a2-%a4
	rts
