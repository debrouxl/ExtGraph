| C prototype: void SlowerSpriteX8_MASK_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),register unsigned char *sprt asm("%a1"),unsigned char *mask,register short w asm("%d3"),register void *dest asm("%a0"));
| see SpriteX8_OR_R for comments

.data
.globl SlowerSpriteX8_MASK_R
.even 

SlowerSpriteX8_MASK_R:
	movem.l	%d3-%d6/%a2-%a3,-(%sp)

	move.l  24+4(%sp),%a2

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

0:
 	movea.l	%a0,%a3
	move.w	%d3,%d4

1:
	moveq.l	#0,%d0
	moveq.l	#-1,%d6
	
	move.b	(%a1)+,%d0
	move.b	(%a2)+,%d6
		
	dbf	%d4,2f
	
	lsl.l	%d1,%d0
	rol.l	%d1,%d6
	
	and.l	%d6,(%a3)
	or.l	%d0,(%a3)
	
	lea	30(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d6/%a2-%a3
	rts
	
2:
	rol.w	#8,%d6
	lsl.w	#8,%d0
	
	move.b	(%a2)+,%d6
	move.b	(%a1)+,%d0
	
	lsl.l	%d5,%d0
	rol.l	%d5,%d6
	
	and.l	%d6,(%a3)
	or.l	%d0,(%a3)
	
	addq.l	#2,%a3
	dbf	%d4,1b
	
	lea	30(%a0),%a0
	dbf	%d2,0b

	movem.l	(%sp)+,%d3-%d6/%a2-%a3
	rts
