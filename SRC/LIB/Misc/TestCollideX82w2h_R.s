| C prototype: short TestCollideX82w2h_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1,short bytewidth0,short bytewidth1,short height0,short height1,const void *data0 asm("%a0"),const void *data1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl TestCollideX82w2h_R
.even

TestCollideX82w2h_R:
	movem.l %d3-%d7/%a2-%a5,-(%a7)
	movem.w 9*4+4(%a7),%d3-%d7
	sub.w %d3,%d1
	sub.w %d2,%d0
	bge 1f
	exg.l %a0,%a1
	exg.l %d4,%d5
	exg.l %d6,%d7
	neg.w %d0
	neg.w %d1
1:
	tst.w %d1
	bge 2f
	add.w %d1,%d6
	muls.w %d4,%d1
	suba.l %d1,%a0
	bra 3f
2:
	sub.w %d1,%d7
	muls.w %d5,%d1
	adda.l %d1,%a1
3:
	cmp.w %d7,%d6
	bge 4f
	move.w %d6,%d7
4:
	move.w %d0,%d2
	and.w #7,%d0 |shiftcount
	moveq #-1,%d1
	lsr.b %d0,%d1 |rightmask
	lsr.w #3,%d2 |bytex0
	adda.w %d2,%a1
	|%d3,%d6 free
	move.w %d5,%d3
	sub.w %d2,%d3 |bytewidth
	moveq #0,%d6 |appendix
	cmp.w %d3,%d4
	blt 5f
	moveq #1,%d6
	bra 6f
5:
	move.w %d4,%d3
6:
	tst.w %d3
	ble 11f
	sub.w %d6,%d3
	sub.w %d3,%d4
	sub.w %d3,%d5
	movea.w %d4,%a2 |sprt0skip
	movea.w %d5,%a3 |sprt1skip
	movea.w %d3,%a4 |bytewidth
	move.w %d1,%d4
	not.b %d4 |leftmask
	move.w %d0,%d5 |shiftcount
	moveq #1,%d0 |positive return value
7:
	subq.w #1,%d7
	blt 11f
	move.w %a4,%d3 |tempshort
8:
	subq.w #1,%d3
	blt 9f
	move.b (%a0)+,%d2 |tempchar
	ror.b %d5,%d2
	movea.w %d2,%a5 |tempcharorig
	and.b %d1,%d2
	and.b (%a1)+,%d2
	bne 0f
	move.w %a5,%d2
	and.b %d4,%d2
	and.b (%a1),%d2
	bne 0f
	bra 8b
9:
	tst.w %d6
	beq 10f
	move.b (%a0),%d2
	lsr.b %d5,%d2
	and.b (%a1),%d2
	bne 0f
10:
	adda.l %a2,%a0
	adda.l %a3,%a1
	bra 7b
11:
	moveq #0,%d0
0:
	movem.l (%a7)+,%d3-%d7/%a2-%a5
	rts
	