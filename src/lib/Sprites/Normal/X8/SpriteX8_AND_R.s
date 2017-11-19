| C prototype: void SpriteX8_AND_R(unsigned short x asm("%d0"), unsigned short y asm("%d1"), unsigned short height asm("%d2"), const unsigned char *sprt asm("%a1"), unsigned short bytewidth asm("%d3"), void *dest asm("%a0")) __attribute__((__regparm__));
| see SpriteX8_OR_R for comments

.include "common.s"

.text
.globl SpriteX8_AND_R
.even

SpriteX8_AND_R:
	movem.l	%d3-%d5/%a2,-(%sp)

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

E0:
 	movea.l	%a0,%a2
 	move.w	%d3,%d4

E1:
 	moveq.l	#-1,%d0
 	move.w	(%a1)+,%d0
	dbf	%d4,E2

	move.b	#-1,%d0
	rol.l	%d5,%d0
	and.l	%d0,(%a2)
	subq.l	#1,%a1
	lea	PLANE_BYTE_WIDTH(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d5/%a2
 	rts

E2:
 	rol.l	%d5,%d0
 	and.l	%d0,(%a2)
 	addq.l	#2,%a2
	dbf	%d4,E1

	lea	PLANE_BYTE_WIDTH(%a0),%a0
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts

O0:
 	movea.l	%a0,%a2
	move.w	%d3,%d4

O1:
	moveq.l	#-1,%d0
	move.b	(%a1)+,%d0
	dbf	%d4,O2

	rol.l	%d1,%d0
	and.l	%d0,(%a2)
	lea	PLANE_BYTE_WIDTH(%a0),%a0
r:
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts

O2:
	move.b  %d0,-(%sp)
	move.w  (%sp)+,%d0
|	rol.w	#8,%d0
	move.b	(%a1)+,%d0
	rol.l	%d5,%d0
	and.l	%d0,(%a2)
	addq.l	#2,%a2
	dbf	%d4,O1

	lea	PLANE_BYTE_WIDTH(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts
