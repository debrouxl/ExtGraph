| C prototype: void FastLine_Erase_R(void *plane asm("%a0"), unsigned short x1 asm("%d0"), unsigned short y1 asm("%d1"), unsigned short x2 asm("%d2"), unsigned short y2 asm("%d3")) __attribute__((__regparm__));
|
| FastLine_Erase_R by Julien Richard-Foy (jackiechan).
| Converted to GNU as ASM by Lionel Debroux.

.text
.globl FastLine_Erase_R
.even

FastLine_Erase_R:
	movem.l	%d3-%d6/%a2,-(%sp)

	cmp.w	%d0,%d2
	bhi.s	2f
	exg.l	%d0,%d2
	exg.l	%d1,%d3
2:
	movea.l	%a0,%a1

	move.w	%d1,%d4
	add.w	%d4,%d4
	move.w	%d4,%d5
	lsl.w	#4,%d4
	sub.w	%d5,%d4	| d4 = 30*y1
	move.w	%d0,%d5
	lsr.w	#3,%d5	| d5 = x1/8
	add.w	%d5,%d4
	adda.w	%d4,%a0

	move.w	%d3,%d4
	add.w	%d4,%d4
	move.w	%d4,%d5
	lsl.w	#4,%d4
	sub.w	%d5,%d4	| d4 = 30*y2
	move.w	%d2,%d5
	lsr.w	#3,%d5	| d5 = x2/8
	add.w	%d5,%d4
	adda.w	%d4,%a1

	sub.w	%d1,%d3	| d3 = dy
	move.w	%d2,%d1	| d1 = x2
	sub.w	%d0,%d2	| d2 = x2-x1 = dx

	moveq.l	#7,%d4

	not.w	%d0
	and.w	%d4,%d0	| d0 = msk1

	not.w	%d1
	and.w	%d1,%d4
	moveq.l	#0,%d1
	bset.l	%d4,%d1	| d1 = msk2
	not.b   %d1

	moveq.l	#30,%d6

	tst.w	%d3
	bpl.s	DYPos_FL_E_R

	neg.w   %d6
	neg.w	%d3

DYPos_FL_E_R:
	cmp.w	%d2,%d3	| dx < dy ?
	bhi.s	DY_FL_E_R

	move.w	%d2,%d4	| d4 = dx
	lsr.w	#1,%d4
	neg.w	%d4	| d4 = -dx/2 = e

	move.w	%d2,%d5
	beq.s	OnePix_FL_E_R
	subq.w	#1,%d5
	lsr.w	#1,%d5	| d5 = (dx - 1)/2 = l

XLoop_FL_E_R:
	bclr.b	%d0,(%a0)
	and.b	%d1,(%a1)

	subq.w	#1,%d0
	bpl.s	Msk1OkX_FL_E_R
	addq.l	#1,%a0
	moveq.l	#7,%d0

Msk1OkX_FL_E_R:
	rol.b	#1,%d1
	bcs.s	Msk2OkX_FL_E_R
	subq.l	#1,%a1
	moveq.l	#~1,%d1

Msk2OkX_FL_E_R:
	add.w	%d3,%d4	| e += dy
	ble.s	NoIncLineX_FL_E_R

	sub.w	%d2,%d4	| e += dx
	adda.w  %d6,%a0
	suba.w  %d6,%a1

NoIncLineX_FL_E_R:
	dbf	%d5,XLoop_FL_E_R
OnePix_FL_E_R:
	bclr.b	%d0,(%a0)

	movem.l	(%sp)+,%d3-%d6/%a2
	rts

DY_FL_E_R:
	move.w	%d3,%d4
	lsr.w	#1,%d4
	neg.w	%d4	| d4 = -dy/2 = e

	move.w	%d3,%d5
	subq.w	#1,%d5
	lsr.w	#1,%d5	| d5 = (dy - 1)/2 = l

YLoop_FL_E_R:
	bclr.b	%d0,(%a0)
	and.b	%d1,(%a1)

	adda.w  %d6,%a0
	suba.w  %d6,%a1

	add.w	%d2,%d4	| e += dx
	ble.s	NoIncColY_FL_E_R

	sub.w	%d3,%d4	| e -= dy
	subq.w	#1,%d0
	bpl.s	Msk1OkY_FL_E_R
	addq.l	#1,%a0
	moveq.l	#7,%d0

Msk1OkY_FL_E_R:
	rol.b	#1,%d1
	bcs.s	Msk2OkY_FL_E_R
	subq.l	#1,%a1
	moveq.l	#~1,%d1
Msk2OkY_FL_E_R:
NoIncColY_FL_E_R:
	dbf	%d5,YLoop_FL_E_R
	bclr.b	%d0,(%a0)

	movem.l	(%sp)+,%d3-%d6/%a2
	rts
