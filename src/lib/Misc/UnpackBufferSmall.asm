;-----------------------------------------------------------------------
;INTRODUCTION:
;
;   This is a 100% assembly version of the ttunpack routine, which is
;   based on code by Pasi 'Albert' Ojala, albert@cs.tut.fi, then
;   reduced by Thomas Nussbaumer to fit his needs.  For a full details
;   on the algorithm see:
;
;	  http://www.cs.tut.fi/~albert/Dev/pucrunch/index.html
;
;   Version: 2.30 Super Small
;			Fixed a bug in header error checks
;
;  Copyright (C) 2004 Samuel Stearley
;
;THE LICENSE:
;
;		wxWindows Library Licence, Version 3.1
;                ======================================
;
;  Copyright (C) 1998-2005 Julian Smart, Robert Roebling et al
;
;  Everyone is permitted to copy and distribute verbatim copies
;  of this licence document, but changing it is not allowed.
;
;  
;  This library is free software; you can redistribute it and/or modify it
;  under the terms of the GNU Library General Public Licence as published by
;  the Free Software Foundation; either version 2 of the Licence, or (at
;  your option) any later version.
;  
;  This library is distributed in the hope that it will be useful, but
;  WITHOUT ANY WARRANTY; without even the implied warranty of
;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library
;  General Public Licence for more details.
;
;  You should have received a copy of the GNU Library General Public Licence
;  along with this software, usually in a file named COPYING.LIB.  If not,
;  write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
;  Boston, MA 02111-1307 USA.
;
;  EXCEPTION NOTICE
;
;  1. As a special exception, the copyright holders of this library give
;  permission for additional uses of the text contained in this release of
;  the library as licenced under the wxWindows Library Licence, applying
;  either version 3.1 of the Licence, or (at your option) any later version of
;  the Licence as published by the copyright holders of version
;  3.1 of the Licence document.
;
;  2. The exception is that you may use, copy, link, modify and distribute
;  under your own terms, binary object code versions of works based
;  on the Library.
;
;  3. If you copy code from files distributed under the terms of the GNU
;  General Public Licence or the GNU Library General Public Licence into a
;  copy of this library, as this licence permits, the exception does not
;  apply to the code that you add in this way.  To avoid misleading anyone as
;  to the status of such modified files, you must delete this exception
;  notice from such code and/or adjust the licensing conditions notice
;  accordingly.
;
;  4. If you write modifications of your own for this library, it is your
;  choice whether to permit this exception to apply to your modifications. 
;  If you do not wish that, you must delete the exception notice from such
;  code and/or adjust the licensing conditions notice accordingly.
;
;NOTES:
;
;1) There were several other names associated with this, but not
;   anymore ;)
;
;
;2) The code was written with wordpad.  It might look better if
;   opened with that program.
;
;
;3) A version of this is included as a hex array for use with programs
;   written with tigcc.  OR you can use this file directly with a
;   tigcc project: add it to the project and remove the ';' from
;   before the 'CALL_DIRECTLY' below.  Be sure to have the latest
;   version of tigcc when doing this.
;----------------------------------------------------------------------

CALL_DIRECTLY			;if this label is defined then this code can be used
					;  directly as part of a tigcc project.


DELTA_LZ				;If defined it will include code to do DELTA lz decompression
					;  ebooks and ppg compressed programs currently do not take advantage of
					;  the -fdelta option of the compressor.
					;removing this saves 24 bytes.


 ifd CALL_DIRECTLY
	public UnpackBufferSmall
 endc

 ifnd CALL_DIRECTLY
	include "os.h"
	xdef _ti89
	xdef _nostub
 endc


;------------------------------------------------------------------
;The data structure defines and error return values
;------------------------------------------------------------------

