| C prototype: void SpriteX8_BLIT_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned char *sprt asm("%a1"),unsigned char *maskval,register short w asm("%d3"),register void *dest asm("%a0")) __attribute__((__stkparm__));
| see SpriteX8_OR_R for comments

.data
.globl SpriteX8_BLIT_R
.even 

SpriteX8_BLIT_R:
	movem.l	%d3-%d6/%a2-%a4,-(%sp)

	move.l  28+4(%sp),%a2

	move.w	%d1,%d4
	lsl.w	#4,%d1
	sub.w	%d4,%d1
 
	move.w	%d0,%d4
	andi.w	#15,%d4

	lsr.w	#4,%d0
	add.w	%d1,%d0	
	add.w	%d0,%d0	
	
	adda.w	%d0,%a0	
 
 	moveq.l	#16,%d5
 	sub.w	%d4,%d5	

	move.w	%d5,%d1
	addq.w	#8,%d1
	
 	subq.w	#1,%d2	
	subq.w	#1,%d3

	lea     r+3(%pc),%a4
| Test: width odd ?
	btst.b  #0,%d3
	beq.s   w
	moveq   #E0-(r+2),%d1
	bra.s   p
w:
	moveq   #O0-(r+2),%d1

p:
	move.b  %d1,(%a4)

	move.w	%d5,%d1
	addq.w	#8,%d1
	
| Test: width odd ?
	btst.b  #0,%d3
	beq.s   O0
	
E0:
 	movea.l	%a0,%a3
 	move.w	%d3,%d4	
	movea.l	%a2,%a4
	 	
E1:
 	moveq.l	#0,%d0	
 	moveq.l	#-1,%d6
 	move.w	(%a1)+,%d0
 	move.w	(%a4)+,%d6
	dbf	%d4,E2

	clr.b	%d0
	st.b	%d6
	lsl.l	%d5,%d0
	rol.l	%d5,%d6

	and.l	%d6,(%a3)
	or.l	%d0,(%a3)
	
	subq.l	#1,%a1
	subq.l	#1,%a4
	
	lea	30(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d6/%a2-%a4
 	rts
 
E2:
 	lsl.l	%d5,%d0	
 	rol.l	%d5,%d6
 	and.l	%d6,(%a3)
 	or.l	%d0,(%a3)
 	addq.l	#2,%a3
	dbf	%d4,E1

	lea	30(%a0),%a0
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d6/%a2-%a4
	rts

O0:
 	movea.l	%a0,%a3
	move.w	%d3,%d4
	movea.l	%a2,%a4

O1:
	moveq.l	#0,%d0
	moveq.l	#-1,%d6
	
	move.b	(%a1)+,%d0
	move.b	(%a4)+,%d6
		
	dbf	%d4,O2

	lsl.l	%d1,%d0
	rol.l	%d1,%d6
	
	and.l	%d6,(%a3)
	or.l	%d0,(%a3)
	
	lea	30(%a0),%a0
r:
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d6/%a2-%a4
	rts
	
O2:
	move.b  %d6,-(%sp)
	move.w  (%sp)+,%d6
|	rol.w	#8,%d6
	move.b  %d0,-(%sp)
	move.w  (%sp)+,%d0
|	lsl.w	#8,%d0

	move.b	(%a4)+,%d6
	move.b	(%a1)+,%d0
	
 	lsl.l	%d5,%d0	
 	rol.l	%d5,%d6
 	
 	and.l	%d6,(%a3)
 	or.l	%d0,(%a3)
 	
 	addq.l	#2,%a3
	dbf	%d4,O1
	
	lea	30(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d6/%a2-%a4
	rts
