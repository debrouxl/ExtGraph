| C prototype: void RotateSprite16_R(unsigned short *srcSprite asm("%a0"),unsigned short *destSprite asm("%a1"),short height,short originX asm("%d1"),short originY asm("%d2"),long degreesClockwise asm("%d0"));
|
| Courtesy of Joey Adams.
| Modified by Lionel Debroux:
| * renamed labels.
| * slightly optimized for size (pc-relative SMC code instead of absolute one: smaller, less relocations).

.text
.even
.globl RotateSprite16_R
RotateSprite16_R:
	movem.l %d3-%d7/%a2-%a6,-(%a7)
	move.w 10*4+4(%a7),%d5 |height

	lea 10f(%pc),%a3
	move.l %a7,(%a3)

	neg.l %d0
	move.w #360,%d3
	divs.w %d3,%d0
	swap %d0
	tst.w %d0
	bge rs16_1
	add.w %d3,%d0
rs16_1:
	add.w %d0,%d0
	lea RS_sin8192tab,%a2
	move.w 0(%a2,%d0.w),%a4 |sin8192
	sub.w #270*2,%d0
	bge rs16_2
	add.w #360*2,%d0
rs16_2:
	move.w 0(%a2,%d0.w),%a5 |cos8192
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
	move.l %d3,%a7 |yv
	add.w %d5,%d2
	neg.w %d1
	move.l %a4,%d0
	lsl.l #4,%d0
	add.l %a5,%d0
	move.l %d0,%a6 |yvr
	move.l %a5,%d0
	lsl.l #4,%d0
	sub.l %a4,%d0
	move.w %d5,10f-rs16_heightdropoff+2(%a3)
	move.l %d0,%a3 |xvr
	move.l %a1,%a2 |origDestSprite
	add.w %d5,%d5
	adda.w %d5,%a1
rs16_yloop:
	cmpa.l %a2,%a1
	bls rs16_endy
	moveq #0,%d6
	moveq #15,%d5
rs16_xloop:
	moveq #13,%d7
	move.l %a7,%d0
	asr.l %d7,%d0
	add.w %d2,%d0 |y2
	blt rs16_continue
    rs16_heightdropoff:
	cmp.w #0xDEED,%d0
	bge rs16_continue
	add.w %d0,%d0
	move.w 0(%a0,%d0.w),%d3 |current row data
	move.l %d4,%d0
	asr.l %d7,%d0
	add.w %d1,%d0 |x2
	blt rs16_continue
	cmp.w #16,%d0
	bge rs16_continue
	eor.w #15,%d0
	btst %d0,%d3
	beq rs16_continue
	bset %d5,%d6
rs16_continue:
	add.l %a4,%a7
	add.l %a5,%d4
	dbra %d5,rs16_xloop
	move.w %d6,-(%a1)
	sub.l %a6,%a7
	sub.l %a3,%d4
	bra rs16_yloop
rs16_endy:
	|%d0.l is general purpose
	|%d1.w is originX
	|%d2.w is originY
	|%d3.l is general purpose
	|%d4.l is xv
	|%d5.w is height, then tracer (%d5.l)
	|%d6.l is rowresult
	|%d7.l is general purpose
	|%a0.a is source address
	|%a1.a is destination address
	|%a2.a is original destination
	|%a3.a is xvr
	|%a4.a is sin -degrees *8192
	|%a5.a is cos -degrees *8192
	|%a6.a is yvr
	|%a7.a is yv
	move.l 10f(%pc),%a7
	movem.l (%a7)+,%d3-%d7/%a2-%a6
	rts

10:
	.long 0
