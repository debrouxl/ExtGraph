/******************************************************************************
*
* E X T G R A P H    v 2 . 0 0    Beta  5
* Copyright © 2001-2004 TICT (TI-Chess Team)
*
*******************************************************************************
*
* ExtGraph is a compile-time library which contains speed-optimized graphics
* routines for the TIGCC cross-compiler for TI-89, TI-89T, TI-92+ and TI-V200
* (TI-68k calculators).
*
* NOTE: using ExtGraph 2.xx requires TIGCC 0.95 and newer (I'm nearly always
* using the latest version myself).
* ExtGraph (extgraph.h + tilemap.h + preshift.h + extgraph.a + tilemap.a) can
* be used as is; recompiling ExtGraph is therefore neither necessary nor
* recommended. Not to mention that it requires the Windows shell, and the GNU
* binutil m68k-coff-ar, which was removed from TIGCC a long time ago. The
* ExtGraph SVN repository contains PC/Win32 and PC/Linux m68k-coff-ar binaries.
* I can add binaries for other architectures, starting with MacOS X, if someone
* provides me them.
*
* Please use as few __stkparm__ functions as possible in your programs: most
* functions have __regparm__ versions (or a mix of __regparm__ and __stkparm__:
* excess parameters are passed on the stack), which are themselves smaller and
* faster, and lead to smaller and faster code !
*
*
* library maintained, improved and extended by:
*                    Thomas Nussbaumer  (thomas.nussbaumer@gmx.net)
*                    Lionel Debroux     (lionel_debroux@yahoo.fr)
*                    Julien Richard-Foy (julien.rf@wanadoo.fr)
*                    various contributors (Geoffrey Anneheim, etc.).
*
*
*******************************************************************************
* [internal version] $Id: extgraph.h,v 1.13 2002/05/22 09:19:20 tnussb Exp $
*******************************************************************************/

#if !defined(__EXTGRAPH__)
#define __EXTGRAPH__

#include <gray.h>   // necessary for GrayGetPlane() macros in the grayscale
                    // support routines !!
#include <stdlib.h> // min(a,b) macro.

//-----------------------------------------------------------------------------
// Reject TIGCC 0.94 and less, since the official release is now 0.95, and the
// previous ones are really outdated compared to it. TIGCC 0.93 won't handle
// calling conventions correctly, TIGCC 0.94 would make only small fusses.
// Warn about other compilers because ExtGraph was tested only under TIGCC
// until further notice.
//-----------------------------------------------------------------------------
#include <version.h>

#ifndef __TIGCC__
#warning This compiler is unknown to ExtGraph. Until further notice, ExtGraph was tested only under standards-compliant TIGCC. Other compilers may not support ExtGraph.
#endif

#if (defined(__TIGCC__)&&(__TIGCC__<1)&&(defined(__TIGCC_MINOR__)&&(__TIGCC_MINOR__<95)))
#error ExtGraph requires TIGCC 0.95 or later ! Update TIGCC.
#endif


//-----------------------------------------------------------------------------
// to embed the extgraph version as string into your program the extgraph
// library contains the following global string variable which SHOULD be used
// for this!
//
// the string looks like this: "ExtGraph vX.YY[ßn]" where X is the major version
// number and YY is the subversion number.
//
// EXTGRAPH_VERSION_PWDSTR looks like this: "powered by ExtGraph vX.YY[ßn]"
//-----------------------------------------------------------------------------
#define EXTGRAPH_VERSION_STR      __egvs__
#define EXTGRAPH_VERSION_PWDSTR   __egvpwds__
extern const char __egvs__[];
extern const char __egvpwds__[];


//-----------------------------------------------------------------------------
// global variables embedded in the library are used for the version numbers
// to guarantee that the version is reported correctly even if you use an
// outdated headerfile
//-----------------------------------------------------------------------------
#define EXTGRAPH_VERSION_MAIN    __egvmain__
#define EXTGRAPH_VERSION_SUB     __egvsub__
#define EXTGRAPH_VERSION_REV     __egvrev__
extern const short __egvmain__;
extern const short __egvsub__;
extern const short __egvrev__;


// macro which dereferences a pointer: DEREFSMALL(p,i) does the same as p[i], but in a faster and
// smaller way (doing the same thing using inline assembly saved ~100 bytes on internal - and buggy -
// version of tthdex). Credits go to Kevin Kofler for its generic definition and the &* trick.
// 2.00 Beta 5: added #define so as to minimize incompatibility chances with the (same) definition
// that should be added to TIGCC some day.
#ifndef __HAVE_DEREFSMALL
#define __HAVE_DEREFSMALL
#define DEREFSMALL(__p,__i) (*((typeof(&*(__p)))((unsigned char*)(__p)+(long)(short)((short)(__i)*sizeof(*(__p))))))
#endif

// macro which returns the absolute value of a given short.
#define EXT_SHORTABS(a)  ({register short __ta=(a); (__ta>=0) ? __ta : -__ta;})

// macro which returns the absolute value of a given long.
#define EXT_LONGABS(a)  ({register long __ta=(a); (__ta>=0) ? __ta : -__ta;})

// macro which exchanges the content of two variables using the ASM exg instruction
// 2.00 adds "a" to the constraints, since exg applies also to address registers.
// Before I rewrote TestCollide8/16 routines in ASM, this saved a number of bytes on them.
#define EXT_XCHG(a,b)    asm volatile ("exg %0,%1" : "=da" (a), "=da" (b) : "0" (a), "1" (b) : "cc")

// macro which returns the word swapped value (upper and lower word swapped) of the given long.
#define EXT_LONGSWAP(val) ({register unsigned long __tmp = val;asm volatile ("swap %0" : "=d" (__tmp) : "0" (__tmp));__tmp;})

// macro which checks two bounding rectangles starting at (x0/y0) and (x1/y1) for
// collision. w is the width in pixels and h the height of the two bounding rectangles.
#define BOUNDS_COLLIDE(x0,y0,x1,y1,w,h) \
   (((EXT_SHORTABS((x1)-(x0)))<(w))&&((EXT_SHORTABS((y1)-(y0)))<(h)))

// macro which checks two bounding rectangles starting at (x0/y0) and (x1/y1) for
// collision. w is the width in pixels and h0 and h1 the heights of the two bounding rectangles.
#define BOUNDS_COLLIDE2H(x0,y0,x1,y1,w,h0,h1) \
   (((EXT_SHORTABS((x1)-(x0)))<(w)) && ((EXT_SHORTABS((y1)-(y0)))<(min((h0),(h1)))))

// macro which checks two bounding rectangles starting at (x0/y0) and (x1/y1) for
// collision. w is the width in pixels and h0 and h1 the heights of the two bounding rectangles.
#define BOUNDS_COLLIDE2W(x0,y0,x1,y1,w0,w1,h) \
   (((EXT_SHORTABS((x1)-(x0)))<(min((w0),(w1)))) && ((EXT_SHORTABS((y1)-(y0)))<(h)))

// macro which checks two bounding rectangles starting at (x0/y0) and (x1/y1) for
// collision. w0 and w1 are the width in pixels and h0 and h1 the heights of the two bounding
// rectangles.
#define BOUNDS_COLLIDE2HW(x0,y0,x1,y1,w0,w1,h0,h1) \
   (((EXT_SHORTABS((x1)-(x0)))<(min((w0),(w1)))) && ((EXT_SHORTABS((y1)-(y0)))<(min((h0),(h1)))))

// handy aliases for standard tile sizes (8x8 / 16x16 / 32x32).
#define BOUNDS_COLLIDE8(x0,y0,x1,y1)  BOUNDS_COLLIDE(x0,y0,x1,y1,8,8)
#define BOUNDS_COLLIDE16(x0,y0,x1,y1) BOUNDS_COLLIDE(x0,y0,x1,y1,16,16)
#define BOUNDS_COLLIDE32(x0,y0,x1,y1) BOUNDS_COLLIDE(x0,y0,x1,y1,32,32)

// aliases for standard tile widths (8xh / 16xh / 32xh).
#define BOUNDS_COLLIDE82H(x0,y0,x1,y1,h0,h1)  BOUNDS_COLLIDE(x0,y0,x1,y1,8,h0,h1)
#define BOUNDS_COLLIDE162H(x0,y0,x1,y1,h0,h1) BOUNDS_COLLIDE(x0,y0,x1,y1,16,h0,h1)
#define BOUNDS_COLLIDE322H(x0,y0,x1,y1,h0,h1) BOUNDS_COLLIDE(x0,y0,x1,y1,32,h0,h1)


// checks for collision between 2 sprites of width 8.
// 2.00 Beta 5: added ...2h_R routine needed by TIGCC/TICT board user lachprog. This routine can
// handle two different sprite heights.
short TestCollide8(short x0,short y0,short x1,short y1,short height,const unsigned char* data0,const unsigned char* data1) __attribute__((__stkparm__));
short TestCollide8_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height,const unsigned char* data0 asm("%a0"),const unsigned char* data1 asm("%a1")) __attribute__((__stkparm__));
short TestCollide82h_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height0,short height1,unsigned char* data0 asm("%a0"),unsigned char* data1 asm("%a1")) __attribute__((__stkparm__));

// checks for collision between 2 sprites of width 16.
// 2.00 Beta 5: added ...2h_R routine needed by TIGCC/TICT board user lachprog. This routine can
// handle two different sprite heights.
short TestCollide16(short x0,short y0,short x1,short y1,short height,const unsigned short* data0, const unsigned short* data1) __attribute__((__stkparm__));
short TestCollide16_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height,const unsigned short* data0 asm("%a0"),const unsigned short* data1 asm("%a1")) __attribute__((__stkparm__));
short TestCollide162h_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height0,short height1,unsigned short* data0 asm("%a0"),unsigned short* data1 asm("%a1")) __attribute__((__stkparm__));

