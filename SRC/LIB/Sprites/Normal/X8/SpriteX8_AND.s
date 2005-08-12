| C prototype: void SpriteX8_AND(short x,short y,short h,unsigned char *sprt,short w,void *dest) __attribute__((__stkparm__));
| see SpriteX8_OR_R for comments

.data
.globl SpriteX8_AND
.even 

SpriteX8_AND:
	movem.l	%d3-%d5/%a2,-(%sp)

	lea     16+4(%sp),%a0
	move.w  (%a0)+,%d0
	move.w  (%a0)+,%d1
	move.w  (%a0)+,%d2
	move.l  (%a0)+,%a1
	move.w  (%a0)+,%d3
	move.l  (%a0)+,%a0
	
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
	
	lea     r+3(%pc),%a2
| Test: width odd ?
	btst.b  #0,%d3
	beq.s   w
	moveq   #E0-(r+2),%d1
	bra.s   p
w:
	moveq   #O0-(r+2),%d1

p:
	move.b  %d1,(%a2)

	move.w	%d5,%d1
	addq.w	#8,%d1
	
| Test: width odd ?
	btst.b  #0,%d3
	beq.s   O0
	
E0:
 	movea.l	%a0,%a2
 	move.w	%d3,%d4	
 	
E1:
 	
 	moveq.l	#-1,%d0	
 	move.w	(%a1)+,%d0
	dbf	%d4,E2

	move.b	#-1,%d0	
	rol.l	%d5,%d0
	and.l	%d0,(%a2)
	subq.l	#1,%a1
	lea	30(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d5/%a2
 	rts
 
E2:
 	rol.l	%d5,%d0	
 	and.l	%d0,(%a2)
 	addq.l	#2,%a2
	dbf	%d4,E1

	lea	30(%a0),%a0
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts

O0:
 	movea.l	%a0,%a2
	move.w	%d3,%d4

O1:
	moveq.l	#-1,%d0
	move.b	(%a1)+,%d0
	dbf	%d4,O2
	
	rol.l	%d1,%d0
	and.l	%d0,(%a2)
	lea	30(%a0),%a0
r:
	dbf	%d2,E0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts
	
O2:
	move.b  %d0,-(%sp)
	move.w  (%sp)+,%d0
|	rol.w	#8,%d0
	move.b	(%a1)+,%d0
	rol.l	%d5,%d0
	and.l	%d0,(%a2)
	addq.l	#2,%a2
	dbf	%d4,O1
	
	lea	30(%a0),%a0
	dbf	%d2,O0

	movem.l	(%sp)+,%d3-%d5/%a2
	rts
