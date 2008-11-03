/******************************************************************************
*
* project name:    ExtGraph
* file name:       demo34.c (originally tribute.c from the TIGCC Tools Suite)
* initial date:    17/08/2000
* author:          thomas.nussbaumer@gmx.net
* contributor:     lionel_debroux@yahoo.fr
* description:     Demo of TTArchive functions
*
******************************************************************************/

#define SAVE_SCREEN
#define OPTIMIZE_ROM_CALLS
#define NO_EXIT_SUPPORT
#define MIN_AMS 100

#include <tigcclib.h>
#include "../../lib/extgraph.h"  // NOTE: this path is just for this demo !!
                                 //       if the extgraph library is correctly
                                 //       installed you should use:
                                 //
                                 //       #include <extgraph.h>


//=============================================================================
// fetch picture from ttarchive and decompress it to buffer
//=============================================================================
static inline short GetPic(unsigned char* buffer, unsigned short index,unsigned char* archive) {
    unsigned short entries;
    unsigned short i;

    if (!ttarchive_valid(archive)) {
        ST_helpMsg("not a valid archive [press a key]");
        ngetchx();
        return 0;
    }

    entries = ttarchive_entries(archive);

    for (i=0;i<entries;i++) {
        short retval;
        if (i==index) {
            retval = ttunpack_decompress(ttarchive_data(archive,i),buffer);

            if (!retval) return 1;
            else         return 0;
        }
    }

    return 0;
}

//=============================================================================
// show the picture
//=============================================================================
static inline short ShowPic(unsigned char* buffer, unsigned char *plane1, unsigned char *plane2) {
    short          i;
    unsigned long* dest1 = (unsigned long *)plane1;
    unsigned long* dest2 = (unsigned long *)plane2;
    unsigned long* src1  = (unsigned long *)buffer;
    unsigned long* src2  = (unsigned long *)(buffer+2000);

    // Make (nearly) centered on 92+/V200.
    if (!TI89) {
        dest1 += ((30*14 + 4)/sizeof(unsigned long));
        dest2 += ((30*14 + 4)/sizeof(unsigned long));
    }

    for (i=0;i<100;i++) {
        *dest1++ = *src1++, *dest2++ = *src2++;
        *dest1++ = *src1++, *dest2++ = *src2++;
        *dest1++ = *src1++, *dest2++ = *src2++;
        *dest1++ = *src1++, *dest2++ = *src2++;
        *dest1++ = *src1++, *dest2++ = *src2++;
        ((unsigned char *)dest1) += 10;
        ((unsigned char *)dest2) += 10;
    }

    return ngetchx();
}

//=============================================================================
// nomen omen est
//=============================================================================
void _main(void) {
    unsigned char* src;
    SYM_ENTRY*     symptr = DerefSym(SymFind(SYMSTR_CONST("demo34dt")));
    __attribute__((__aligned__(2))) unsigned char  buffer[4000];
    short          i;
    unsigned char *plane1 = NULL;
    unsigned char *plane2 = NULL;

    if(!symptr) {
        ST_helpMsg("Data file not found [press a key]");
        ngetchx();
        return;
    }

    src = HLock(symptr->handle);

    src+=2;  // skip "length of variable" bytes

    //---------------------------
    // turn on grayscale graphics
    //---------------------------
    if (!GrayOn()) {
        HeapUnlock(symptr->handle);
        ST_helpMsg("Grayscale init failure [press a key]");
        ngetchx();
        return;
    }

    //-----------------------------------------
    // setup bitplane globals and show the logo
    //-----------------------------------------
    plane1 = GrayGetPlane(LIGHT_PLANE);
    plane2 = GrayGetPlane(DARK_PLANE);

    GrayClearScreen2B_R(plane1, plane2);

    for (i=0;i<15;i++) {
        if (GetPic(buffer,i,src)) {
            asm("0: bra.s 0b");
            if (ShowPic(buffer, plane1, plane2) == KEY_ESC) break;
        }
        else {
            //                0123456789012345678901
            char message[] = "no pic with index    [press a key]";
            CharNumber(i, 18, message);
            strcat(message,"no pic with index    [press a key]" + 20);
            ST_helpMsg(message);
            ngetchx();
            break;
        }
    }

    GrayOff();
    HeapUnlock(symptr->handle);
}

//#############################################################################
//###################### NO MORE FAKES BEYOND THIS LINE #######################
//#############################################################################
//
//=============================================================================
// Revision History
//=============================================================================
//
// $Log: tribute.c,v $
// Revision 1.4  2002/03/14 10:41:17  tnussb
// source "modernized" for TIGCC v0.93 and above
//
// Revision 1.3  2001/02/10 20:24:16  Thomas Nussbaumer
// using now new calctools header files
//
// Revision 1.2  2000/08/20 16:14:38  Thomas Nussbaumer
// (1) using now shared unpack.c
// (2) using now ttarchive.h
// (3) HeapUnlock() added before returning from main
//
// Revision 1.1  2000/08/16 23:14:08  Thomas Nussbaumer
// initial version
//
//
//
