#include <tigcclib.h>         // Include All Header Files
#include "extgraph.h"

// Sprites provided for convenience.
unsigned char sprite_8[8] = {0x1,0x3,0x7,0xF,0x1F,0x3F,0x7F,0xFF};

unsigned short sprite_16[16] = {
0x1,0x3,0x7,0xF,
0x1F,0x3F,0x7F,0xFF,
0x1FF,0x3FF,0x7FF,0xFFF,
0x1FFF,0x3FFF,0x7FFF,0xFFFF
};

unsigned short sprite_16_2[16] = {
0x5555,0xAAAA,0x5555,0xAAAA,
0x5555,0xAAAA,0x5555,0xAAAA,
0x5555,0xAAAA,0x5555,0xAAAA,
0x5555,0xAAAA,0x5555,0xAAAA
};

// Warning, this sprite has a symmetry...
unsigned long sprite_32[32] = {
0x00000000,0x11111111,
0x22222222,0x33333333,
0x44444444,0x55555555,
0x66666666,0x77777777,
0x88888888,0x99999999,
0xAAAAAAAA,0xBBBBBBBB,
0xCCCCCCCC,0xDDDDDDDD,
0xEEEEEEEE,0xFFFFFFFF,
0xFFFFFFFF,0xEEEEEEEE,
0xDDDDDDDD,0xCCCCCCCC,
0xBBBBBBBB,0xAAAAAAAA,
0x99999999,0x88888888,
0x77777777,0x66666666,
0x55555555,0x44444444,
0x33333333,0x22222222,
0x11111111,0x00000000,
};

// TICT's logo, inclued because it's a nontrivial 64x64 sprite.
unsigned long long sprite_64[64] = {
0xffffffffffffffffULL,0xffffffff00000001ULL,0xffffffff00000001ULL,0xf0000007007fff01ULL,
0xf0f80f870007f801ULL,0xf1f80fc70007f001ULL,0xf3f80fe70007f001ULL,0xf7f80ff70007f001ULL,
0xf7f80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f801ULL,0xfff007ff000ff801ULL,
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,
0xc0000000ffffffffULL,0xc0000000ffffffffULL,0xc000fc04ffffffffULL,0xc00fff84f0000007ULL,
0xc07f00fcf0f80f87ULL,0xc0fe007cf1f80fc7ULL,0xc0fc001cf3f80fe7ULL,0xc1f8001cf7f80ff7ULL,
0xc7f0000cf7f80fffULL,0xc7f00004fff80fffULL,0xcfe00004fff80fffULL,0xcfe00000fff80fffULL,
0xdfe00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,
0xdfc00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,
0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,0xc7f00000fff80fffULL,0xc7f00004fff80fffULL,
0xc1f8001cfff80fffULL,0xc0fc0038fff80fffULL,0xc0ff00e0fff80fffULL,0xc07fc7c0fff007ffULL,
0xc001fc00ffffffffULL,0xc0000000ffffffffULL,0xffffffffffffffffULL,0xffffffffffffffffULL};


unsigned char dest_8[8];
unsigned short dest_16[16];
unsigned long dest_32[32];
unsigned long dest2_32[32];
unsigned long long dest_64[64];


void _main(void) {
    // Counters...
    register short i = 0, j = 0;

    // Old font.
    short f = FontGetSys();

    // The goal of those two strings is to show whether there are buffer
    // overruns.
    const char z1[52]="01234567890123456789013245678901234567890123456789\0";
    LCD_BUFFER lcd[2];
    const char z2[52]="01234567890123456789013245678901234567890123456789\0";


    // The first one if you want to fill the planes, the second one if you
    // want to clear them.
//    GrayFillScreen2B_R(&lcd[0],&lcd[1]);
//    GrayClearScreen2B_R(&lcd[0],&lcd[1]);

    // If you need a timer...
/*
    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,10000*20);
*/

    // Loop suitable for clipped sprite functions.
    // See below if you want to test a particular function / set of functions.
/*
    for (i = -300; i < 300; i++) {
        for (j = -300; j < 300; j++) {
            // Add your call here.
            // Sample: GrayClipSprite32_MASK_R(i,j,32,sprite_32,sprite_32,sprite_32,sprite_32,&lcd[0],&lcd[1]);
        }
    }
*/
    // Loop suitable for non-clipped sprite functions.
    // See below if you want to test a particular function / set of functions.
/*
    for (i = 0; i <= 240 - [WIDTH OF SPRITE]; i++) {
        for (j = 0; j <= 128 - [HEIGHT OF SPRITE]; j++) {
            // Add your call here.
            // Sample: GraySprite16_OR(i,j,16,sprite_16,sprite_16,&lcd[0],&lcd[1]);
        }
    }
*/
    // If you use grayscale...
/*
    if (!GrayOn()) return;
    memcpy(GetPlane(LIGHT_PLANE),&lcd[0],LCD_SIZE);
    memcpy(GetPlane(DARK_PLANE),&lcd[1],LCD_SIZE);
    ngetchx();
    GrayOff();
*/

    // If you don't use grayscale...
/*
    memcpy(LCD_MEM,&lcd[0],LCD_SIZE);
    ngetchx();
*/

    FontSetSys(F_4x6);
    DrawStr(0,0,z1,A_REPLACE);
    DrawStr(0,6,z2,A_REPLACE);
    ngetchx();

    // If you used a timer...
/*
    OSFreeTimer(USER_TIMER);
*/

    // Restore font.
    FontSetSys(f);

    // Clean up keyboard queue.
    GKeyFlush();
    OSClearBreak();
}