// checks for collision between 2 sprites of width 32. This routine can handle two different
// sprite heights.
// Courtesy of Joey Adams, added in 2.00 Beta 5.
short TestCollide322h_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height0,short height1,const unsigned long *data0 asm("%a0"),const unsigned long *data1 asm("%a1")) __attribute__((__stkparm__));

// checks for collision between 2 sprites whose width is a multiple of 8.
// This routine can handle two different sprite heights AND widths.
// Courtesy of Joey Adams, added in 2.00 Beta 5.
short TestCollideX82w2h_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1,short bytewidth0,short bytewidth1,short height0,short height1,const void *data0 asm("%a0"),const void *data1 asm("%a1")) __attribute__((__stkparm__));

// checks for collision between pixel at (x0, y0) and sprite of given height at (x1, y1).
// Added in 2.00 Beta 5. Original PixCollide8_R by Joey Adams, Samuel Stearley, Jesse
// Frey worked on them. Modified and extended by Lionel Debroux, fixed by Jesse Frey.
char PixCollide8_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height asm("%a1"),unsigned char *sprite asm("%a0")) __attribute__((__regparm__(6)));
char PixCollide16_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height asm("%a1"),unsigned short *sprite asm("%a0")) __attribute__((__regparm__(6)));
char PixCollide32_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),short height asm("%a1"),unsigned long *sprite asm("%a0")) __attribute__((__regparm__(6)));
char PixCollideX8_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),register short bytewidth asm("%d4"),short height asm("%a1"),unsigned char *sprite asm("%a0")) __attribute__((__regparm__));
char PixCollideX16_R(short x0 asm("%d0"),short y0 asm("%d1"),short x1 asm("%d2"),short y1 asm("%d3"),register short wordwidth asm("%d4"),short height asm("%a1"),unsigned short *sprite asm("%a0")) __attribute__((__regparm__));

//-----------------------------------------------------------------------------
// enums used by some extgraph functions
// 2.00 changes the values in enum GrayColors for more optimized routines.
// 2.00 Beta 5 adds the COLOR_LGRAY and COLOR_DGRAY aliases.
//-----------------------------------------------------------------------------
enum GrayColors {COLOR_WHITE=0,COLOR_LIGHTGRAY=1,COLOR_LGRAY=1,COLOR_DARKGRAY=2,COLOR_DGRAY=2,COLOR_BLACK=3};
enum FillAttrs  {RECT_EMPTY=0,RECT_FILLED=1};
enum ExtAttrs   {A_CENTERED=0x40,A_SHADOWED=0x80};


//-----------------------------------------------------------------------------
// fast pixel access macros
// They were coded and most of all fixed numerous times by Julien Richard-Foy,
// Kevin Kofler, Lionel Debroux, Sebastian Reichelt.
// 2.00 introduces new macros in order to have GCC 3.x generate better code.
// GCC 4.x seems to do better with the old macros, but we will keep the old
// ones, which work starting from 2.00 Beta 5 (at last), until we know GCC
// can do as well on its own with the old macros as it is forced to do by the
// new macros.
//-----------------------------------------------------------------------------
#define EXT_PIXOFFSET(x,y) ((((y)<<4)-(y))*2+((x)>>3))
#define EXT_PIXADDR(p,x,y) (((char *)(p))+EXT_PIXOFFSET(x,y))
#define EXT_PIXMASK(x) (0x80>>((x)&7))
#define EXT_PIXNBIT(x) (~(x))


#define EXT_SETPIX_AM(a,m)   (*(a) |= (m))
#define EXT_CLRPIX_AM(a,m)   (*(a) &= ~(m))
#define EXT_XORPIX_AM(a,m)   (*(a) ^= (m))
#define EXT_GETPIX_AM(a,m)   (*(a) & (m))


#define EXT_PIXUP(a,m) ((unsigned char *)(a) -= 30)
#define EXT_PIXDOWN(a,m) ((unsigned char *)(a) += 30)
#define EXT_PIXLEFT_AM(a,m)   asm("rol.b  #1,%0;bcc.s  0f;subq.l #1,%1;0:"\
                                  : "=d" (m), "=g" (a) : "0" (m), "1" (a))
#define EXT_PIXRIGHT_AM(a,m)  asm("ror.b  #1,%0;bcc.s  0f;addq.l #1,%1;0:"\
                                  : "=d" (m), "=g" (a) : "0" (m), "1" (a))
#define EXT_PIXLEFT_AN(a,n)   asm("addq.w #1,%0;cmpi.b #7,%0;bhi.s 0f;moveq #0,%0;subq.l #1,%1;0:"\
                                  : "=d" (n), "=g" (a) : "0" (m), "1" (a))
#define EXT_PIXRIGHT_AN(a,n)  asm("subq.w #1,%0;blt.s  0f;moveq #7,%0;addq.l #1,%1;0:"\
                                  : "=d" (n), "=g" (a) : "0" (m), "1" (a))


// These macros are more optimized than EXT_..._AM ones, but less readable...
// Thanks a lot to Sebastian for giving me the solution to the trigraph
// problem, I couldn't think of escaping one of the offending question marks !
#define EXT_SETPIX_AN(a,offset,n) ({if(__builtin_constant_p(offset)) \
	{	\
		if(__builtin_constant_p(a))	\
			asm("bset.b %0,%c1" : : "di" (n), "dai" ((offset)+(unsigned char*)(a)));	\
		else	\
			if (offset !=0) \
				asm("bset.b %0,%c1(%2)" : : "di,di" (n), "i,\?\?\?\?!g" (offset), "a,a" (a));	\
			else \
				asm("bset.b %0,(%1)" : : "di" (n), "a" (a));	\
	}	\
	else	\
		asm("bset.b %0,0(%2,%1.w)" : : "di" (n), "da" (offset), "a" (a));	\
	})

#define EXT_CLRPIX_AN(a,offset,n) ({if(__builtin_constant_p(offset)) \
	{	\
		if(__builtin_constant_p(a))	\
			asm("bclr.b %0,%c1" : : "di" (n), "dai" ((offset)+(unsigned char*)(a)));	\
		else	\
			if (offset !=0) \
				asm("bclr.b %0,%c1(%2)" : : "di,di" (n), "i,\?\?\?\?!g" (offset), "a,a" (a));	\
			else \
				asm("bclr.b %0,(%1)" : : "di" (n), "a" (a));	\
	}	\
	else	\
		asm("bclr.b %0,0(%2,%1.w)" : : "di" (n), "da" (offset), "a" (a));	\
	})

#define EXT_XORPIX_AN(a,offset,n) ({if(__builtin_constant_p(offset)) \
	{ \
		if(__builtin_constant_p(a)) \
			asm("bchg.b %0,%c1" : : "di" (n), "dai" ((offset)+(unsigned char*)(a))); \
		else \
			if (offset !=0) \
				asm("bchg.b %0,%c1(%2)" : : "di,di" (n), "i,\?\?\?\?!g" (offset), "a,a" (a)); \
			else \
				asm("bchg.b %0,(%1)" : : "di" (n), "a" (a)); \
	} \
	else \
		asm("bchg.b %0,0(%2,%1.w)" : : "di" (n), "da" (offset), "a" (a)); \
	})


#define EXT_GETPIX_AN(a,offset,n) ({char __result; if(__builtin_constant_p(offset)) \
	{ \
		if(__builtin_constant_p(a)) \
			asm("btst.b %1,%c2; sne.b %0" : "=d" (__result) : "di" (n), "dai" ((offset)+(unsigned char*)(a))); \
		else \
			if (offset !=0) \
				asm("btst.b %1,%c2(%3); sne.b %0" : "=d,d" (__result) : "di,di" (n), "i,\?\?\?\?!g" (offset), "a,a" (a)); \
			else \
				asm("btst.b %1,(%2); sne.b %0" : "=d" (__result) : "di" (n), "a" (a)); \
	} \
	else \
		asm("btst.b %1,0(%3,%2.w); sne.b %0" : "=d" (__result) : "di" (n), "da" (offset), "a" (a)); \
	__result;})


#define EXT_SETPIX(p,x,y) EXT_SETPIX_AN(p,EXT_PIXOFFSET(x,y),~(x))
#define EXT_CLRPIX(p,x,y) EXT_CLRPIX_AN(p,EXT_PIXOFFSET(x,y),~(x))
#define EXT_XORPIX(p,x,y) EXT_XORPIX_AN(p,EXT_PIXOFFSET(x,y),~(x))
#define EXT_GETPIX(p,x,y) EXT_GETPIX_AN(p,EXT_PIXOFFSET(x,y),~(x))



