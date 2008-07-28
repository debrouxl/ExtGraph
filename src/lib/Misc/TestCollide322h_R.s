| C prototype: short TestCollide322h_R(short x0 asm("%d0"), short y0 asm("%d1"), short x1 asm("%d2"), short y1 asm("%d3"), unsigned short height0, unsigned short height1, const unsigned long *data0 asm("%a0"), const unsigned long *data1 asm("%a1")) __attribute__((__stkparm__));

.text
.globl TestCollide322h_R
.even

TestCollide322h_R:
	move.l %d3,-(%a7)
	sub.w %d3,%d1
	move.l 8(%a7),%d3
	sub.w %d2,%d0
	bge 1f
	exg.l %a0,%a1
	swap %d3
	neg.w %d0
	neg.w %d1
1:
	move.w %d3,%d2 |height1
	swap %d3 |height0
	tst.w %d1
	bge 2f
	add.w %d1,%d3
	lsl.w #2,%d1
	suba.w %d1,%a0
	bra 3f
2:
	sub.w %d1,%d2
	lsl.w #2,%d1
	adda.w %d1,%a1
3:
	cmp.w %d2,%d3
	bge 4f
	move.w %d3,%d2
4:
	move.l (%a7)+,%d3
	cmp.w #32,%d0
	bge 0f
5:
	subq.w #1,%d2
	blt 0f
	move.l (%a0)+,%d1
	lsr.l %d0,%d1
	and.l (%a1)+,%d1
	beq 5b
	moveq #1,%d0
	rts
0:	
	moveq #0,%d0
	rts
