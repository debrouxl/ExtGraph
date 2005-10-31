| C prototype: void SpriteX8_MASK(short x,short y,short h,unsigned char *sprt,unsigned char *mask,short bytewidth,void *dest) __attribute__((__stkparm__));
| see SpriteX8_OR_R for comments

.text
.globl SpriteX8_MASK
.even

SpriteX8_MASK:
	movem.l	%d3-%d6/%a2-%a3,-(%sp)

	lea     24+4(%sp),%a0
	move.w  (%a0)+,%d0
	move.w  (%a0)+,%d1
	move.w  (%a0)+,%d2
	move.l  (%a0)+,%a1
	move.l  (%a0)+,%a2
	move.w  (%a0)+,%d3
	move.l  (%a0)+,%a0

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

	lea     r+3(%pc),%a3
| Test: width odd ?
	btst.b  #0,%d3
	beq.s   w
	moveq   #E0-(r+2),%d1
	bra.s   p
w:
	moveq   #O0-(r+2),%d1

p:
	move.b  %d1,(%a3)

	move.w	%d5,%d1
	addq.w	#8,%d1

| Test: width odd ?
	btst.b  #0,%d3
	beq.s   O0

E0:
 	movea.l	%a0,%a3
 	move.w	%d3,%d4

E1:
 	moveq.l	#0,%d0
 	moveq.l	#-1,%d6
 	move.w	(%a1)+,%d0
 	move.w	(%a2)+,%d6

	dbf	%d4,E2

	clr.b	%d0
	st.b	%d6
	lsl.l	%d5,%d0
	rol.l	%d5,%d6
	and.l	%d6,(%a3)
	or.l	%d0,(%a3)

	subq.l	#1,%a1
	subq.l	#1,%a2

	lea	30(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d6/%a2-%a3
 	rts

E2:
 	lsl.l	%d5,%d0
 	rol.l	%d5,%d6
 	and.l	%d6,(%a3)
 	or.l	%d0,(%a3)
 	addq.l	#2,%a3
	dbf	%d4,E1

	lea	30(%a0),%a0
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d6/%a2-%a3
	rts

O0:
 	movea.l	%a0,%a3
	move.w	%d3,%d4

O1:
	moveq.l	#0,%d0
	moveq.l	#-1,%d6

	move.b	(%a1)+,%d0
	move.b	(%a2)+,%d6

	dbf	%d4,O2

	lsl.l	%d1,%d0
	rol.l	%d1,%d6

	and.l	%d6,(%a3)
	or.l	%d0,(%a3)

	lea	30(%a0),%a0
r:
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d6/%a2-%a3
	rts

O2:
	move.b  %d6,-(%sp)
	move.w  (%sp)+,%d6
|	rol.w	#8,%d6
	move.b  %d0,-(%sp)
	move.w  (%sp)+,%d0
|	lsl.w	#8,%d0

	move.b	(%a2)+,%d6
	move.b	(%a1)+,%d0

	lsl.l	%d5,%d0
	rol.l	%d5,%d6

	and.l	%d6,(%a3)
	or.l	%d0,(%a3)

	addq.l	#2,%a3
	dbf	%d4,O1

	lea	30(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d6/%a2-%a3
	rts
