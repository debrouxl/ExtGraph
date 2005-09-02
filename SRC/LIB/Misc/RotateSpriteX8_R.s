| C prototype: void RotateSpriteX8_R(unsigned char *srcSprite asm("%a0"),unsigned char *destSprite asm("%a1"),short width,short height,short originX asm("%d1"),short originY asm("%d2"),long degreesClockwise asm("%d0"));
|
| Courtesy of Joey Adams.
| Modified by Lionel Debroux:
| * renamed labels.
| * slightly optimized for size (pc-relative SMC code instead of absolute one: smaller, less relocations).

.text
.even
.globl RotateSpriteX8_R
RotateSpriteX8_R:
	movem.l %d3-%d7/%a2-%a6,-(%a7)
	lea 10*4+4(%a7),%a3
	move.w (%a3)+,%d6 |width  *****
	move.w (%a3)+,%d5 |height

	lea 10f(%pc),%a3
	move.l %a7,(%a3)

	move.w %d1,10f-rs8X_oxdropoff+2(%a3)
	move.w %d2,10f-rs8X_oydropoff+2(%a3)
	move.w %d5,10f-rs8X_heightdropoff+2(%a3)
	move.w %d6,10f-rs8X_widthdropoff1+2(%a3)

	neg.l %d0
	move.w #360,%d3
	divs.w %d3,%d0
	swap %d0
	tst.w %d0
	bge 1f
	add.w %d3,%d0
1:
	add.w %d0,%d0
	lea RS_sin8192tab,%a2
	move.w 0(%a2,%d0.w),%a4 |sin8192
	sub.w #270*2,%d0
	bge 1f
	add.w #360*2,%d0
1:
	move.w 0(%a2,%d0.w),%a5 |cos8192
	neg.w %d1
	move.w %a4,%d4
	move.w %d4,%d7
	muls.w %d1,%d7
	move.w %a5,%d0
	muls.w %d2,%d0
	sub.l %d0,%d7
	move.l %d7,%a7 |yv
	muls.w %d2,%d4
	move.w %a5,%d0
	muls.w %d1,%d0
	add.l %d0,%d4 |xv
	move.w %a4,%d0
	muls.w %d6,%d0
	sub.l %a5,%d0
	move.l %d0,%a6 |yvr
	move.w %a5,%d3
	muls.w %d6,%d3
	add.l %a4,%d3 |xvr
	subq.w #1,%d6
	move.w %d6,10f-rs8X_widthdropoff2+2(%a3)
	lsr.w #3,%d6
	addq.w #1,%d6 |bpr
	mulu.w %d6,%d5
	lea 0(%a1,%d5.l),%a2 |endDestSprite
	moveq #7,%d5 |bitTracer
	moveq #0,%d1 |byteresult
rs8X_yloop:
	cmpa.l %a2,%a1
	bcc rs8X_endy
    rs8X_widthdropoff2:
	move.w #0xDEED,%d2
rs8X_xloop:
	moveq #13,%d7
	move.l %a7,%d0
	asr.l %d7,%d0
    rs8X_oydropoff:
	add.w #0xDEED,%d0 |y2
	blt rs8X_continue
    rs8X_heightdropoff:
	cmp.w #0xDEED,%d0
	bge rs8X_continue
	mulu.w %d6,%d0
	lea 0(%a0,%d0.l),%a3 |pointer to current row
	move.l %d4,%d0
	asr.l %d7,%d0
    rs8X_oxdropoff:
	add.w #0xDEED,%d0 |x2
	blt rs8X_continue
    rs8X_widthdropoff1:
	cmp.w #0xDEED,%d0
	bge rs8X_continue
	move.w %d0,%d7
	lsr.w #3,%d0 |x2r
	not.w %d7
	and.w #7,%d7
	btst %d7,0(%a3,%d0.w)
	beq rs8X_continue
	bset %d5,%d1
rs8X_continue:
	subq.w #1,%d5
	bge rs8X_loopback
	moveq #7,%d5
	move.b %d1,(%a1)+
	moveq #0,%d1
rs8X_loopback:
	add.l %a4,%a7
	add.l %a5,%d4
	dbra %d2,rs8X_xloop
	cmp.w #7,%d5
	beq rs8X_noresetbyte
	moveq #7,%d5
	move.b %d1,(%a1)+
	moveq #0,%d1
rs8X_noresetbyte:
	sub.l %a6,%a7
	sub.l %d3,%d4
	bra rs8X_yloop
rs8X_endy:
	|%d0.l is general purpose
	|%d1.w is originX, then byteresult
	|%d2.w is originY, then x
	|%d3.l is xvr
	|%d4.l is xv
	|%d5.w is height, then tracer (%d5.l)
	|%d6.l is bpr
	|%d7.l is general purpose
	|%a0.a is source address
	|%a1.a is destination address
	|%a2.a is end destination
	|%a3.a is general purpose
	|%a4.a is sin -degrees *8192
	|%a5.a is cos -degrees *8192
	|%a6.a is yvr
	|%a7.a is yv
	move.l 10f(%pc),%a7
	movem.l (%a7)+,%d3-%d7/%a2-%a6
	rts

10:
	.long 0