osize_lo		equ	0	;original size lowbyte
osize_hi		equ	1	;original size highbyte
magic1		equ	2	;must be equal to UNPACK_MAGIC1
magic2		equ	3	;must be equal to UNPACK_MAGIC2
csize_lo		equ	4	;compressed size lowbyte
csize_hi		equ	5	;compressed size lowbyte
esc1			equ	6	;escape >> (8-escBits)
notused3		equ	7	;
notused4		equ	8	;
esc2			equ	9	;escBits
gamma1		equ	10	;maxGamma + 1
gamma2		equ	11	;(1<<maxGamma)
extralz		equ	12	;extraLZPosBits
notused1		equ	13	;
notused2		equ	14	;
rleentries		equ	15	;rleUsed

HEADER_SIZE		equ	16

__MAGIC_CHAR1	equ	$54
__MAGIC_CHAR2	equ	$50

__ERRPCK_OKAY		equ	0
__ERRPCK_NOESCFOUND	equ	8		;248
__ERRPCK_ESCBITS		equ	7		;249
__ERRPCK_MAXGAMMA		equ	6		;250
__ERRPCK_EXTRALZP		equ	5		;251
__ERRPCK_NOMAGIC		equ	4		;252
__ERRPCK_OUTBUFOVERRUN	equ	3		;253
__ERRPCK_LZPOSUNDERRUN	equ	2		;254

;-----------------------------------------------------------------------
;Notes on register useage, might be good Idea to print this.
;
;	a0 => NOT USED
;	a1 => points to the next byte of the compressed data.
;		updated when d7 overflows.
;	a2 => NOT USED
;	a3 => the bytecodevec table
;	a4 => NOT USED
;	a5 => the destination buffer
;	a6 => Used during error checking
;
;	d0 => trashing, output of __GetBits and __GetValue
;	d1 => trashing, input to __GetBits
;	d2 => trashing but only by the main routine, not the subroutines
;	d3 => trashing but only by the main routine, not the subroutines
;	d4 => # of escape bits
;	d5 => start escape
;	d6 => current byte of data.
;	d7 => which bit we are at in the compressed data.
;
;During the zip part of the code:
;	d2 must be lzpos variable
;	d3 must be lzlen variable
;
;during rle part:
;	d0 byte to repeat
;	d3 number of times to repeat it
;-----------------------------------------------------------------------
UnpackBufferSmall:

 ifnd CALL_DIRECTLY
	dc.b		"UNPACK_0"
 endc

	movem.l	d3-d7/a2-a6,-(a7)
	move.l	4+10*4(a7),a6
	move.l	8+10*4(a7),a5
;--------------------------------------------------------
;  startesc = cth->esc1;     //d5
;  bytecodevec = &src[15];   //a3
;  __imask__   = 0x80;	     //d7
;
;These are initialized here to insure that certain
;branches can use the short form.
;--------------------------------------------------------
	lea		15(a6),a3		;'bytecodevec'
	move.b	esc1(a6),d5		;'StartEsc'
	moveq		#-128,d7		;which bit i am at.
;-------------------------------------------------------------------------------------------------
;  if (cth->magic1 != __MAGIC_CHAR1 || cth->magic2 != __MAGIC_CHAR2) return __ERRPCK_NOMAGIC;
;  if (cth->gamma1 != 8 || cth->gamma2 != 128)                       return __ERRPCK_MAXGAMMA;
;  if ((escbits = cth->esc2) > 8)                                    return __ERRPCK_ESCBITS;
;  if ((extralzposbits = cth->extralz) > 4)                          return __ERRPCK_EXTRALZP;
;-------------------------------------------------------------------------------------------------
	moveq		#__ERRPCK_NOMAGIC,d0
	addq.l	#2,a6
	cmp.b		#__MAGIC_CHAR1,(a6)+
	bne.s		__ReturnError
	cmp.b		#__MAGIC_CHAR2,(a6)
	bne.s		__ReturnError

	moveq		#8,d1
	moveq		#__ERRPCK_ESCBITS,d0
	addq.l	#6,a6					;point to esc2
	move.b	(a6)+,d4				;get esc2 and point to gamma1
	cmp.b		d1,d4
	bhi.s		__ReturnError

	moveq		#__ERRPCK_MAXGAMMA,d0
	cmp.b		(a6)+,d1				;gamma1 == 8?
	bne.s		__ReturnError
	cmp.b		(a6)+,d7				;gamma2 == 128 ?
	bne.s		__ReturnError