//-----------------------------------------------------------------------------
// Given buffer variants of grayscale support routines
// NOTE: these functions modify the active plane using PortSet() !
// 2.00 introduces new names, more compliant with the new names in TIGCCLIB.
//-----------------------------------------------------------------------------
void GrayClearScreen2B(void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayClearScreen2B_R(void* lightplane asm("%a0"),void* darkplane asm("%a1")) __attribute__((__regparm__(2)));
void GrayFillScreen2B_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),unsigned long lcolor asm("%d0"),unsigned long dcolor asm("%d1")) __attribute__((__regparm__(4)));
void GrayDrawRect2B(short x0,short y0,short x1, short y1, short color,short fill,void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayInvertRect2B(short x0,short y0,short x1, short y1,void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayDrawLine2B(short x0,short y0,short x1, short y1, short color,void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayFastDrawLine2B(short x0,short y0,short x1, short y1, short color,void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayFastDrawHLine2B(short x0,short x1, short y, short color,void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayDrawChar2B(short x,short y,char c,short attr,void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayDrawStr2B(short x,short y,const char* s,short attr,void* lightplane,void* darkplane) __attribute__((__stkparm__));
void GrayDrawStrExt2B(short x,short y,const char* s,short attr,short font,void* lightplane,void* darkplane) __attribute__((__stkparm__));

// Deprecated names...
#define ClearGrayScreen2B GrayClearScreen2B
#define ClearGrayScreen2B_R GrayClearScreen2B_R
#define DrawGrayRect2B GrayDrawRect2B
#define InvertGrayRect2B GrayInvertRect2B
#define DrawGrayLine2B GrayDrawLine2B
#define FastDrawGrayLine2B GrayFastDrawLine2B
#define FastDrawGrayHLine2B GrayFastDrawHLine2B
#define DrawGrayChar2B GrayDrawChar2B
#define DrawGrayStr2B GrayDrawStr2B
#define DrawGrayStrExt2B GrayDrawStrExt2B



//-----------------------------------------------------------------------------
// Helper macros for functions from grayutil.h.
// NOTE: graph functions modify active plane with PortSet() !!
// 2.00 introduces new names, more compliant with the new names in TIGCCLIB.
//-----------------------------------------------------------------------------
#define GrayClearScreen()                    GrayClearScreen2B(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayClearScreen_R()                  GrayClearScreen2B_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayFillScreen_R(l,d)                GrayFillScreen2B_R(GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE),l,d)
#define GrayDrawRect(x0,y0,x1,y1,color,fill) GrayDrawRect2B(x0,y0,x1,y1,color,fill,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayInvertRect(x0,y0,x1,y1)          GrayInvertRect2B(x0,y0,x1,y1,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayDrawLine(x0,y0,x1,y1,color)      GrayDrawLine2B(x0,y0,x1,y1,color,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayFastDrawHLine(x0,x1,y,color)     GrayFastDrawHLine2B(x0,x1,y,color,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayFastDrawLine(x0,y0,x1,y1,color)  GrayFastDrawLine2B(x0,y0,x1,y1,color,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayDrawChar(x,y,c,attr)             GrayDrawChar2B(x,y,c,attr,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayDrawStr(x,y,s,attr)              GrayDrawStr2B(x,y,s,attr,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))
#define GrayDrawStrExt(x,y,s,attr,font)      GrayDrawStrExt2B(x,y,s,attr,font,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE))

// Deprecated names...
#define ClearGrayScreen GrayClearScreen
#define ClearGrayScreen_R GrayClearScreen_R
#define DrawGrayRect GrayDrawRect
#define InvertGrayRect GrayInvertRect
#define DrawGrayLine GrayDrawLine
#define FastDrawGrayHLine GrayFastDrawHLine
#define FastDrawGrayLine GrayFastDrawLine
#define DrawGrayChar GrayDrawChar
#define DrawGrayStr GrayDrawStr
#define DrawGrayStrExt GrayDrawStrExt



//-----------------------------------------------------------------------------
// screen scrolling routines
//-----------------------------------------------------------------------------
void ScrollLeft160(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));
void ScrollLeft240(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));
void ScrollRight160(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));
void ScrollRight240(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));
void ScrollUp160(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));
void ScrollUp240(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));
void ScrollDown160(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));
void ScrollDown240(unsigned short* buffer,unsigned short lines) __attribute__((__stkparm__));

void ScrollLeft160_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));
void ScrollLeft240_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));
void ScrollRight160_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));
void ScrollRight240_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));
void ScrollUp160_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));
void ScrollUp240_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));
void ScrollDown160_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));
void ScrollDown240_R(unsigned short* buffer asm("%a0"),unsigned short lines asm("%d0")) __attribute__((__regparm__(2)));



//-----------------------------------------------------------------------------
// fast alternative functions for line drawing.
// FastDrawLine(_R) rewritten by ExtendeD and optimized a bit by Lionel. Added
// GrayFastDrawLine(_R) in 2.00 Beta 5.
// FastLine_... written by jackiechan.
// FastTestLine_... modified from FastLine_Invert_R: BE checks both ends at
// the same time, LE starts from the left end, RE from the right end. Added in
// 2.00 Beta 5.
// ClipLine, (Gray)ClipDrawLine" (ClipLine + callback to a
// (Gray)Fast*_R-compatible line function) added in 2.00 Beta 5 too. Upon exit,
// a0 = NULL if there's nothing to draw.
//-----------------------------------------------------------------------------
void FastDrawLine(void* plane,short x1,short y1,short x2,short y2,short mode) __attribute__((__stkparm__));
void FastDrawLine_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short mode) __attribute__((__stkparm__));
void GrayFastDrawLine2B_R(void* plane0 asm("%a0"),void *plane1 asm("%a1"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short color) __attribute__((__stkparm__));

void FastDrawHLine(void* plane,short x1,short x2,short y,short mode) __attribute__((__stkparm__));
void FastDrawHLine_R(void* plane asm("a0"), short x1 asm("d0"), short x2 asm("d1"), short y asm("d2"),short mode) __attribute__((__stkparm__));
void GrayFastDrawHLine2B_R(void *plane0 asm("%a0"),void *plane1 asm("%a1"),short x0 asm("%d0"),short x1 asm("%d1"),short y asm("%d2"),short color asm("%d3"));

void FastDrawVLine(void* plane,short x,short y1,short y2,short mode) __attribute__((__stkparm__));
void FastDrawVLine_R(void* plane asm("%a0"),short x asm("%d0"),short y1 asm("%d1"),short y2 asm("%d2"),short mode) __attribute__((__stkparm__));

void FastLine_Draw_R(void *plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__));
void FastLine_Erase_R(void *plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__));
void FastLine_Invert_R(void *plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__));

char FastTestLine_BE_R(void *plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__));
char FastTestLine_LE_R(void *plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__));
char FastTestLine_RE_R(void *plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__));

void * ClipLine_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short *clippedcoord asm("%a1")) __attribute__((__regparm__));
// In assembly, you can use _ClipLine_R, which returns the clipped coordinates in d0-d3 and the result (NULL if nothing to draw) in a0.
void ClipDrawLine_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short *clippedcoord asm("%a1"),short mode,void *plane asm("%a0"), void (__attribute__((__stkparm__)) *)(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short mode)) __attribute__((__stkparm__));
void GrayClipDrawLine_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short *clippedcoord asm("%a1"),short color,void *plane0,void *plane,void (__attribute__((__stkparm__)) *)(void* plane0 asm("%a0"),void *plane1 asm("%a1"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short color)) __attribute__((__stkparm__));



//-----------------------------------------------------------------------------
// Functions for rectangle drawing. Much faster than the AMS routines.
//-----------------------------------------------------------------------------
void FastFillRect(void* plane,short x1,short y1,short x2,short y2,short mode) __attribute__((__stkparm__));
void FastFillRect_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short mode) __attribute__((__stkparm__));
void GrayFastFillRect_R(void* dest0 asm("%a0"),void* dest1 asm("%a1"), short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short color) __attribute__((__stkparm__));

void FastOutlineRect(void* plane,short x1,short y1,short x2,short y2,short mode) __attribute__((__stkparm__));
void FastOutlineRect_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short mode) __attribute__((__stkparm__));
void GrayFastOutlineRect_R(void* dest0 asm("%a0"),void* dest1 asm("%a1"), short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short color) __attribute__((__stkparm__));

void FastEraseRect160_R(void* plane asm("%a0"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
void FastEraseRect240_R(void* plane asm("%a0"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
void GrayFastEraseRect2B160_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
void GrayFastEraseRect2B240_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
void FastFillRect160_R(void* plane asm("%a0"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
void FastFillRect240_R(void* plane asm("%a0"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
void GrayFastFillRect2B160_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
void GrayFastFillRect2B240_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
void FastInvertRect160_R(void* plane asm("%a0"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
void FastInvertRect240_R(void* plane asm("%a0"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(3)));
void GrayFastInvertRect2B160_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));
void GrayFastInvertRect2B240_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short starty asm("%d0"), unsigned short lines asm("%d1")) __attribute__((__regparm__(4)));

void FastEraseRectX8_R(void* plane asm("%a0"),short startcol asm("%d0"),short startrow asm("%d1"),unsigned short nrlines asm("%d2"),unsigned short bytewidth asm("%d3")) __attribute__((__regparm__(5)));
void FastFillRectX8_R(void* plane asm("%a0"),short startcol asm("%d0"),short startrow asm("%d1"),unsigned short nrlines asm("%d2"),unsigned short bytewidth asm("%d3")) __attribute__((__regparm__(5)));
void FastInvertRectX8_R(void* plane asm("%a0"),short startcol asm("%d0"),short startrow asm("%d1"),unsigned short nrlines asm("%d2"),unsigned short bytewidth asm("%d3")) __attribute__((__regparm__(5)));

void FastFilledRect_Draw_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__(5)));
void FastFilledRect_Erase_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__(5)));
void FastFilledRect_Invert_R(void* plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__(5)));



//-----------------------------------------------------------------------------
// Functions for circle drawing. Much faster than the AMS routine, which
// support multiple drawing modes and can draw ellipses, but are rarely used
// to draw ellipses in games. Any bench between DrawClipEllipse and these
// routines is unfair, though.
//--------------------------------** WARNING **--------------------------------
// GrayClipFastOutlined/FilledCircle_R and all GrayDrawSpan (see below)
// require consecutive grayscale planes (see the root of the ExtGraph
// documentation, paragraph about the tilemap engine, for more information)
// so as not to use too many registers, which makes the used algorithm less
// efficient.
// NOT PROVIDING THEM SUCH PLANES IS LIKELY TO CRASH HW1 CALCULATORS.
//--------------------------------** WARNING **--------------------------------
// Most routines added in 2.00 Beta 5.
//-----------------------------------------------------------------------------
void FastOutlinedCircle_DRAW_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"));
void FastOutlinedCircle_ERASE_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"));
void FastOutlinedCircle_INVERT_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"));
void ClipFastOutlinedCircle_DRAW_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"));
void ClipFastOutlinedCircle_ERASE_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"));
void ClipFastOutlinedCircle_INVERT_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"));

void ClipFastFilledCircle_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"),void * addr asm("%a0")) asm("%a2"));

void GrayClipFastOutlinedCircle_R(void *planes asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addrs asm("%a0")) asm("%a2"));
void GrayClipFastFilledCircle_R(void *planes asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),unsigned short radius asm("%d2"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addrs asm("%a0")) asm("%a2"));



