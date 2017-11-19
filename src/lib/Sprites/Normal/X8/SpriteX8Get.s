| C prototype: void SpriteX8Get(unsigned short x, unsigned short y, unsigned short height, const void* src, unsigned char* dest, unsigned short bytewidth) __attribute__((__stkparm__));

.include "common.s"

.text
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

	subq.w	#1,%d2
	blt.s   9f

	COMPUTE_HALF_PLANE_BYTE_WIDTH %d1,%d4
	add.w	%d1,%d1

	move.w	%d0,%d4
	lsr.w	#3,%d4
	add.w	%d4,%d1

	adda.w	%d1,%a1

	moveq	#PLANE_BYTE_WIDTH,%d6
	sub.w	%d3,%d6			| constant offset from the end of a line to the beginning of the next one

	and.w	#7,%d0			| shifting coeff
	moveq   #8,%d5			| 8-shift
	sub.w	%d0,%d5

	tst.w   %d0
	beq.s	2f

	subq.w	#2,%d3			| we need w-2 since first and last bytes are not in a loop
	blt.s   5f			| branch taken <=> sprite is small.
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

9:
	movem.l	(%sp)+,%d3-%d6
	rts


2:				| loop if shift == 0
	subq.w	#1,%d3
	blt.s   7f

3:
	move.w	%d3,%d1

4:
	move.b	(%a1)+,(%a0)+
	dbf	%d1,4b

	adda.w	%d6,%a1
	dbf	%d2,3b

7:
	movem.l	(%sp)+,%d3-%d6
	rts

5:
	addq.w  #1,%d3
	bne.s   7b			| bytewidth == 0 <=> nothing to do.
6:
| Bytewidth == 1.
	move.b	(%a1)+,%d4
	lsl.b	%d0,%d4
	move.b	(%a1),%d3
	lsr.b	%d5,%d3
	or.b	%d4,%d3
	move.b  %d3,(%a0)+

	adda.w	%d6,%a1
	dbf	%d2,6b

	movem.l	(%sp)+,%d3-%d6
	rts
