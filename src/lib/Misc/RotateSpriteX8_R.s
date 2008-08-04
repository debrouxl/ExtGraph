| C prototype: void RotateSpriteX8_R(const unsigned char *src asm("%a0"), unsigned char *dest asm("%a1"), unsigned short width, short height, short originX asm("%d1"), short originY asm("%d2"), long degreesClockwise asm("%d0")) __attribute__((__stkparm__));
|
| Courtesy of Joey Adams.
| Modified by Lionel Debroux:
| * renamed labels.
| * slightly optimized for size.

.text
.even
.globl RotateSpriteX8_R
RotateSpriteX8_R:
	movem.l %d3-%d7/%a2-%a6,-(%a7)
	lea 10*4+4(%a7),%a3
	move.w (%a3)+,%d6 |width  *****
	move.w (%a3)+,%d5 |height
	lea 10f(%pc),%a3
	move.w %d1,rsX8_oxdropoff+2-10f(%a3)
	move.w %d2,rsX8_oydropoff+2-10f(%a3)
	move.w %d5,rsX8_heightdropoff+2-10f(%a3)
	move.w %d6,rsX8_widthdropoff1+2-10f(%a3)
	jbsr RS_detrSCO
	move.l %a7,(%a3) | Save sp.

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
	move.w %d6,rsX8_widthdropoff2+2-10f(%a3)
	lsr.w #3,%d6
	addq.w #1,%d6 |bpr
	mulu.w %d6,%d5
	lea (%a1,%d5.l),%a2 |endDestSprite
	moveq #7,%d5 |bitTracer
	moveq #0,%d1 |byteresult
rsX8_yloop:
	cmpa.l %a2,%a1
	bcc.s rsX8_endy
    rsX8_widthdropoff2:
	move.w #0xDEED,%d2
rsX8_xloop:
	moveq #13,%d7
	move.l %a7,%d0
	asr.l %d7,%d0
    rsX8_oydropoff:
	add.w #0xDEED,%d0 |y2
	blt.s rsX8_continue
    rsX8_heightdropoff:
	cmp.w #0xDEED,%d0
	bge.s rsX8_continue
	mulu.w %d6,%d0
	lea (%a0,%d0.l),%a3 |pointer to current row
	move.l %d4,%d0
	asr.l %d7,%d0
    rsX8_oxdropoff:
	add.w #0xDEED,%d0 |x2
	blt.s rsX8_continue
    rsX8_widthdropoff1:
	cmp.w #0xDEED,%d0
	bge.s rsX8_continue
	move.w %d0,%d7
	lsr.w #3,%d0 |x2r
	not.w %d7
	and.w #7,%d7
	btst %d7,(%a3,%d0.w)
	beq.s rsX8_continue
	bset %d5,%d1
rsX8_continue:
	subq.w #1,%d5
	bge.s rsX8_loopback
	moveq #7,%d5
	move.b %d1,(%a1)+
	moveq #0,%d1
rsX8_loopback:
	add.l %a4,%a7
	add.l %a5,%d4
	dbf %d2,rsX8_xloop
	cmp.w #7,%d5
	beq.s rsX8_noresetbyte
	moveq #7,%d5
	move.b %d1,(%a1)+
	moveq #0,%d1
rsX8_noresetbyte:
	sub.l %a6,%a7
	sub.l %d3,%d4
	bra.s rsX8_yloop
rsX8_endy:
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