//-----------------------------------------------------------------------------
// Functions for filled triangle drawing and special line drawing functions
// fit for them. No equivalent in AMS. Added in 2.00 Beta 5.
// Can you figure the code of the outlined triangle drawing functions ? ;-)
//--------------------------------** WARNING **--------------------------------
// Gray(Clip)FilledTriangle_R and all GrayDrawSpan require consecutive grayscale
// planes (see the root of the ExtGraph documentation, paragraph about the
// tilemap engine, for more information) so as not to use too many registers,
// which makes the used algorithm less efficient.
// NOT PROVIDING THEM SUCH PLANES IS LIKELY TO CRASH HW1 CALCULATORS.
//--------------------------------** WARNING **--------------------------------
// All DrawSpan are clipped.
// The difference between FilledTriangle_R and ClipFilledTriangle_R, and their
// grayscale versions, is currently only a shift count. Higher shift counts
// give better-looking triangles (smaller accumulated errors due to round-down
// when dividing), but they are more prone to numerical overflows, which mess
// up the entire triangle. Compare
// FilledTriangle_R(-50,0,300,49,159,99,LCD_MEM,DrawSpan_OR_R);
// and
// ClipFilledTriangle_R(-50,0,300,49,159,99,LCD_MEM,DrawSpan_OR_R);
// to see both problems.
// Does anyone have an algorithm which would be more or even slightly less
// efficient, and better-looking ?
//-----------------------------------------------------------------------------
void FilledTriangle_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short x3 asm("%d4"),short y3 asm("%a1"),void *plane asm("%a0"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addr asm("%a0")) asm("%a2"));
void ClipFilledTriangle_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short x3 asm("%d4"),short y3 asm("%a1"),void *plane asm("%a0"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addr asm("%a0")) asm("%a2"));
void DrawSpan_OR_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addr asm("%a0"));
void DrawSpan_XOR_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addr asm("%a0"));
void DrawSpan_REVERSE_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addr asm("%a0"));

void GrayFilledTriangle_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short x3 asm("%d4"),short y3 asm("%a1"),void *planes asm("%a0"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addrs asm("%a0")) asm("%a2"));
void GrayClipFilledTriangle_R(short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3"),short x3 asm("%d4"),short y3 asm("%a1"),void *planes asm("%a0"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addrs asm("%a0")) asm("%a2"));
void GrayDrawSpan_WHITE_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addrs asm("%a0"));
void GrayDrawSpan_LGRAY_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addrs asm("%a0"));
void GrayDrawSpan_DGRAY_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addrs asm("%a0"));
void GrayDrawSpan_BLACK_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addrs asm("%a0"));
void GrayDrawSpan_INVERT_R(short x1 asm("%d0"),short x2 asm("%d1"), void * addrs asm("%a0"));



//-----------------------------------------------------------------------------
// sprite scaling routines by Julien Richard-Foy (julien.rf@wanadoo.fr)
// "Legally" unencumbered; faster, smaller than the routines by Jim Haskell used
// prior to 2.00 Beta 5.
// The new routines could have been used for way longer if I (Lionel)
// had not messed up the coding of AND and XOR from that of OR, which
// made me put the routines aside as "algorithm good for OR but not for
// AND and XOR". When I had a fresh look at the routines, more than one year
// later, it took me several minutes to see and fix the mistake....
// Sorry again Julien...
//
// X8 version added in 2.00 Beta 5.
//
// scales a square input sprite to any extent (WARNING: no clipping is done!)
//
//
// Two scaling routines optimized for fixed size and scale factor,
// DoubleSpriteDimensions16x16_R is obviously designed for use in file explorers
// to read the AMS native comments available in TIGCC 0.95+ (well, hardly any
// does, starting with TICT-Explorer).
//-----------------------------------------------------------------------------
void ScaleSprite8_OR(const unsigned char *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite16_OR(const unsigned short *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite32_OR(const unsigned long *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite64_OR(const unsigned long long *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));

void ScaleSprite8_AND(const unsigned char *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite16_AND(const unsigned short *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite32_AND(const unsigned long *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite64_AND(const unsigned long long *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));

void ScaleSprite8_XOR(const unsigned char *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite16_XOR(const unsigned short *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite32_XOR(const unsigned long *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));
void ScaleSprite64_XOR(const unsigned long long *sprite,void *dest,short x0,short y0,short sizex,short sizey) __attribute__((__stkparm__));

void DoubleSpriteDimensionsX8_R(short h asm("%d0"),const unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned short* dest asm("%a1")) __attribute__((__regparm__(4)));
void DoubleSpriteDimensions16x16_R(const unsigned short* src asm("%a0"),unsigned long* dest asm("%a1")) __attribute__((__regparm__(2)));



//-----------------------------------------------------------------------------
// plane scaling routines by Geoffrey Anneheim (240 -> 160), "GoldenCrystal"
// (160 -> 240).
// Two-plane versions do not make sense to me:
// * they wouldn't be faster;
// * they wouldn't help the plane switching process, they could probably make
//   things worse.
// * they would require more memory, since the B/W ones can reuse an intermediate
//   buffer, but the two-plane ones cannot.
// [routines slightly modified to fit the needs, optimized for speed and/or size]
// Added in 2.00 beta 5.
//-----------------------------------------------------------------------------
void Scale1Plane240to160_R(void *src asm("%a0"),void *dest asm("%a1"));
void Scale1Plane160to240_R(void *src asm("%a0"),void *dest asm("%a1"));



//-----------------------------------------------------------------------------
// fast copy routine for a complete screen (240x128 pixels == 3840 bytes)
// Two-plane versions would have two of the same drawbacks as the two-plane
// versions of plane scaling routines (the last one does not apply to plane
// copy routines).
// 160to240(NC) added in 2.00 Beta 5, they copy a 160xheight screen
// (bytewidth = 20) to a 240x128 screen. NC stands for "Nearly Centered": the
// upper corner of the 160x100 screen is drawn at (32,14+(100-height)/2)
// instead of (40,14+(100-height)/2). This makes the copy process more efficient.
//-----------------------------------------------------------------------------
void FastCopyScreen(void* src,void* dest) __attribute__((__stkparm__));
void FastCopyScreen_R(void* src asm("%a0"),void* dest asm("%a1")) __attribute__((__regparm__(2)));
void FastCopyScreen160to240_R(short height asm("%d0"),void* src asm("%a0"),void* dest asm("%a1")) __attribute__((__regparm__(2)));
void FastCopyScreen160to240NC_R(short height asm("%d0"),void* src asm("%a0"),void* dest asm("%a1")) __attribute__((__regparm__(2)));




//-----------------------------------------------------------------------------
// floodfill routines (courtesy of Zeljko Juric)
//-----------------------------------------------------------------------------
void FloodFill(short x,short y,unsigned short shade,void* tmpplane,void* dest) __attribute__((__stkparm__));
void FloodFill_R(short x,short y,unsigned short shade,void* tmpplane,void* dest) __attribute__((__regparm__(5)));

void FloodFillMF(short x,short y,unsigned short shade,void* dest) __attribute__((__stkparm__));
void FloodFillMF_R(short x,short y,unsigned short shade,void* dest) __attribute__((__regparm__(4)));



//-----------------------------------------------------------------------------
// NON-CLIPPED SINGLE PLANE SPRITE FUNCTIONS
// Both __stkparm__ and __regparm__ functions are available.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// fast alternative functions for SpriteX() functions: AND, OR, XOR.
// fast additional sprite functions: BLIT, RPLC (BLIT with hard-coded white
// blitmask) MASK.
// fast alternative functions for BitmapGet() function (incompatible): Get.
//-----------------------------------------------------------------------------
void Sprite8_AND(short x,short y,short h,const unsigned char *sprt,void *dest) __attribute__((__stkparm__));
void Sprite8_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite8_BLIT(short x,short y,short h,const unsigned char *sprt,unsigned char maskval,void *dest) __attribute__((__stkparm__));
void Sprite8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),unsigned char maskval asm("%d3"),void *dest asm("%a0"));
void Sprite8Get(short x,short y,short h,void* src,unsigned char* dest) __attribute__((__stkparm__));
void Sprite8Get_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned char* dest asm("%a1")) __attribute__((__regparm__));
void Sprite8_MASK(short x,short y,short h,const unsigned char *sprt,const unsigned char *mask,void *dest) __attribute__((__stkparm__));
void Sprite8_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),const unsigned char *mask,void *dest asm("%a0")) __attribute__((__stkparm__));
void Sprite8_OR(short x,short y,short h,const unsigned char *sprt,void *dest) __attribute__((__stkparm__));
void Sprite8_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite8_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite8_XOR(short x,short y,short h,const unsigned char *sprt,void *dest) __attribute__((__stkparm__));
void Sprite8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));