;--------------------------------------------------------
;  __ibuffer__ = src + sizeof(__PACKHEADER) + cth->rleentries;  //a6
;--------------------------------------------------------
	move.b	(a3),d1			;d1 is already a long
	lea		1(a3,d1),a1
	move.b	(a1)+,d6


	moveq		#__ERRPCK_EXTRALZP,d0
	cmp.b		#5,(a6)
	bcs.s		__DecompressLoop		;jump into the loop
;---------------------------------------------------------
;And when all is done branch here
;  If success d0 will be zero
;---------------------------------------------------------
__ReturnError:
__WeAreDone:
	neg.b		d0				;turn the loaded values into the actual error code
	movem.l	(a7)+,d3-d7/a2-a6
	rts
;-----------------------------------------------------------------
;  newesc = __GetBits(escbits);
;  *outbuffer++ = (startesc<<escbits8) | __GetBits(escbits8);
;  startesc = newesc;
;  continue;
;-----------------------------------------------------------------
__NextBitIsClear_EscapeFromEscape:
	move.b	d4,d1			;get 'escbits'
	bsr.s		__GetBits		;d0 is 'newesc'
	exg		d0,d5			;'startesc' = 'newesc'; and d0 = OLD_startesc
;---------------------------------------------------------
;  *outbuffer++ = (sel<<escbits8) | __GetBits(escbits8);
;  continue;
;---------------------------------------------------------
__SelIsNOTStartEscape:
	moveq		#8,d1
	sub.b		d4,d1			;'escbits8'
	bsr.s		__GetBits_D0_IS_Loaded_For_Shifting
	move.b	d0,(a5)+
;---------------------------------------------------------
;The while(1) loop, just a label ;)
;---------------------------------------------------------
__DecompressLoop:

