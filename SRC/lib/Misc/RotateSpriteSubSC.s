| Subroutine of other RotateSprite functions.
| Courtesy of Joey Adams.

.text
.even
.globl RS_detrSC
RS_detrSC:
	jbsr RS_detrSCO
	neg.w %d1
	sub.w %d5,%d2
	move.w %a5,%d0
	muls.w %d1,%d0
	move.w %a4,%d4
	muls.w %d2,%d4
	add.l %d0,%d4 |xv
	move.w %a5,%d0
	muls.w %d2,%d0
	move.w %a4,%d3
	muls.w %d1,%d3
	sub.l %d0,%d3
	add.w %d5,%d2
	neg.w %d1
	move.l %a4,%d0
	rts
