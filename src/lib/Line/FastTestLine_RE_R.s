| C prototype: char FastTestLine_RE_R(void *plane asm("%a0"), unsigned short x1 asm("%d0"), unsigned short y1 asm("%d1"), unsigned short x2 asm("%d2"), unsigned short y2 asm("%d3")) __attribute__((__regparm__));
|
| FastTestLine_R by Lionel Debroux.
| Based on FastLine_*_R by Julien Richard-Foy / Lionel Debroux.


.text
.globl FastTestLine_RE_R
.even

FastTestLine_RE_R:
	movem.l	%d3-%d5,-(%sp)

	cmp.w	%d0,%d2
	bhi.s	10f
	exg.l	%d0,%d2
	exg.l	%d1,%d3
10:
	move.w	%d3,%d4
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

	move.w  %d2,%d0
	not.w	%d0
	andi.w	#7,%d0	| d0 = msk0

	moveq.l	#-30,%d4

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

	addq.w	#1,%d0
	cmpi.w  #8,%d0
	bne.s	5f
	subq.l  #1,%a0
	moveq.l	#0,%d0

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

	addq.w	#1,%d0
	cmpi.w  #8,%d0
	bne.s	7f
	subq.l	#1,%a0
	moveq.l	#0,%d0

7:
	dbf	%d5,2b
	bra.s   0b

/*	cmp.w	%d0,%d2
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

	moveq.l	#30,%d4
	moveq.l	#-30,%d5

	tst.w	%d3
	bpl.s	DYPos_FTL_R

	exg.l	%d4,%d5
	neg.w	%d3

DYPos_FTL_R:
	cmp.w	%d2,%d3	| dx < dy ?
	bhi.s	DY_FTL_R

	lea     IncLineX_FTL_R+2(%pc),%a2
	move.w	%d4,(%a2)
	move.w	%d5,4(%a2)

	move.w	%d2,%d4	| d4 = dx
	lsr.w	#1,%d4
	neg.w	%d4	| d4 = -dx/2 = e

	move.w	%d2,%d5
	beq.s	OnePix_FTL_R
	subq.w	#1,%d5
	lsr.w	#1,%d5	| d5 = (dx - 1)/2 = l

XLoop_FTL_R:
	btst.b	%d0,(%a0)
	bne.s   End_FTL_R

	subq.w	#1,%d0
	bpl.s	MskOkX_FTL_R
	addq.l	#1,%a0
	moveq.l	#7,%d0

Msk1OkX_FTL_R:
	add.b	%d1,%d1
	bne.s	Msk2OkX_FTL_R
	subq.l	#1,%a1
	moveq.l	#1,%d1

Msk2OkX_FTL_R:
	add.w	%d3,%d4	| e += dy
	ble.s	NoIncLineX_FTL_R

	sub.w	%d2,%d4	| e += dx
IncLineX_FTL_R:
	lea.l	30(%a0),%a0
	lea.l	-30(%a1),%a1

NoIncLineX_FTL_R:
	dbf	%d5,XLoop_FTL_R
| Prevent the center from being drawn twice.
| This is a problem only in A_XOR mode.
End_FTL_R:
	btst     #0,%d2
	bne.s    __Draw_center_only_once_FTL_R__
	or.b     %d6,(%a0)                      | Draw the center only once.
__Draw_center_only_once_FTL_R__:
	movem.l	(%sp)+,%d3-%d5/%a2
	rts

DY_FTL_R:
	lea     IncLineY_FTL_R+2(%pc),%a2
	move.w	%d4,(%a2)
	move.w	%d5,4(%a2)

	move.w	%d3,%d4
	lsr.w	#1,%d4
	neg.w	%d4	| d4 = -dy/2 = e

	move.w	%d3,%d5
	subq.w	#1,%d5
	lsr.w	#1,%d5	| d5 = (dy - 1)/2 = l

YLoop_FTL_R:
	bchg.b	%d0,(%a0)
	eor.b	%d1,(%a1)

IncLineY_FTL_R:
	lea.l	30(%a0),%a0
	lea.l	-30(%a1),%a1

	add.w	%d2,%d4	| e += dx
	ble.s	NoIncColY_FTL_R

	sub.w	%d3,%d4	| e -= dy
	subq.w	#1,%d0
	bpl.s	Msk1OkY_FTL_R
	addq.l	#1,%a0
	moveq.l	#7,%d0

Msk1OkY_FTL_R:
	add.b	%d1,%d1
	bne.s	Msk2OkY_FTL_R
	subq.l	#1,%a1
	moveq.l	#1,%d1
Msk2OkY_FTL_R:
NoIncColY_FTL_R:
	dbf	%d5,YLoop_FTL_R
	bra.s   OnePix_FTL_R
*/