void Sprite16_AND(short x,short y,short h,const unsigned short *sprt,void *dest) __attribute__((__stkparm__));
void Sprite16_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite16_BLIT(short x,short y,short h,const unsigned short *sprt,unsigned short maskval,void *dest) __attribute__((__stkparm__));
void Sprite16_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),unsigned short maskval asm("%d3"),void *dest asm("%a0"));
void Sprite16Get(short x,short y,short h,void* src,unsigned short* dest) __attribute__((__stkparm__));
void Sprite16Get_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned short* dest asm("%a1")) __attribute__((__regparm__));
void Sprite16_MASK(short x,short y,short h,const unsigned short *sprt,const unsigned short *mask,void *dest) __attribute__((__stkparm__));
void Sprite16_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),const unsigned short *mask,void *dest asm("%a0")) __attribute__((__stkparm__));
void Sprite16_OR(short x,short y,short h,const unsigned short *sprt,void *dest) __attribute__((__stkparm__));
void Sprite16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite16_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite16_XOR(short x,short y,short h,const unsigned short *sprt,void *dest) __attribute__((__stkparm__));
void Sprite16_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));


void Sprite32_AND(short x,short y,short h,const unsigned long *sprt,void *dest) __attribute__((__stkparm__));
void Sprite32_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite32_BLIT(short x,short y,short h,const unsigned long *sprt,unsigned long maskval,void *dest) __attribute__((__stkparm__));
void Sprite32_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),unsigned long maskval asm("%d3"),void *dest asm("%a0"));
void Sprite32Get(short x,short y,short h,void* src,unsigned long* dest) __attribute__((__stkparm__));
void Sprite32Get_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned long* dest asm("%a1")) __attribute__((__regparm__));
void Sprite32_MASK(short x,short y,short h,const unsigned long *sprt,const unsigned long *mask,void *dest) __attribute__((__stkparm__));
void Sprite32_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),const unsigned long *mask,void *dest asm("%a0")) __attribute__((__stkparm__));
void Sprite32_OR(short x,short y,short h,const unsigned long *sprt,void *dest) __attribute__((__stkparm__));
void Sprite32_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite32_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void Sprite32_XOR(short x,short y,short h,const unsigned long *sprt,void *dest) __attribute__((__stkparm__));
void Sprite32_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));


void SpriteX8_AND(short x,short y,short h,const unsigned char *sprt,short bytewidth,void *dest) __attribute__((__stkparm__));
void SpriteX8_AND_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__regparm__));
void SpriteX8_BLIT(short x,short y,short h,const unsigned char *sprt,const unsigned char *maskval,short bytewidth,void *dest) __attribute__((__stkparm__));
void SpriteX8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),const unsigned char *maskval,short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__stkparm__));
void SpriteX8Get(short x,short y,short h,void* src,unsigned char* dest,short bytewidth) __attribute__((__stkparm__));
void SpriteX8Get_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void *src asm("%a1"),unsigned char *dest asm("%a0"),short bytewidth asm("%d3")) __attribute__((__regparm__));
void SpriteX8_MASK(short x,short y,short h,const unsigned char *sprt,const unsigned char *mask,short bytewidth,void *dest) __attribute__((__stkparm__));
void SpriteX8_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),const unsigned char *mask,short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__stkparm__));
void SpriteX8_OR(short x,short y,short h,const unsigned char *sprt,short bytewidth,void *dest) __attribute__((__stkparm__));
void SpriteX8_OR_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__regparm__));
void SpriteX8_XOR(short x,short y,short h,const unsigned char *sprt,short bytewidth,void *dest) __attribute__((__stkparm__));
void SpriteX8_XOR_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__regparm__));


void SlowerSpriteX8_AND_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__regparm__));
void SlowerSpriteX8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),const unsigned char *maskval,short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__stkparm__));
void SlowerSpriteX8Get_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void *src asm("%a1"),unsigned char *dest asm("%a0"),short bytewidth asm("%d3")) __attribute__((__regparm__));
void SlowerSpriteX8_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),const unsigned char *mask,short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__stkparm__));
void SlowerSpriteX8_OR_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__regparm__));
void SlowerSpriteX8_XOR_R(short x asm("%d0"), short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),short bytewidth asm("%d3"),void *dest asm("%a0")) __attribute__((__regparm__));



//-----------------------------------------------------------------------------
// CLIPPED SINGLE PLANE SPRITE FUNCTIONS
// Only __regparm__ functions are available, __stkparm__ functions are NOT
// planned.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// fast alternative functions for SpriteX() functions: AND, OR, XOR.
// fast additional sprite functions: BLIT, RPLC (BLIT with hard-coded white
// blitmask) MASK.
//-----------------------------------------------------------------------------
void ClipSprite8_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),unsigned char maskval asm("%d3"),void *dest asm("%a0"));
void ClipSprite8_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),const unsigned char *mask,void *dest asm("%a0")) __attribute__((__stkparm__));
void ClipSprite8_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite8_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt asm("%a1"),void *dest asm("%a0"));


void ClipSprite16_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite16_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),unsigned short maskval asm("%d3"),void *dest asm("%a0"));
void ClipSprite16_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),const unsigned short *mask,void *dest asm("%a0")) __attribute__((__stkparm__));
void ClipSprite16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite16_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite16_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));


void ClipSprite32_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite32_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),unsigned long maskval asm("%d3"),void *dest asm("%a0"));
void ClipSprite32_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),const unsigned long *mask,void *dest asm("%a0")) __attribute__((__stkparm__));
void ClipSprite32_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite32_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0"));
void ClipSprite32_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt asm("%a1"),void *dest asm("%a0"));


void ClipSpriteX8_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d3"),short bytewidth asm("%d2"),unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void ClipSpriteX8_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d3"),short bytewidth asm("%d2"),unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));
void ClipSpriteX8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d3"),short bytewidth asm("%d2"),unsigned char *sprt asm("%a1"),void *dest asm("%a0")) __attribute__((__regparm__));



