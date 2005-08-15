| C prototype: void SlowerSpriteX8Get_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register void *src asm("%a1"),register unsigned char *dest asm("%a0"),register short bytewidth asm("%d3"));

.data
.globl SlowerSpriteX8Get_R
.even 

SlowerSpriteX8Get_R:
	movem.l	%d3-%d6,-(%sp)
	
	subq.w	#1,%d2
	blt.s   7f

	tst.w   %d3
	beq.s   7f
	
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
	
	and.w	#7,%d0			| shifting coeff
	moveq   #8,%d5			| 8-shift
	sub.w	%d0,%d5

	subq.w	#2,%d3			| we need w-2 since first and last bytes are not in a loop
0:
	move.b	(%a1)+,%d4		| first byte of the line
	lsl.b	%d0,%d4
	move.b	%d4,(%a0)
	
	move.w	%d3,%d1
	blt.s   2f
1:
	move.b	(%a1),%d4		| middle bytes
	lsr.b	%d5,%d4
	or.b	%d4,(%a0)+
	
	move.b	(%a1)+,%d4
	lsl.b	%d0,%d4
	move.b	%d4,(%a0)

	dbf	%d1,1b

2:
	move.b	(%a1),%d4		| last byte of the line
	lsr.b	%d5,%d4
	or.b	%d4,(%a0)+
	
	adda.w	%d6,%a1
	dbf	%d2,0b

7:
	movem.l	(%sp)+,%d3-%d6
	rts
