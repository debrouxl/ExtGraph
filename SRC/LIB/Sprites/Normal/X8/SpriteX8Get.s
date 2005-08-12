| C prototype: void SpriteX8Get(short x,short y,short h,void* src,unsigned char* dest,short w) __attribute__((__stkparm__));

.data
.globl SpriteX8Get
.even 

SpriteX8Get:
	movem.l	%d3-%d6,-(%sp)

	lea     16+4(%sp),%a0
	move.w  (%a0)+,%d0
	move.w  (%a0)+,%d1
	move.w  (%a0)+,%d2
	move.l  (%a0)+,%a1
	move.w  4(%a0),%d3
	move.l  (%a0),%a0

	add.w	%d1,%d1
	move.w	%d1,%d4
	lsl.w	#4,%d4
	sub.w	%d1,%d4
	
	move.w	%d0,%d1
	lsr.w	#3,%d1
	add.w	%d1,%d4
	
	adda.w	%d4,%a1

	moveq	#30,%d6
	sub.w	%d3,%d6			| constant offset from the end of a line to the beginning of the next one
	subq.w	#2,%d3			| we need w-2 since first and last bytes are not in a loop
	
	andi.w	#7,%d0			| shifting coeff
	beq.s	2f
	
	moveq	#8,%d5			| 8-shift
	sub.w	%d0,%d5
	
	subq.w	#1,%d2

0:
	move.b	(%a1)+,%d4		| first byte of the line
	lsl.b	%d0,%d4
	move.b	%d4,(%a0)
	
	move.w	%d3,%d1

1:
	move.b	(%a1),%d4		| middle bytes
	lsr.b	%d5,%d4
	or.b	%d4,(%a0)+
	
	move.b	(%a1)+,%d4
	lsl.b	%d0,%d4
	move.b	%d4,(%a0)

	dbf	%d1,1b

	move.b	(%a1),%d4		| last byte of the line
	lsr.b	%d5,%d4
	or.b	%d4,(%a0)+
	
	adda.w	%d6,%a1
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d6
	rts


2:				| loop if shift == 0
	addq.w	#1,%d3
	subq.w	#1,%d2
	
3:
	move.w	%d3,%d1
	
4:
	move.b	(%a1)+,(%a0)+
	dbf	%d1,4b

	adda.w	%d6,%a1
	dbf	%d2,3b
	
	movem.l	(%sp)+,%d3-%d6
	rts
