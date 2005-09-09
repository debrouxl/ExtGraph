| Subroutine of other RotateSprite functions.
| Courtesy of Joey Adams.

.text
.even
.globl RS_detrSCO
RS_detrSCO:
	neg.l %d0
	moveq #90,%d3
	divs.w %d3,%d0
	swap %d0
	blt.s 0f |the swap causes the negative test to lie on the divisor
	tst.w %d0
	bge.s 1f
0:
	add.w %d3,%d0
	swap %d0
	subq.w #1,%d0
	swap %d0
1:
	btst #16,%d0
	beq.s 2f
	sub.w %d3,%d0
	neg.w %d0
2:
	add.w %d0,%d0
	lea RS_sin8192tab,%a2
	move.w (%a2,%d0.w),%d3
	btst #17,%d0
	beq.s 3f
	neg.w %d3
3:
	move.w %d3,%a4 |sin8192
	swap %d0
	addq.w #1,%d0
	swap %d0
	sub.w #180,%d0
	neg.w %d0
	move.w (%a2,%d0.w),%d3
	btst #17,%d0
	beq.s 4f
	neg.w %d3
4:
	move.w %d3,%a5 |cos8192
	rts