//-----------------------------------------------------------------------------
// NON-CLIPPED TWO-PLANE SPRITE FUNCTIONS
// Both __stkparm__ and __regparm__ functions are available.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// fast alternative functions for SpriteX() functions: AND, OR, XOR.
// fast additional sprite functions: BLIT, RPLC (BLIT with hard-coded white
// blitmask), MASK/SMASK, TRANB/TRANW (transparencies).
//-----------------------------------------------------------------------------
void GraySprite8_AND(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite8_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite8_BLIT(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,unsigned char maskval,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,unsigned char maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite8_MASK(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,const unsigned char* mask1,const unsigned char* mask2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite8_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,const unsigned char *mask0,const unsigned char *mask1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite8_OR(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite8_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite8_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite8_SMASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,const unsigned char *mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite8_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySprite8_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite8_XOR(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


void GraySprite16_AND(short x,short y,short h,const unsigned short* sprite1,const unsigned short* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite16_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite16_BLIT(short x,short y,short h,const unsigned short* sprite1,const unsigned short* sprite2,unsigned short maskval,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite16_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,unsigned short maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite16_MASK(short x,short y,short h,const unsigned short* sprite1,const unsigned short* sprite2,const unsigned short* mask1,const unsigned short* mask2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite16_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,const unsigned short *mask0,const unsigned short *mask1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite16_OR(short x,short y,short h,const unsigned short* sprite1,const unsigned short* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite16_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite16_SMASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,const unsigned short *mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite16_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySprite16_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite16_XOR(short x,short y,short h,const unsigned short* sprite1,const unsigned short* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite16_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


void GraySprite32_AND(short x,short y,short h,const unsigned long* sprite1,const unsigned long* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite32_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite32_BLIT(short x,short y,short h,const unsigned long* sprite1,const unsigned long* sprite2,unsigned long maskval,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite32_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,unsigned long maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite32_MASK(short x,short y,short h,const unsigned long* sprite1,const unsigned long* sprite2,const unsigned long* mask1,const unsigned long* mask2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite32_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,const unsigned long *mask0,const unsigned long *mask1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite32_OR(short x,short y,short h,const unsigned long* sprite1,const unsigned long* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite32_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite32_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite32_SMASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,const unsigned long *mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite32_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySprite32_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GraySprite32_XOR(short x,short y,short h,const unsigned long* sprite1,const unsigned long* sprite2,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySprite32_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


// Not currently rewritten, transparency routines and __regparm__ versions
// were not written either...
void GraySpriteX8_AND(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,short bytewidth,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySpriteX8_BLIT(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,const unsigned char* maskval,short bytewidth,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySpriteX8_MASK(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,const unsigned char* mask1,const unsigned char* mask2,short bytewidth,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySpriteX8_OR(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,short bytewidth,void* dest1,void* dest2) __attribute__((__stkparm__));
void GraySpriteX8_XOR(short x,short y,short h,const unsigned char* sprite1,const unsigned char* sprite2,short bytewidth,void* dest1,void* dest2) __attribute__((__stkparm__));


//-----------------------------------------------------------------------------
// CLIPPED TWO-PLANE SPRITE FUNCTIONS
// Only __regparm__ functions are available, __stkparm__ functions are NOT
// planned.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// fast alternative functions for SpriteX() functions: AND, OR, XOR.
// fast additional sprite functions: BLIT, RPLC (BLIT with hard-coded white
// blitmask), MASK, TRANB/TRANW (transparencies), SMASKBLIT.
// SMASKBLIT was made for "lachprog"'s Super Mario 3 68k.
//-----------------------------------------------------------------------------
void GrayClipSprite8_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,unsigned char maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,const unsigned char *mask0,const unsigned char *mask1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_SMASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,const unsigned char *mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


void GrayClipSprite16_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,unsigned short maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,const unsigned short *mask0,const unsigned short *mask1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_SMASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,const unsigned short *mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_SMASKBLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned short *sprt0,unsigned short *sprt1,unsigned short *mask,unsigned short maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite16_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


void GrayClipSprite32_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,unsigned long maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,const unsigned long *mask0,const unsigned long *mask1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_SMASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,const unsigned long *mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipSprite32_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


// MastaZog between others asked for GrayClipSpriteX8_X_R routines...



//-----------------------------------------------------------------------------
// CLIPPED TWO PLANE INTERLACED SPRITE FUNCTIONS
// The interlaced sprite format is as follows:
// * all routines except MASK: L/D or D/L (depending on the convention you use
//   for dest0 and dest1, usually LIGHT_PLANE and DARK_PLANE respectively, but
//   you can do otherwise), without mask.
// * MASK: M/L/D or M/D/L (depending on the convention you use for dest0 and
//   dest1, usually LIGHT_PLANE and DARK_PLANE respectively, but you can do
//   otherwise), mask is applied to both planes.
//
// With some amount of work, depending on your knowledge of assembly, you
// can make other TRAND/L routines from GrayClipISprite16_TRAND/L_R.
//
// As you can guess, GrayClipISpriteX16_MASK_R draws an interlaced masked
// sprite whose width is multiple of 16 pixels, with the "interlacement size"
// (size of a M/L/D chunk) being 3*2 bytes.
//-----------------------------------------------------------------------------
void GrayClipISprite8_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite8_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,unsigned char maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite8_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite8_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite8_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite8_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite8_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


void GrayClipISprite16_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,unsigned short maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_TRAND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_TRANL_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite16_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


void GrayClipISprite32_AND_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite32_BLIT_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,unsigned long maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite32_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite32_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite32_RPLC_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite32_TRANB_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite32_TRANW_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISprite32_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


void GrayClipISpriteX16_MASK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d3"),unsigned short *sprt,short wordwidth asm("%d2"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayClipISpriteX16_OR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d3"),unsigned short *sprt,short wordwidth asm("%d2"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));


//-----------------------------------------------------------------------------
// NON-CLIPPED DOUBLE PLANE SINGLE SPRITE FUNCTIONS.
// These functions draw a single sprite to two planes. They were originally
// made by David Randall.
//-----------------------------------------------------------------------------
void GraySingleSprite8_BLACK_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySingleSprite8_COLOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt,unsigned short color,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySingleSprite8_DGRAY_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySingleSprite8_LGRAY_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySingleSprite8_WHITE_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GraySingleSprite8_XOR_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),unsigned char *sprt,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));



//-----------------------------------------------------------------------------
// NON-CLIPPED SINGLE PLANE TILE (ALIGNED SPRITE, USUAL SPRITE FORMAT) FUNCTIONS
// (nothing to do with the tilemap engine).
//-----------------------------------------------------------------------------
void Tile8x8_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile8x8_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite asm("%a1"),unsigned char maskval asm("%d3"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile8x8_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite asm("%a1"),const unsigned char* mask,void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile8x8_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile8x8_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile8x8_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));

void Tile16x16_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile16x16_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite asm("%a1"),unsigned short maskval asm("%d3"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile16x16_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite asm("%a1"),const unsigned short* mask,void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile16x16_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile16x16_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile16x16_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));

void Tile32x32_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile32x32_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite asm("%a1"),unsigned long maskval asm("%d3"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile32x32_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite asm("%a1"),const unsigned long* mask,void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile32x32_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile32x32_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));
void Tile32x32_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite asm("%a1"),void *plane asm("%a0")) __attribute__((__stkparm__));



//-----------------------------------------------------------------------------
// NON-CLIPPED TWO PLANE TILE (ALIGNED SPRITE, USUAL SPRITE FORMAT) FUNCTIONS
// (nothing to do with the tilemap engine).
//-----------------------------------------------------------------------------
void GrayTile8x8_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,unsigned char maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,const unsigned char* mask1,const unsigned char* mask2,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_SMASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,const unsigned char* mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_TRANB_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_TRANW_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile8x8_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprt0,const unsigned char *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GrayTile16x16_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,unsigned short maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,const unsigned short* mask1,const unsigned short* mask2,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_SMASK_R(short col asm("%d0"),short y asm("%d1"),unsigned short *sprt0,unsigned short *sprt1,unsigned short* mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_TRANB_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_TRANW_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile16x16_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprt0,const unsigned short *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GrayTile32x32_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,unsigned long maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,const unsigned long* mask1,const unsigned long* mask2,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_SMASK_R(short col asm("%d0"),short y asm("%d1"),unsigned long *sprt0,unsigned long *sprt1,unsigned long* mask,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_TRANB_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_TRANW_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayTile32x32_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprt0,const unsigned long *sprt1,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));



//-----------------------------------------------------------------------------
// NON-CLIPPED TWO PLANE TILE (ALIGNED SPRITE, INTERLACED SPRITE FORMAT) FUNCTIONS
// (nothing to do with the tilemap engine).
// The interlaced sprite format is as follows:
// * all routines except MASK: L/D or D/L (depending on the convention you use
//   for dest0 and dest1, usually LIGHT_PLANE and DARK_PLANE respectively, but
//   you can do otherwise), without mask.
// * MASK: M/L/D or M/D/L (depending on the convention you use for dest0 and
//   dest1, usually LIGHT_PLANE and DARK_PLANE respectively, but you can do
//   otherwise), mask is applied to both planes.
//-----------------------------------------------------------------------------
void GrayITile8x8_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile8x8_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,unsigned char maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile8x8_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile8x8_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile8x8_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile8x8_TRANB_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile8x8_TRANW_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile8x8_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned char *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GrayITile16x16_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile16x16_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,unsigned short maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile16x16_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile16x16_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile16x16_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile16x16_TRANB_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile16x16_TRANW_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile16x16_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned short *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));

void GrayITile32x32_AND_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile32x32_BLIT_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,unsigned long maskval asm("%d3"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile32x32_MASK_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile32x32_OR_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile32x32_RPLC_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile32x32_TRANB_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile32x32_TRANW_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));
void GrayITile32x32_XOR_R(short col asm("%d0"),short y asm("%d1"),const unsigned long *sprite,void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__stkparm__));



//-----------------------------------------------------------------------------
// TRANSITION EFFECTS.
// Many I'd like to make are currently missing.
//-----------------------------------------------------------------------------
void FadeOutToBlack_CWS1_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_CWS1_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

void FadeOutToBlack_CCWS1_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_CCWS1_R(void* lightplane asm("%a0"),void* darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));


void FadeOutToBlack_LR_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_LR_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToBlack_LR18_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_LR18_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToBlack_LR28_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_LR28_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

void FadeOutToBlack_RL_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_RL_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToBlack_RL18_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_RL18_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToBlack_RL28_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_RL28_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));


void FadeOutToBlack_TB_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_TB_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));

void FadeOutToBlack_BT_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));
void FadeOutToWhite_BT_R(void *lightplane asm("%a0"),void *darkplane asm("%a1"),short height asm("%d0"),short bytewidth asm("%d1"),short wait asm("%d2"));


void GrayIShadowPlanesX16_R(short height asm("%d0"),short wordwidth asm("%d1"), void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__regparm__(4)));
void GrayShadowPlanesX16_R(short height asm("%d0"),short wordwidth asm("%d1"), void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__regparm__(4)));
void GrayIShadowPlanes240_R(short height asm("%d0"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__regparm__(3)));
void GrayShadowPlanes240_R(short height asm("%d0"),void *dest0 asm("%a0"),void *dest1 asm("%a1")) __attribute__((__regparm__(3)));
void GrayIShadowPlanesTo_R(void *src0 asm("%a0"),void *src1 asm("%a1"),void *dest0,void *dest1) __attribute__((__stkparm__));
void GrayShadowPlanesTo_R(void *src0 asm("%a0"),void *src1 asm("%a1"),void *dest0,void *dest1) __attribute__((__stkparm__));

void FastFillScreen_R(void *plane asm("%a0"));
void FastClearScreen_R(void *plane asm("%a0"));
// Fills (len-len%4) bytes of plane with LFSR-generated garbage, initialized with seed. Less
// random but two orders of magnitude faster than using other pseudo-random generators like
// twice the number of writes of random(RAND_MAX)+random(RAND_MAX).
void FillScreenWithGarbage_R(unsigned long seed asm("%d0"),unsigned short len asm("%d1"), void *plane asm("%a0"));



