| C prototype: char FastTestLine_LE_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),void *plane asm("%a0"));
|
| FastTestLine_R by Lionel Debroux.
| Based on FastLine_*_R by Julien Richard-Foy / Lionel Debroux.

.text
.globl FastTestLine_LE_R
.even

FastTestLine_LE_R:
	movem.l	%d3-%d5,-(%sp)

	cmp.w	%d0,%d2
	bhi.s	10f
	exg.l	%d0,%d2
	exg.l	%d1,%d3
10:
	move.w	%d1,%d4
	add.w	%d4,%d4
	move.w	%d4,%d5
	lsl.w	#4,%d4
	sub.w	%d5,%d4	| d4 = 30*y1
	move.w	%d0,%d5
	lsr.w	#3,%d5	| d5 = x1/8
	add.w	%d5,%d4
	adda.w	%d4,%a0

	sub.w	%d1,%d3	| d3 = dy
	move.w	%d2,%d1	| d1 = x2
	sub.w	%d0,%d2	| d2 = x2-x1 = dx

	not.w	%d0
	andi.w	#7,%d0	| d0 = msk0

	moveq.l	#30,%d4

	tst.w	%d3
	bpl.s	10f

	neg.w	%d4
	neg.w	%d3

10:
	cmp.w	%d2,%d3	| dx < dy ?
	bhi.s	4f

	move.w	%d2,%d1	| d1 = dx
	beq.s	3f
	lsr.w	#1,%d1
	neg.w	%d1	| d1 = -dx/2 = e

	move.w	%d2,%d5

2:
	btst.b	%d0,(%a0)
	bne.s   1f

	subq.w	#1,%d0
	bpl.s	5f
	addq.l	#1,%a0
	moveq.l	#7,%d0

5:
	add.w	%d3,%d1	| e += dy
	ble.s	6f

	sub.w	%d2,%d1	| e -= dx

	adda.w  %d4,%a0

6:
	dbf	%d5,2b
0:
	moveq   #0,%d0
	movem.l	(%sp)+,%d3-%d5
	rts

3:
	btst.b	%d0,(%a0)
1:
	sne.b   %d0
	movem.l	(%sp)+,%d3-%d5
	rts


4:
	move.w	%d3,%d1
	lsr.w	#1,%d1
	neg.w	%d1	| d1 = -dy/2 = e

	move.w	%d3,%d5

2:
	btst.b	%d0,(%a0)
	bne.s   1b

	adda.w  %d4,%a0

	add.w	%d2,%d1	| e += dx
	ble.s	7f

	sub.w	%d3,%d1	| e -= dy

	subq.w	#1,%d0
	bpl.s	7f
	addq.l	#1,%a0
	moveq.l	#7,%d0

7:
	dbf	%d5,2b
	bra.s   0b