;---------------------------------------------------------
;  sel = (escbits) ? __GetBits(escbits) : startesc;
;  if (sel == startesc) {
;---------------------------------------------------------
	move.b	d4,d1			;test 'escBits'
	beq.s		__SelIsStartEscape
	bsr.s		__GetBits		;get the bits, input is in d1
	cmp.b		d5,d0			;did __getBits return 'startesc' into 'sel'?
	bne.s		__SelIsNOTStartEscape
;---------------------------------------------------------
;The following code is entered if sel = start escape
;but it does not actually use the sel variable
;
;  lzlen = __GetValue();
;  if (lzlen != 1) {
;---------------------------------------------------------
__SelIsStartEscape:
	bsr.s		__GetValue		;get a value for 'lzlen', d1 will be negative
	move.w	d0,d3			;save 'lzlen'
	subq.w	#1,d0			;does 'lzlen' == 1 ?
	beq.s		__RleDecoding
;---------------------------------------------------------
;Zip decoding
;
;  lzposhi = __GetValue() - 1;
;  if (lzposhi == 254) {
;---------------------------------------------------------

 ifnd DELTA_LZ
	bsr.s		__GetValue		;if it equals 254, then lzlen must be > 3 because
	addq.b	#1,d0			;  there is no other possiblity because Delta decompression
	beq.s		__WeAreDone		;  is not being used.  It the branch is not taken it
 endc						;  drops through to the __LzPosHi_IsNot254

 ifd DELTA_LZ
		bsr		__GetValue		;get 'lzposhi', dont subtract 1 yet
		addq.b	#1,d0			;does 'lzposhi' = 254, remember it has not yet subtracted 1
		bne.s		__LzPosHi_IsNot254
		subq.w	#4,d3			;is 'lzlen' greater than 3?
		bcs.s		__WeAreDone		;destination is above
	;---------------------------------------------------------
	;  add   = __Get8Bit();			//put into d2
	;  lzpos = __Get8Bit() ^ 0xff;	//put into d0
	;
	;the bit inverstion and the pointer subtraction will be
	;  combined
	;---------------------------------------------------------
		addq.w	#4,d3			;undo above subq.w
		bsr.s		__Get8Bit
		move.b	d0,d2
		bsr.s		__Get8Bit
__UseDeltaLzCode:
		not.b		d0
		neg.l		d0
	;---------------------------------------------------------
	;  for (i=0; i<=lzlen; i++) {
	;    *outbuffer = *(outbuffer - lzpos - 1) + add;
	;    outbuffer++;
	;  }
	;---------------------------------------------------------
__WriteDataLoop2:
		move.b	-1(a5,d0.l),(a5)
		add.b		d2,(a5)+
		dbra		d3,__WriteDataLoop2
__ContinueWithinRange:
		bra.s		__DecompressLoop	;continue
 endc

;----------------------------------------------------------------------------------------
;  if (extralzposbits) lzposhi = (lzposhi<<extralzposbits) | __GetBits(extralzposbits);
;  lzposlo = __Get8Bit() ^ 0xff;
;  lzpos   = COMBINE_LOWHIGH(lzposlo,lzposhi);
;
; d0= lzPosHi, d3.w = lzlen, d2.l =lzpos
;----------------------------------------------------------------------------------------
__LzPosHi_IsNot254:
	subq.b	#2,d0				;undo the addq.b #1
	move.b	-3(a3),d1			;get 'extralzposbits'
	bsr.s		__GetBits_D0_IS_Loaded_For_Shifting
__NextBitClear_DoZipAfterAll:			;to jump here be sure that d0.l = 0
	moveq		#7,d1
	bsr.s		__GetBits_D0_IS_Loaded_For_Shifting_D1_is_not_Variable
;-----------------------------------------------------------------------------------
;  for (i=0; i<=lzlen; i++) {
;    *outbuffer = *(outbuffer - lzpos - 1); //no 'add' variable
;    outbuffer++;
;  }
;
; d0.l must be lzpos
; d3.w must be lzlen
;------------------------------------------------------------------------------------
 ifd DELTA_LZ
	moveq		#0,d2				;'add' = 0;
	bra.s		__UseDeltaLzCode
 endc

 ifnd DELTA_LZ
	not.b		d0
	neg.l		d0
__WriteDataLoop:
	move.b	-1(a5,d0.l),(a5)+		;18 cycles
__UseZipCopyLoop:					;entrance for the rle code
	dbra		d3,__WriteDataLoop
	bra.s		__DecompressLoop		;continue
 endc

;-------------------------------------------------------------
;The subroutines are here for size:
;
;  __Get8Bits returns an 8 bit value in d0.l  It can be used
;  as an:
;	unsigned character
;	unsigned short
;	unsigned long
;
;  __GetValue returns an 8 bit value in d0.l  It can be used
;  as an:
;	unsigned character
;	unsigned short
;	unsigned long
;
;  __GetBits takes as its input d1.b, returns a value in d0.w
;  There is a limit on it being 16 bit output.  With the
;  upper bits being 0 so it can be used as an:
;	unsigned character, if 8 bits or less are requested.
;	unsigned short
;	unsigned long
;
;  __GetBits has two other entrances, that assume a value in d0
;  is ready to be shifted up as bits are shifted in.  This is
;  limited to 16 bit values, with no guarantee about the upper
;  bits.
;
;  '__GetBits_D0_IS_Loaded_For_Shifting_D1_is_not_Variable' is
;  used when there is no possiblity that the input is 0.  For
;  example: __getBits(3)
;
;
; They will update d6, d7, a6
;
; They may not destroy
;	d3-d5/a0-a5
;
;--------------------------------------------------------------
 ifd DELTA_LZ
__Get8Bit:
	moveq		#8,d1
 endc

__GetBits:
	moveq		#0,d0
	bra.s		__IntoLoop
__GetBits_D0_IS_Loaded_For_Shifting_D1_is_not_Variable:
__inl_loop0:
__CheckBitProceed:			;to call this like the old 'CheckBitProceed' make sure d1 = negative
	add.b		d6,d6
	addx.w	d0,d0
	ror.b		#1,d7
	bcc.s		__NotInNext
	move.b	(a1)+,d6
__NotInNext:
__GetBits_D0_IS_Loaded_For_Shifting:
__IntoLoop:
	subq.b	#1,d1			;must be byte valued, if d1.b = negative then drop through
	bpl.s		__inl_loop0
	move		d0,ccr
	rts

__GetValue:
	moveq		#6,d2
	moveq		#-1,d1
__inl_loop1:
	bsr.s		__CheckBitProceed
	dbcc		d2,__inl_loop1
	moveq		#6,d1
	sub.w		d2,d1
	moveq		#1,d0
	bra.s		__GetBits_D0_IS_Loaded_For_Shifting
;---------------------------------------------------------
;RLE decoding
;---------------------------------------------------------
__RleDecoding:						;important! at this point d0=0 and d1 = -1
	bsr.s		__CheckBitProceed			;will modify d0 if the bit is set
	bcc.s		__NextBitClear_DoZipAfterAll	;if it branches d0 is still 0, the destination requires this!
	bsr.s		__CheckBitProceed
	bcc		__NextBitIsClear_EscapeFromEscape
;-----------------------------------------------------------------
;  rlelen = __GetValue();
;  if (rlelen >= 128) {
;     rlelen = ((rlelen-128)<<1) | __GetBits(1);
;     rlelen |= (((__GetValue())-1)<<8);
;  }
;------------------------------------------------------------------
__NextBitIsSet_RunLengthEncoding:
	bsr.s		__GetValue		;get 'rlelen' into d0, limited to 8 bit values. d1 =negative
	move.b	d0,d3			;copy it and check sign bit to see if >= 128
	bpl.s		__LessThan128
	bsr.s		__CheckBitProceed	;__getBits(1)
	move.w	d0,-(a7)
	bsr.s		__GetValue
	subq.b	#1,d0
	move.b	d0,(a7)		;overwrites the high bit that is should be cleared by
	move.w	(a7)+,d3		;  by the rlelen-128
;-------------------------------------------------------------------
;Need the byte to copy
;
;  bytecode = __GetValue();
;  if (bytecode < 32) byte = bytecodevec[bytecode];
;  else               byte = ((bytecode-32)<<3) | __GetBits(3);
;-------------------------------------------------------------------
__LessThan128:
	bsr.s		__GetValue			;get 'bytecode'
	cmp.b		#32,d0
	bcc.s		__GreaterThanOrEqual32
	move.b	0(a3,d0.w),d0		;byte = bytecodevec[bytecode];
	bra.s		__RleCopy
__GreaterThanOrEqual32:
	moveq		#2,d1
	bsr.s		__GetBits_D0_IS_Loaded_For_Shifting_D1_is_not_Variable
;--------------------------------------------------------
;  for (i=0; i<=rlelen; i++) *outbuffer++ = byte;
;  continue;   // continue the main loop ...
;
;Rle loop expects
; d0 = byte
; d3 = number of em to copy, no need to subtract 1 for
;	 dbra
;--------------------------------------------------------
__RleCopy:

 ifnd DELTA_LZ
	move.b	d0,(a5)+
	moveq		#0,d0
	bra.s		__UseZipCopyLoop
 endc

 ifd DELTA_LZ
__RleCopyLoop:
	move.b	d0,(a5)+
	dbra		d3,__RleCopyLoop
	bra.s		__ContinueWithinRange
 endc

;------------------------------------------------
;This routine has two outputs:
;1) d0.w is shifted up and the next bit is
;   shifted in: ie it is __getBits(1)
;
;2) The carry flag will be loaded with the state
;   of the bit.  If this is all that is needed
;   don't forget that it will modify d0.
;
;3) a6, d7, and d6 are advanced to the next bit.
;
;4+4+8+(10 or 16)+12+16= 54 or 60
;-------------------------------------------------
;__CheckBitProceed:
;	add.b		d6,d6
;	addx.w	d0,d0
;	ror.b		#1,d7
;	bcc.s		__NotInNext
;	move.b	(a1)+,d6
;__NotInNext:
;	move.b	d0,ccr		;sets or clears the carry flag
;	rts					;return


 ifnd CALL_DIRECTLY
	dc.b		"UNPACK_1"
 endc