//-----------------------------------------------------------------------------
// Helper functions to create shadows and inverse shadows from sprites, in
// order to draw them with OR routines (significantly faster than SHADOW
// routines removed starting from 2.00 Beta 4). This way takes a slightly
// greater amount of memory, but is significantly more efficient at run-time.
//-----------------------------------------------------------------------------
void CreateSpriteIShadow8_R(short height asm("%d0"),const unsigned char* src0 asm("%a0"),const unsigned char* src1 asm("%a1"),const unsigned char* mask, unsigned char* dest0, unsigned char* dest1) __attribute__((__stkparm__));
void CreateSpriteIShadow16_R(short height asm("%d0"),const unsigned short* src0 asm("%a0"),const unsigned short* src1 asm("%a1"),const unsigned short* mask, unsigned short* dest0, unsigned short* dest1) __attribute__((__stkparm__));
void CreateSpriteIShadow32_R(short height asm("%d0"),const unsigned long* src0 asm("%a0"),const unsigned long* src1 asm("%a1"),const unsigned long* mask, unsigned long* dest0, unsigned long* dest1) __attribute__((__stkparm__));
void CreateSpriteIShadowX8_R(short height asm("%d0"),short bytewidth asm("%d1"),const unsigned char* src0 asm("%a0"),const unsigned char* src1 asm("%a1"),const unsigned char* mask, unsigned char* dest0, unsigned char* dest1) __attribute__((__stkparm__));

void CreateSpriteShadow8_R(short height asm("%d0"),const unsigned char* src0 asm("%a0"),const unsigned char* src1 asm("%a1"),const unsigned char* mask, unsigned char* dest0, unsigned char* dest1) __attribute__((__stkparm__));
void CreateSpriteShadow16_R(short height asm("%d0"),const unsigned short* src0 asm("%a0"),const unsigned short* src1 asm("%a1"),const unsigned short* mask, unsigned short* dest0, unsigned short* dest1) __attribute__((__stkparm__));
void CreateSpriteShadow32_R(short height asm("%d0"),const unsigned long* src0 asm("%a0"),const unsigned long* src1 asm("%a1"),const unsigned long* mask, unsigned long* dest0, unsigned long* dest1) __attribute__((__stkparm__));
void CreateSpriteShadowX8_R(short height asm("%d0"),short bytewidth asm("%d1"),const unsigned char* src0 asm("%a0"),const unsigned char* src1 asm("%a1"),const unsigned char* mask, unsigned char* dest0, unsigned char* dest1) __attribute__((__stkparm__));

void CreateISpriteIShadow8_R(short height asm("%d0"),const unsigned char* src asm("%a0"),unsigned char* dest asm("%a1"));
void CreateISpriteIShadow16_R(short height asm("%d0"),const unsigned short* src asm("%a0"),unsigned short* dest asm("%a1"));
void CreateISpriteIShadow32_R(short height asm("%d0"),const unsigned long* src asm("%a0"),unsigned long* dest asm("%a1"));

void CreateISpriteShadow8_R(short height asm("%d0"),const unsigned char* src asm("%a0"),unsigned char* dest asm("%a1"));
void CreateISpriteShadow16_R(short height asm("%d0"),const unsigned short* src asm("%a0"),unsigned short* dest asm("%a1"));
void CreateISpriteShadow32_R(short height asm("%d0"),const unsigned long* src asm("%a0"),unsigned long* dest asm("%a1"));



//-----------------------------------------------------------------------------
// Fast SpriteGet/RPLC functions and macros. They are designed for programs
// where redrawing everything every frame is detrimental to speed. See demo22,
// demo23 and the documentation for hints.
// (Clip)FastGetBkgrnd8/16_R requires dest being at least 4*h+6 bytes long;
// (Clip)FastGetBkgrnd32_R requires dest being at least 6*h+6 bytes long;
// Gray(Clip)FastGetBkgrnd8/16_R require dest being at least 8*h+6 bytes long;
// Gray(Glip)FastGetBkgrnd32_R requires dest being at least 12*h+6 bytes long.
//
// Special thanks go to Julien Richard-Foy: he needed such routines for one
// of his own projects. Mine were not exactly what he was looking for, but
// his idea of storing the offset instead of recomputing everything from the
// parameters is great. I went further, storing as well the x coordinate (not
// necessarily anded with 15) and the offset from start of plane and the
// height - hence the +6 bytes.
//-----------------------------------------------------------------------------
void FastGetBkgrnd8_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned short* dest asm("%a1"));
void FastGetBkgrnd16_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned short* dest asm("%a1"));
void FastGetBkgrnd32_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src asm("%a0"),unsigned short* dest asm("%a1"));
void FastPutBkgrnd8_R(const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));
void FastPutBkgrnd16_R(const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));
void FastPutBkgrnd32_R(const unsigned short *sprt asm("%a1"),void *dest asm("%a0"));

void GrayFastGetBkgrnd8_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src1 asm("%a0"),void* src2 asm("%a1"),unsigned short* dest asm("%a2"));
void GrayFastGetBkgrnd16_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src1 asm("%a0"),void* src2 asm("%a1"),unsigned short* dest asm("%a2"));
void GrayFastGetBkgrnd32_R(short x asm("%d0"),short y asm("%d1"),short h asm("%d2"),void* src1 asm("%a0"),void* src2 asm("%a1"),unsigned short* dest asm("%a2"));
void GrayFastPutBkgrnd8_R(const unsigned short *sprt asm("%a2"),void *dest1 asm("%a0"),void *dest2 asm("%a1"));
void GrayFastPutBkgrnd16_R(const unsigned short *sprt asm("%a2"),void *dest1 asm("%a0"),void *dest2 asm("%a1"));
void GrayFastPutBkgrnd32_R(const unsigned short *sprt asm("%a2"),void *dest1 asm("%a0"),void *dest2 asm("%a1"));



//-----------------------------------------------------------------------------
// Tilemap Engine.
//-----------------------------------------------------------------------------
// See tilemap.h.
// NOTE1: the API was somewhat changed by Julien between the versions. New
// functions were added, but the most useless ones were removed, because they
// were a maintenance burden. I did the same later for (I)SHADOW(2) functions
// in extgraph.h and extgraph.a. Beta 4 and later reflect the changes in the
// tilemap engine.
// NOTE2: ExtGraph 2.00 Beta 5 is still incompatible with the official TIGCCLIB
// grayscale doublebuffering support, because the TIGCCLIB grayscale support
// does not allocate both planes consecutively on HW1), _BUT_ there is a fork,
// which is one of the two ways to use this tilemap engine with doublebuffering.
// Read the root of the ExtGraph documentation for more information.



//-----------------------------------------------------------------------------
// Brute-force preshifted sprite functions and macros.
//-----------------------------------------------------------------------------
// See preshift.h.



//-----------------------------------------------------------------------------
// Miscellanous SpriteX8(X8) functions (mirror, rotate).
// SpriteX8X8_ROTATE_RIGHT_R and SpriteX8X8_ROTATE_LEFT_R do not require the
// source sprite to be in a writable area. However, they require that both
// dimensions are multiples of 8 (they are coded for simplicity; coding
// routines supporting any height isn't extremely difficult).
//
// SpriteX8X8_RR_MH_R has a funny story: it was actually supposed to be
// SpriteX8X8_ROTATE_RIGHT_R, but I made mistakes in the implementation and
// when trying to fix it, after several modifications, it started creating
// r-rotated h-mirrored sprites.
// Therefore I saved that routine and coded a working SpriteX8X8_ROTATE_RIGHT_R.
// Afterwards, to complete the series of functions, I coded
// SpriteX8X8_RL_MH_R.
//
// I had forgotten to write SpriteX8_MIRROR_HV_R for a long period of time...
//
// FastSprite8/16/32/X8_MIRROR_H_R are fast sprite mirroring routines, using a
// 256-byte lookup table for chunks of 8 bits/pixels instead of a 16-byte lookup
// table for chunks of 4 bits/pixels. Courtesy of Geoffrey Anneheim for the
// 32xn routine, which I made twice faster than the original version.
//-----------------------------------------------------------------------------
void SpriteX8_MIRROR_H(short h,const unsigned char* src,short bytewidth,unsigned char* dest) __attribute__((__stkparm__));
void SpriteX8_MIRROR_H_R(short h asm("%d0"),const unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));

void SpriteX8_MIRROR_V(short h,const unsigned char* src,short bytewidth,unsigned char* dest) __attribute__((__stkparm__));
void SpriteX8_MIRROR_V_R(short h asm("%d0"),const unsigned char* src asm("%a1"),short bytewidth asm("%d2"),unsigned char* dest asm("%a0")) __attribute__((__regparm__(4)));

void SpriteX8_MIRROR_HV_R(short h asm("%d0"),const unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));

void SpriteX8X8_ROTATE_RIGHT_R(short h asm("%d0"),const unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));
void SpriteX8X8_ROTATE_LEFT_R(short h asm("%d0"),const unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));
void SpriteX8X8_RR_MH_R(short h asm("%d0"),const unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));
void SpriteX8X8_RL_MH_R(short h asm("%d0"),const unsigned char* src asm("%a0"),short bytewidth asm("%d1"),unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));

void FastSprite8_MIRROR_H_R(short h asm("%d2"),unsigned char *sprt asm("%a0"),unsigned char *dest asm("%a1"));
void FastSprite16_MIRROR_H_R(short h asm("%d2"),unsigned short *sprt asm("%a0"),unsigned short *dest asm("%a1"));
void FastSprite32_MIRROR_H_R(short h asm("%d2"),unsigned long *sprt asm("%a0"),unsigned long *dest asm("%a1"));
void FastSpriteX8_MIRROR_H_R(short h asm("%d2"),short bytewidth asm("%d1"),char *sprt asm("%a0"),unsigned char *dest asm("%a1"));



//-----------------------------------------------------------------------------
// Arbitrary angle sprite rotating functions. Courtesy of Joey Adams. Slightly
// modified to fit the needs.
//-----------------------------------------------------------------------------
void RotateSprite8_R(unsigned char *srcSprite asm("%a0"),unsigned char *destSprite asm("%a1"),short height,short originX asm("%d1"),short originY asm("%d2"),long degreesClockwise asm("%d0")) __attribute__((__stkparm__));
void RotateSprite16_R(unsigned short *srcSprite asm("%a0"),unsigned short *destSprite asm("%a1"),short height,short originX asm("%d1"),short originY asm("%d2"),long degreesClockwise asm("%d0")) __attribute__((__stkparm__));
void RotateSprite32_R(unsigned long *srcSprite asm("%a0"),unsigned long *destSprite asm("%a1"),short height,short originX asm("%d1"),short originY asm("%d2"),long degreesClockwise asm("%d0")) __attribute__((__stkparm__));
void RotateSpriteX8_R(unsigned char *srcSprite asm("%a0"),unsigned char *destSprite asm("%a1"),short width,short height,short originX asm("%d1"),short originY asm("%d2"),long degreesClockwise asm("%d0")) __attribute__((__stkparm__));


//-----------------------------------------------------------------------------
// Sine table (0..90) used in arbitrary angle sprite rotating functions, values
// multiplied by 8192 == 1<<13. Courtesy of Joey Adams. Exported at his request
// to avoid duplication of sine tables in case a program would use another sine
// table.
//-----------------------------------------------------------------------------
extern const short RS_sin8192tab[91];



//=============================================================================
//=============================================================================
//=============================================================================
//
// TTUNPACK.H (now extgraph.h contains everything necessary for unpacking)
// taken from TIGCC Tools Suite © 2000-2004 TICT
//
//=============================================================================
//=============================================================================
//=============================================================================
#ifndef __TTUNPACK_H__
#define __TTUNPACK_H__

typedef struct {
    unsigned char  osize_lo;   // original size lowbyte
    unsigned char  osize_hi;   // original size highbyte
    unsigned char  magic1;     // must be equal to TTUNPACK_MAGIC1
    unsigned char  magic2;     // must be equal to TTUNPACK_MAGIC2
    unsigned char  csize_lo;   // compressed size lowbyte
    unsigned char  csize_hi;   // compressed size highbyte
    unsigned char  esc1;       // escape >> (8-escBits)
    unsigned char  notused3;
    unsigned char  notused4;
    unsigned char  esc2;       // escBits
    unsigned char  gamma1;     // maxGamma + 1
    unsigned char  gamma2;     // (1<<maxGamma)
    unsigned char  extralz;    // extraLZPosBits
    unsigned char  notused1;
    unsigned char  notused2;
    unsigned char  rleentries; // rleUsed
} TTUNPACK_HEADER;

#define TTUNPACK_MAGIC1 0x54
#define TTUNPACK_MAGIC2 0x50

#define ttunpack_size(_p_)  ((unsigned short)(((TTUNPACK_HEADER*)(_p_))->osize_lo | (((TTUNPACK_HEADER*)(_p_))->osize_hi << 8)))
#define ttunpack_valid(_p_) (((TTUNPACK_HEADER*)(_p_))->magic1 == TTUNPACK_MAGIC1 && ((TTUNPACK_HEADER*)(_p_))->magic2 == TTUNPACK_MAGIC2)

#define TTUNPACK_OKAY             0
#define TTUNPACK_NOESCFOUND     248
#define TTUNPACK_ESCBITS        249
#define TTUNPACK_MAXGAMMA       250
#define TTUNPACK_EXTRALZP       251
#define TTUNPACK_NOMAGIC        252
#define TTUNPACK_OUTBUFOVERRUN  253
#define TTUNPACK_LZPOSUNDERRUN  254

short UnpackBuffer(unsigned char *src, unsigned char *dest) __attribute__((__stkparm__));
#define ttunpack_decompress UnpackBuffer

short UnpackBufferGray(unsigned char *src, unsigned char *dest) __attribute__((__stkparm__));
#define ttunpack_decompress_gray UnpackBufferGray


#else
#error EXTGRAPH.H already contains TTUNPACK.H defines (remove ttunpack.h include !)
#endif





//=============================================================================
//=============================================================================
//=============================================================================
//
// TTARCHIVE.H (now extgraph.h contains everything for archive handling)
// taken from TIGCC Tools Suite © 2000-2004 TICT
//
//=============================================================================
//=============================================================================
//=============================================================================
#ifndef __TTARCHIVE_H__
#define __TTARCHIVE_H__

//-----------------------------------------------------------------------------
// entry of archive structure
//-----------------------------------------------------------------------------
typedef struct {
   unsigned short offset;     // offset to the entry data from end of entry list
   unsigned short length;     // length of entry
   char           name[8];    // entry name
   unsigned char  misc1[2];   // info from cfg file (may be queried by a program)
   unsigned char  misc2[2];   // info from cfg file (may be queried by a program)
} TTARCHIVE_ENTRY;

//-----------------------------------------------------------------------------
// header of a TTARCHIVE file
//-----------------------------------------------------------------------------
typedef struct {
   unsigned long   magic;    // must be equal to TTARCHIVE_MAGIC
   unsigned short  nr;       // number of entries
   TTARCHIVE_ENTRY entry[0]; // here comes the list of TTARCHIVE_ENTRY structures
} TTARCHIVE_HEADER;

#define TTARCHIVE_MAGIC 0x74746100L

//-----------------------------------------------------------------------------
// smart macros to access ttarchive
//
// _p_   ... pointer to archive start address
// _i_   ... index of entry
//
// NOTE: No checking is done in the macros !!
//-----------------------------------------------------------------------------

#define ttarchive_valid(_p_)     (((TTARCHIVE_HEADER*)(_p_))->magic == TTARCHIVE_MAGIC)
#define ttarchive_entries(_p_)   (((TTARCHIVE_HEADER*)(_p_))->nr)
#define ttarchive_desc(_p_,_i_)  (&(((TTARCHIVE_HEADER*)(_p_))->entry[_i_]))
#define ttarchive_data(_p_,_i_)  (((unsigned char*)&(((TTARCHIVE_HEADER*)(_p_))->entry[((TTARCHIVE_HEADER*)(_p_))->nr]))+\
                                 ((TTARCHIVE_HEADER*)(_p_))->entry[_i_].offset)

#define ttarchive_size(_p_)      ({TTARCHIVE_ENTRY* e=&(((TTARCHIVE_HEADER*)(_p_))->entry[((TTARCHIVE_HEADER*)(_p_))->nr-1]);\
                                  ((unsigned char*)e)+sizeof(TTARCHIVE_ENTRY)+e->offset+e->length-(unsigned char*)(_p_);})

#define ttarchive_info(_p_)      ({char* p=((char*)(_p_))+ttarchive_size(_p_)+21;\
                                  ((!(*p) && (*(p+1) ==((char)0xad)))?(p-20):NULL);})

#define TTARCHIVE_INFOLENGTH 20

#else
#error EXTGRAPH.H already contains TTARCHIVE.H defines (remove ttarchive.h include !)
#endif

#endif

//#############################################################################
// Revision History
//#############################################################################
//
// Huge changes for v2.00 (rewrites, internal organization of library...).
// No longer using CVS, but using online SVN starting from 2.00 Beta 5.
// The changelog is in the documentation and will stay there.
//
// -- ExtGraph 2.xx --
//
//
// $Log: extgraph.h,v $
//
// Revision 1.13  2002/05/22 09:19:20  tnussb
// for TIGCC versions greater than 0.93 all functions are declared with
// "__attribute__((__stkparm__))" to work correctly with compilation
// switch -mregparm
//
// Revision 1.12  2002/05/08 19:32:46  tnussb
// version number raised (just a bug in unpack function was fixed)
//
// Revision 1.11  2002/04/05 13:47:28  tnussb
// changes for v1.00
//
// Revision 1.10  2002/04/02 18:10:35  tnussb
// version number raised
//
// Revision 1.9  2002/03/21 12:20:39  tnussb
// FastDrawVLine added and version number changed
//
// Revision 1.8  2002/02/25 17:01:01  tnussb
// ttunpack stuff moved in front of ttarchive stuff
//
// Revision 1.7  2002/02/25 13:16:42  tnussb
// ttarchive.h and ttunpack.h integrated
//
// Revision 1.6  2002/02/22 17:13:57  tnussb
// fixed double use of EXTGRAPH_VERSION_MAIN and EXTGRAPH_VERSION_SUB (thanx, Kevin!)
//
// Revision 1.5  2002/02/22 16:31:03  tnussb
// (1) version depended stuff added (like EXTGRAPH_VERSION_STR)
// (2) complete header revised
// (3) CheckHWMatch() and DESIRED_CALCTYPE added
//
// Revision 1.4  2002/02/11 13:43:54  tnussb
// version number raised
//
// Revision 1.3  2002/02/11 10:24:37  tnussb
// generic commit for v0.87
//
// Revision 1.2  2001/06/22 14:33:01  Thomas Nussbaumer
// grayscale sprite drawing routines added
//
// Revision 1.1  2001/06/20 21:34:08  Thomas Nussbaumer
// initial check-in
//
//
