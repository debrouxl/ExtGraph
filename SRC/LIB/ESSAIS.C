// C Source File
// Created 17/11/2002; 18:38:11

#define MIN_AMS 205
#define NO_AMS_CHECK
// Note: compiler-side and linker-side constant merging are disabled, since they can merge the
// destination sprites defined below. But as a side effect, using the macro definitions for the
// sprites is extremely wasteful, all the more the sprites are large.

#define debug_printf _rom_call(short,(const char*,...),479)
#define debug_printf_enabled (*((unsigned char *)(_rom_call_addr(47A))))

// 205modif-mod pour tester TICT-Explorer: dernière instruction avant le programme kernel-based:
// jsr 0(a5,d0.l) à 3BBD8.
// 0x34.l (launch) = 3C228.

















#include <tigcclib.h>         // Include All Header Files
#include "extgraph.h"
#include "preshift.h"


#define sprite_8 \
((unsigned char[8]){0x1,0x3,0x7,0xF,0x1F,0x3F,0x7F,0xFF})
#define isprite_8 \
((unsigned char[2*8]){0x1,0x1,0x3,0x3,0x7,0x7,0xF,0xF,0x1F,0x1F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF})
#define msprite_8 \
((unsigned char[3*8]){0x1,0x1,0x1,0x3,0x3,0x3,0x7,0x7,0x7,0xF,0xF,0xF,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF})

#define sprite2_8 \
((unsigned char[8]){0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA})

#define sprite3_8 \
((unsigned char[11]){0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF})


#define sprite_16 \
((unsigned short[16]){0x1,0x3,0x7,0xF,0x1F,0x3F,0x7F,0xFF,0x1FF,0x3FF,0x7FF,0xFFF,0x1FFF,0x3FFF,0x7FFF,0xFFFF})
#define isprite_16 \
((unsigned short[2*16]){0x1,0x1,0x3,0x3,0x7,0x7,0xF,0xF,0x1F,0x1F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0x1FF,0x1FF,0x3FF,0x3FF,0x7FF,0x7FF,0xFFF,0xFFF,0x1FFF,0x1FFF,0x3FFF,0x3FFF,0x7FFF,0x7FFF,0xFFFF,0xFFFF})
#define msprite_16 \
((unsigned short[3*16]){0x1,0x1,0x1,0x3,0x3,0x3,0x7,0x7,0x7,0xF,0xF,0xF,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0x1FF,0x1FF,0x1FF,0x3FF,0x3FF,0x3FF,0x7FF,0x7FF,0x7FF,0xFFF,0xFFF,0xFFF,0x1FFF,0x1FFF,0x1FFF,0x3FFF,0x3FFF,0x3FFF,0x7FFF,0x7FFF,0x7FFF,0xFFFF,0xFFFF,0xFFFF})

#define sprite2_16 \
((unsigned short[16]){0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA,0x5555,0xAAAA})

/*
extern unsigned char sprite_24[3*23];
asm("
.byte 0x00
| Aligned to an odd boundary by intention.
sprite_24:
.word 0x0000
.byte 0x01
.word 0x0000
.byte 0x03
.word 0x0000
.byte 0x07
.word 0x0000
.byte 0x0F
.word 0x0000
.byte 0x1F
.word 0x0000
.byte 0x3F
.word 0x0000
.byte 0x7F
.word 0x0000
.byte 0xFF
.word 0x0001
.byte 0xFF
.word 0x0003
.byte 0xFF
.word 0x0007
.byte 0xFF
.word 0x000F
.byte 0xFF
.word 0x001F
.byte 0xFF
.word 0x003F
.byte 0xFF
.word 0x007F
.byte 0xFF
.word 0x00FF
.byte 0xFF
.word 0x01FF
.byte 0xFF
.word 0x03FF
.byte 0xFF
.word 0x07FF
.byte 0xFF
.word 0x0FFF
.byte 0xFF
.word 0x1FFF
.byte 0xFF
.word 0x3FFF
.byte 0xFF
.word 0x7FFF
.byte 0xFF
.even
");
*/

#define isprite2_16 \
((unsigned short[32]) \
{0b0000011111100000,0b1111100000011111,\
0b0001100000011000,0b1110000000000111,\
0b0010000000000100,0b1100000000000011,\
0b0100000000000010,0b1000000000000001,\
0b0100010000100010,0b1000000000000001,\
0b1000101001010001,0b0000000000000000,\
0b1000000000000001,0b0000000000000000,\
0b1000000000000001,0b0000000000000000,\
0b1000000110000001,0b0000000000000000,\
0b1001100000011001,0b0000000000000000,\
0b1001010000101001,0b0000000000000000,\
0b0100101111010010,0b1000000000000001,\
0b0100010000100010,0b1000000000000001,\
0b0010001111000100,0b1100000000000011,\
0b0001100000011000,0b1110000000000111,\
0b0000011111100000,0b1111100000011111})

#define isprite3_16 \
((unsigned short[32]) \
{0b0000011111100000,0b0111100000011110,\
0b0001111111111000,0b1110000000000111,\
0b0011111111111100,0b1100000000000011,\
0b0111111111111110,0b1000000000000001,\
0b0111101111011110,0b1000000000000001,\
0b1111010110101111,0b0000000000000000,\
0b1111111111111111,0b0000000000000000,\
0b1111111111111111,0b0000000000000000,\
0b1111111001111111,0b0000000000000000,\
0b1110011111100111,0b0000000000000000,\
0b1110101111010111,0b0000000000000000,\
0b0111010000101110,0b1000000000000001,\
0b0111101111011110,0b1000000000000001,\
0b0011110000111100,0b1100000000000011,\
0b0001111111111000,0b1110000000000111,\
0b0000011111100000,0b0111100000011110})

#define isprite4_16 \
((unsigned short[32]) \
{0b1111100000011111,0b0000011111100000,\
0b1110000000000111,0b0001100000011000,\
0b1100000000000011,0b0010000000000100,\
0b1000000000000001,0b0100000000000010,\
0b1000000000000001,0b0100010000100010,\
0b0000000000000000,0b1000101001010001,\
0b0000000000000000,0b1000000000000001,\
0b0000000000000000,0b1000000000000001,\
0b0000000000000000,0b1000000110000001,\
0b0000000000000000,0b1001100000011001,\
0b0000000000000000,0b1001010000101001,\
0b1000000000000001,0b0100101111010010,\
0b1000000000000001,0b0100010000100010,\
0b1100000000000011,0b0010001111000100,\
0b1110000000000111,0b0001100000011000,\
0b1111100000011111,0b0000011111100000})

#define isprite5_16 \
((unsigned short[32]) \
{0b0111100000011110,0b0000011111100000,\
0b1110000000000111,0b0001111111111000,\
0b1100000000000011,0b0011111111111100,\
0b1000000000000001,0b0111111111111110,\
0b1000000000000001,0b0111101111011110,\
0b0000000000000000,0b1111010110101111,\
0b0000000000000000,0b1111111111111111,\
0b0000000000000000,0b1111111111111111,\
0b0000000000000000,0b1111111001111111,\
0b0000000000000000,0b1110011111100111,\
0b0000000000000000,0b1110101111010111,\
0b1000000000000001,0b0111010000101110,\
0b1000000000000001,0b0111101111011110,\
0b1100000000000011,0b0011110000111100,\
0b1110000000000111,0b0001111111111000,\
0b0111100000011110,0b0000011111100000})


#define sprite_32 \
((unsigned long[32]){0x00000000,0x11111111,0x22222222,0x33333333,0x44444444,0x55555555,0x66666666,0x77777777,0x88888888,0x99999999,0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEE,0xFFFFFFFF,0xFFFFFFFF,0xEEEEEEEE,0xDDDDDDDD,0xCCCCCCCC,0xBBBBBBBB,0xAAAAAAAA,0x99999999,0x88888888,0x77777777,0x66666666,0x55555555,0x44444444,0x33333333,0x22222222,0x11111111,0x00000000})
#define isprite_32 \
((unsigned long[2*32]){0x00000000,0x00000000,0x11111111,0x11111111,0x22222222,0x22222222,0x33333333,0x33333333,0x44444444,0x44444444,0x55555555,0x55555555,0x66666666,0x66666666,0x77777777,0x77777777,0x88888888,0x88888888,0x99999999,0x99999999,0xAAAAAAAA,0xAAAAAAAA,0xBBBBBBBB,0xBBBBBBBB,0xCCCCCCCC,0xCCCCCCCC,0xDDDDDDDD,0xDDDDDDDD,0xEEEEEEEE,0xEEEEEEEE,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xEEEEEEEE,0xEEEEEEEE,0xDDDDDDDD,0xDDDDDDDD,0xCCCCCCCC,0xCCCCCCCC,0xBBBBBBBB,0xBBBBBBBB,0xAAAAAAAA,0xAAAAAAAA,0x99999999,0x99999999,0x88888888,0x88888888,0x77777777,0x77777777,0x66666666,0x66666666,0x55555555,0x55555555,0x44444444,0x44444444,0x33333333,0x33333333,0x22222222,0x22222222,0x11111111,0x11111111,0x00000000,0x00000000})
#define msprite_32 \
((unsigned long[3*32]){0x00000000,0x00000000,0x00000000,0x11111111,0x11111111,0x11111111,0x22222222,0x22222222,0x22222222,0x33333333,0x33333333,0x33333333,0x44444444,0x44444444,0x44444444,0x55555555,0x55555555,0x55555555,0x66666666,0x66666666,0x66666666,0x77777777,0x77777777,0x77777777,0x88888888,0x88888888,0x88888888,0x99999999,0x99999999,0x99999999,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xBBBBBBBB,0xBBBBBBBB,0xBBBBBBBB,0xCCCCCCCC,0xCCCCCCCC,0xCCCCCCCC,0xDDDDDDDD,0xDDDDDDDD,0xDDDDDDDD,0xEEEEEEEE,0xEEEEEEEE,0xEEEEEEEE,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xEEEEEEEE,0xEEEEEEEE,0xEEEEEEEE,0xDDDDDDDD,0xDDDDDDDD,0xDDDDDDDD,0xCCCCCCCC,0xCCCCCCCC,0xCCCCCCCC,0xBBBBBBBB,0xBBBBBBBB,0xBBBBBBBB,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0x99999999,0x99999999,0x99999999,0x88888888,0x88888888,0x88888888,0x77777777,0x77777777,0x77777777,0x66666666,0x66666666,0x66666666,0x55555555,0x55555555,0x55555555,0x44444444,0x44444444,0x44444444,0x33333333,0x33333333,0x33333333,0x22222222,0x22222222,0x22222222,0x11111111,0x11111111,0x11111111,0x00000000,0x00000000,0x00000000})

#define sprite2_32 \
((unsigned long[32]){0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA,0x55555555,0xAAAAAAAA})

// TICT's logo, inclued because it's a nontrivial 64x64 sprite.
#define tictlogo64 \
((unsigned long long[64]){\
0xffffffffffffffffULL,0xffffffff00000001ULL,0xffffffff00000001ULL,0xf0000007007fff01ULL,\
0xf0f80f870007f801ULL,0xf1f80fc70007f001ULL,0xf3f80fe70007f001ULL,0xf7f80ff70007f001ULL,\
0xf7f80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f801ULL,0xfff007ff000ff801ULL,\
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,\
0xc0000000ffffffffULL,0xc0000000ffffffffULL,0xc000fc04ffffffffULL,0xc00fff84f0000007ULL,\
0xc07f00fcf0f80f87ULL,0xc0fe007cf1f80fc7ULL,0xc0fc001cf3f80fe7ULL,0xc1f8001cf7f80ff7ULL,\
0xc7f0000cf7f80fffULL,0xc7f00004fff80fffULL,0xcfe00004fff80fffULL,0xcfe00000fff80fffULL,\
0xdfe00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,\
0xdfc00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,\
0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,0xc7f00000fff80fffULL,0xc7f00004fff80fffULL,\
0xc1f8001cfff80fffULL,0xc0fc0038fff80fffULL,0xc0ff00e0fff80fffULL,0xc07fc7c0fff007ffULL,\
0xc001fc00ffffffffULL,0xc0000000ffffffffULL,0xffffffffffffffffULL,0xffffffffffffffffULL})

#define mtictlogo64 \
((unsigned long long[64*3]){\
0xffffffffffffffffULL,0xffffffffffffffffULL,0xffffffffffffffffULL,\
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,\
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,\
0xf0000007007fff01ULL,0xf0000007007fff01ULL,0xf0000007007fff01ULL,\
0xf0f80f870007f801ULL,0xf0f80f870007f801ULL,0xf0f80f870007f801ULL,\
0xf1f80fc70007f001ULL,0xf1f80fc70007f001ULL,0xf1f80fc70007f001ULL,\
0xf3f80fe70007f001ULL,0xf3f80fe70007f001ULL,0xf3f80fe70007f001ULL,\
0xf7f80ff70007f001ULL,0xf7f80ff70007f001ULL,0xf7f80ff70007f001ULL,\
0xf7f80fff0007f001ULL,0xf7f80fff0007f001ULL,0xf7f80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,0xfff80fff0007f001ULL,\
0xfff007ff000ff801ULL,0xfff007ff000ff801ULL,0xfff007ff000ff801ULL,\
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,\
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,\
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,\
0xffffffff00000001ULL,0xffffffff00000001ULL,0xffffffff00000001ULL,\
0xc0000000ffffffffULL,0xc0000000ffffffffULL,0xc0000000ffffffffULL,\
0xc0000000ffffffffULL,0xc0000000ffffffffULL,0xc0000000ffffffffULL,\
0xc000fc04ffffffffULL,0xc000fc04ffffffffULL,0xc000fc04ffffffffULL,\
0xc00fff84f0000007ULL,0xc00fff84f0000007ULL,0xc00fff84f0000007ULL,\
0xc07f00fcf0f80f87ULL,0xc07f00fcf0f80f87ULL,0xc07f00fcf0f80f87ULL,\
0xc0fe007cf1f80fc7ULL,0xc0fe007cf1f80fc7ULL,0xc0fe007cf1f80fc7ULL,\
0xc0fc001cf3f80fe7ULL,0xc0fc001cf3f80fe7ULL,0xc0fc001cf3f80fe7ULL,\
0xc1f8001cf7f80ff7ULL,0xc1f8001cf7f80ff7ULL,0xc1f8001cf7f80ff7ULL,\
0xc7f0000cf7f80fffULL,0xc7f0000cf7f80fffULL,0xc7f0000cf7f80fffULL,\
0xc7f00004fff80fffULL,0xc7f00004fff80fffULL,0xc7f00004fff80fffULL,\
0xcfe00004fff80fffULL,0xcfe00004fff80fffULL,0xcfe00004fff80fffULL,\
0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,\
0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,\
0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,\
0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,\
0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,\
0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,0xdfc00000fff80fffULL,\
0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,\
0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,\
0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,0xdfe00000fff80fffULL,\
0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,\
0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,0xcfe00000fff80fffULL,\
0xc7f00000fff80fffULL,0xc7f00000fff80fffULL,0xc7f00000fff80fffULL,\
0xc7f00004fff80fffULL,0xc7f00004fff80fffULL,0xc7f00004fff80fffULL,\
0xc1f8001cfff80fffULL,0xc1f8001cfff80fffULL,0xc1f8001cfff80fffULL,\
0xc0fc0038fff80fffULL,0xc0fc0038fff80fffULL,0xc0fc0038fff80fffULL,\
0xc0ff00e0fff80fffULL,0xc0ff00e0fff80fffULL,0xc0ff00e0fff80fffULL,\
0xc07fc7c0fff007ffULL,0xc07fc7c0fff007ffULL,0xc07fc7c0fff007ffULL,\
0xc001fc00ffffffffULL,0xc001fc00ffffffffULL,0xc001fc00ffffffffULL,\
0xc0000000ffffffffULL,0xc0000000ffffffffULL,0xc0000000ffffffffULL,\
0xffffffffffffffffULL,0xffffffffffffffffULL,0xffffffffffffffffULL,\
0xffffffffffffffffULL,0xffffffffffffffffULL,0xffffffffffffffffULL})


/*
#define dest_8 \
((unsigned char[3*8]){})
#define dest_16 \
((unsigned short[3*16]){})
#define dest_24 \
((unsigned char[3*24]){})
#define dest_32 \
((unsigned long[3*32]){})
#define dest_64 \
((unsigned long[3*64]){})
#define dest2_64 \
((unsigned long[3*64]){})
*/
//static unsigned long dest_64[3*64];
//static unsigned long dest2_64[3*64];

#define preshiftbuf \
((unsigned long[256]){})

/*
static const unsigned short sprite1[16] =
{
0b0000011111100000,
0b0001111111111000,
0b0011111111111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b1111111001111111,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000};

static const unsigned short sprite2[16] =
{
0b0000011111100000,
0b0001110000111000,
0b0011111001111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b0111110000111110,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000};
*/


volatile unsigned short counter = 0;

DEFINE_INT_HANDLER(MyInt5)
{
  counter++;
//  ExecuteHandler (OldInt5);
}

/*
// Routine by Exploder, tweaked a bit by Lionel (inverted the second and
// third EXT_SETPIX, changed << 1 to * 2).
// Bench on a circle of radius 25 drawn at (30;30), real 89 HW2 AMS 2.05,
// PRG_getStart() = 0xCE: 43 ticks to draw 2000 circles, ~930 circles / sec.
void old_ocircle(register void *plane asm("%a0"),
register unsigned short xc asm("%d0"),
register unsigned short yc asm("%d1"),
register unsigned short r asm("%d2")) {
        short int x = 0, y = r, d = 2 * (1 - r);
        while (y >= 0) {
                EXT_SETPIX(plane, (xc - x), (yc + y));
                EXT_SETPIX(plane, (xc - x), (yc - y));
                EXT_SETPIX(plane, (xc + x), (yc + y));
                EXT_SETPIX(plane, (xc + x), (yc - y));
                if(d + y > 0) {
                        y--;
                        d -= (y * 2) - 1;
                }
                if(x > d) {
                        x++;
                        d += (x * 2) + 1;
                }
        }
}
*/

/*
void __attribute__((__regparm__)) clip_ocircle(register void *plane asm("%a0"),register short xc asm("%d0"), register short yc asm("%d1"), register short r asm("%d2")) {        // clipped outlined circle
        register short d asm("%d3") = 2 * (1 - r);
        register short x1 asm("%d2") = xc;
        register short x2 asm("%d4") = xc;
        register short x asm("%d0") = 0;
        register short y1 asm("%d5") = yc - r;
        register short y2 asm("%d1") = yc + r;
        while (r >= 0) {
#if 0
                if (!((unsigned short)y1 > 127)) {
                        if (!((unsigned short)x1 > 239)) {
                                EXT_SETPIX(plane, x1, y1);
                        }
                        if (!((unsigned short)x2 > 239)) {
                                EXT_SETPIX(plane, x2, y1);
                        }
                }
                if (!((unsigned short)y2 > 127)) {
                        if (!((unsigned short)x1 > 239)) {
                                EXT_SETPIX(plane, x1, y2);
                        }
                        if (!((unsigned short)x2 > 239)) {
                                EXT_SETPIX(plane, x2, y2);
                        }
                }
#else

                if (!((unsigned short)x1 > 239)) {
                        if (!((unsigned short)y1 > 127)) {
                                EXT_SETPIX(plane, x1, y1);
                        }
                        if (!((unsigned short)y2 > 127)) {
                                EXT_SETPIX(plane, x1, y2);
                        }
                }
                if (!((unsigned short)x2 > 239)) {
                        if (!((unsigned short)y1 > 127)) {
                                EXT_SETPIX(plane, x2, y1);
                        }
                        if (!((unsigned short)y2 > 127)) {
                                EXT_SETPIX(plane, x2, y2);
                        }
                }
#endif

                if(d + r > 0) {
                        r--;
                        y1++;
                        y2--;
                        d -= (r * 2) - 1;
                }
                if(x > d) {
                        x++;
                        x1--;
                        x2++;
                        d += (x * 2) + 1;
                }
        }
}
*/
// Found in Ice Hockey 68k.
/*
#define Clip_Pix(x, y)		if ((x) >= 0 && (x) <= 239 && (y) >= 0 && (y) <= 127) EXT_SETPIX(plane, x, y)


void Circle_Clipped(register void *plane asm("%a0"),register short CX asm("%d0"),register short CY asm("%d1"),register short Radius asm("%d2")) {
	short Xchange = 1 - (Radius * 2), Ychange = 1, x = Radius, y = 0, RadiusError = 0;

	while(x >= y) {
		Clip_Pix(CX+x, CY+y);  // point in octant 1
		Clip_Pix(CX-x, CY+y);  // point in octant 4
		Clip_Pix(CX-x, CY-y);  // point in octant 5
		Clip_Pix(CX+x, CY-y);  // point in octant 8
		Clip_Pix(CX+y, CY+x);  // point in octant 2
		Clip_Pix(CX-y, CY+x);  // point in octant 3
		Clip_Pix(CX-y, CY-x);  // point in octant 6
		Clip_Pix(CX+y, CY-x);  // point in octant 7

		y++;
		RadiusError += Ychange;
		Ychange += 2;

		if ((RadiusError+RadiusError) + Xchange > 0) {
			x--;
			RadiusError += Xchange;
			Xchange += 2;
		}
	}
}
*/

/*
void __attribute__((__regparm__)) fcircle(int xc, int yc, int r) {        // filled circle
        int x = 0, y = r, d = 2 * (1 - r);
        int x1, y1, x2;
        while (y >= 0) {
                x1 = xc - x;
                x2 = xc + x;
                y1 = yc + y;
                if (x >> 3) {
                        FastDrawHLine_R(LCD_MEM, x1, x2, y1, A_NORMAL);
                        y1 = yc -y;
                        FastDrawHLine_R(LCD_MEM, x1, x2, y1, A_NORMAL);
                } else {
                        FastDrawLine_R(LCD_MEM, x1, y1, x2, y1, A_NORMAL);
                        y1 = yc - y;
                        FastDrawLine_R(LCD_MEM, x1, y1, x2, y1, A_NORMAL);
                }
                if(d + y > 0) {
                        y--;
                        d -= (y << 1) - 1;
                }
                if(x > d) {
                        x++;
                        d += (x << 1) + 1;
                }
        }
}
*/

/*
void __attribute__((__regparm__)) clip_fcircle(int xc, int yc, int r) {        // clipped filled circle
        int x = 0, y = r, d = 2 * (1 - r);
        int x1, y1, x2;
        while (y >= 0) {
                x1 = xc - x;
                x2 = xc + x;
                y1 = yc + y;
                x1 = (x1 < 0) ? 0 : x1;
                x1 = (x1 > 159) ? 159 : x1;
                x2 = (x2 < 0) ? 0 : x2;
                x2 = (x2 > 159) ? 159 : x2;
                if ((x2 < 159) && ((x2 - x1) > 16)) {
                        if ((y1 >= 0) && (y1 < 100)) {
                                FastDrawHLine_R(LCD_MEM, x1, x2, y1, A_NORMAL);
                        }
                        y1 = yc -y;
                        if ((y1 >= 0) && (y1 < 100)) {
                                FastDrawHLine_R(LCD_MEM, x1, x2, y1, A_NORMAL);
                        }
                } else {
                        if ((y1 >= 0) && (y1 < 100)) {
                                FastDrawLine_R(LCD_MEM, x1, y1, x2, y1, A_NORMAL);
                        }
                        y1 = yc - y;
                        if ((y1 >= 0) && (y1 < 100)) {
                                FastDrawLine_R(LCD_MEM, x1, y1, x2, y1, A_NORMAL);
                        }
                }
                if(d + y > 0) {
                        y--;
                        d -= (y << 1) - 1;
                }
                if(x > d) {
                        x++;
                        d += (x << 1) + 1;
                }
        }
}
*/




/*
unsigned long reverselongword(register unsigned long val asm("%d0"));

asm("
masks:
.long 0x55555555
.long 0x33333333
.long 0x0F0F0F0F
.long 0x00FF00FF
|.long 0x0000FFFF


reverselongword:
|lea      masks+20(%pc),%a0
lea      masks+16(%pc),%a0

| 4, shift count = 16.
move.l   %d0,%d1 | 4
|and.l    -(%a0),%d0
|swap     %d0
swap     %d0 | 4
clr.w    %d0 | 4
clr.w    %d1 | 4
swap     %d1 | 4
|and.l    (%a0),%d1
or.l     %d1,%d0 |8

| 3, shift count = 8.
move.l   %d0,%d1 | 4
and.l    -(%a0),%d0 | 20
lsl.l    #8,%d0 | 24
lsr.l    #8,%d1 | 24
and.l    (%a0),%d1 | 18
or.l     %d1,%d0 | 8

| 2, shift count = 4.
move.l   %d0,%d1 | 4
and.l    -(%a0),%d0 | 20
lsl.l    #4,%d0 | 16
lsr.l    #4,%d1 | 16
and.l    (%a0),%d1 | 18
or.l     %d1,%d0  | 8

| 1, shift count = 2.
move.l   %d0,%d1 | 4
and.l    -(%a0),%d0 | 20
lsl.l    #2,%d0 | 12
lsr.l    #2,%d1 | 12
and.l    (%a0),%d1 | 18
or.l     %d1,%d0 | 8

| 0, shift count = 1.
move.l   %d0,%d1 | 4
and.l    -(%a0),%d0 | 20
add.l    %d0,%d0 | 8
lsr.l    #1,%d1 | 10
and.l    (%a0),%d1 | 18
or.l     %d1,%d0 | 8

rts
");
*/

/*
static unsigned long masks[5] = {
0x55555555UL,
0x33333333UL,
0x0F0F0F0FUL,
0x00FF00FFUL,
0x0000FFFFUL};

unsigned long reverselongword(register unsigned long val asm("%d0"))
{
	register unsigned long i = val;
	register unsigned long j = 16;
	register unsigned long k = 4;

	while(j) {
		i = ((i&masks[k])<<j)|((i>>j)&masks[k]);
		j >>= 1;
		k--;
	}
	return(i);
}
*/



extern void Scale1Plane240to160_R(register void *src asm("%a0"),register void *dest asm("%a1"));
extern void Scale1Plane160to240_R(register void *src asm("%a0"),register void *dest asm("%a1"));
extern unsigned short sc1p160x240_t[256];

extern void screen_stretch(void *dst asm("%a0"), const void *src asm("%a1"));

// Le résultat de 160->240->160 est meilleur, mais le résultat de 240->160->240 est moins bon.
// Fait grosses strings.
//unsigned char t[4] = {0b000,0b011,0b110,0b111};
// Le résultat de 160->240->160 est moins bon, mais le résultat de 240->160->240 est meilleur.
// Fait strings coupées...
////unsigned char t[4] = {0b000,0b001,0b100,0b111};
/*
void gen_table(void) {
    unsigned short i = 0, res = 0;
    unsigned short *ptr = sc1p160x240_t;
    for (i = 0; i < 256; i++) {
        res = t[(i>>6)&3];
        res <<= 3;
        res |= t[(i>>4)&3];
        res <<= 3;
        res |= t[(i>>2)&3];
        res <<= 3;
        res |= t[(i>>0)&3];
        *ptr++ = res << 4;
    }
}
*/

/*
typedef struct scoord {
    short x_new;
    short y_new;
    short padding;
} scoord;
struct scoord a = {8,0,7};
struct scoord *p = &a;
*/

//#include "splash.h"

//unsigned char m[13][20];

// Original one.
#define BOUNDS_COLLIDE2HORIG(x0,y0,x1,y1,w,h0,h1) \
   (((x0+w)>x1) && ((x1+w)>x0) && ((y0+h0)>y1) && ((y1+h1)>y0))

// Better than ORIG.
#define BOUNDS_COLLIDE2HMOD(x0,y0,x1,y1,w,h0,h1) \
   (((EXT_SHORTABS((x1)-(x0)))<(w)) && ((y0+h0)>y1) && ((y1+h1)>y0))

// Slightly worse than MOD.
#define BOUNDS_COLLIDE2HMOD2(x0,y0,x1,y1,w,h0,h1) \
   (((EXT_SHORTABS((x1)-(x0)))<(w)) && ((EXT_SHORTABS((y1)-(y0)))<(h0) && (EXT_SHORTABS((y1)-(y0)))<(h1)))

// The best one (speed-wise, as far from MOD2 as MOD2 is far from ORIG). Is it possible to do better ?
#define BOUNDS_COLLIDE2HMOD3(x0,y0,x1,y1,w,h0,h1) \
   (((EXT_SHORTABS((x1)-(x0)))<(w)) && ((EXT_SHORTABS((y1)-(y0)))<(min((h0),(h1)))))

//extern void UpsideDownGrayClipSprite16_MASK_R(register short x asm("%d0"),register short y asm("%d1"),register short h asm("%d2"),unsigned short *sprt0,unsigned short *sprt1,unsigned short *mask0,unsigned short *mask1,register void *dest0 asm("%a0"),register void *dest1 asm("%a1")) __attribute__((__stkparm__));

/*
PixCollide8:
        sub.w %d0,%d1
        blt pc8_rts
        moveq #7,%d0
        sub.w %d1,%d0
        blt pc8_rts
        sub.w %d3,%d2
        blt pc8_rts
        cmp.w %d4,%d2
        bge pc8_rts
        btst.b %d0,(%a0, %d1.w)
        seq.b %d0
        rts
pc8_rts:
        clr.b  d0
*/
/*
     short PixCollide8(register short x0 asm("%d1")   ,
register short y0 asm("%d0")   , register short x1
asm("%d2")   , register short y1 asm("%d3")   ,
register short height asm("%d4")   , register unsigned
char* data1 asm("%a0")
)__attribute__((__regparm__(6)));
PixCollide8:
sub.w %d2,%d1
blt pc8_rts
moveq #7,%d2
sub.w %d1,%d2
blt pc8_rts
sub.w %d3,%d0
blt pc8_rts
cmp.w %d4,%d0
bge pc8_rts
btst.b %d2,(%a0, %d0.w)
sne.b %d0
ext.w %d0
rts
pc8_rts:
clr.w %d0
rts
*/

/*
// fait bien un zoom, mais utilise un scaling d'un facteur
// fixed-point donné. Pas grand chose à en tirer.
genlib::do_zoom			EQU	genlib@0025
// C'est la même fonction.
// C'est probablement lent (huit appels à une sous-fonction qui refait tout
// à chaque fois)...
void gl_draw_circle (short x, short y, short radius, short color)
genlib::draw_circle		EQU	genlib@004B
void gl_draw_clipped_circle (short x, short y, short radius, short color)
genlib::draw_clipped_circle	EQU	genlib@004C

// C'est la même fonction.
// Fonction de dessin de lignes horizontales en callback.
// L'algorithme semble classique. Peut-être qu'un "DrawMultiHLines"
// resterait la meilleure solution ?
void gl_draw_disk (short x, short y, short radius, short color)
genlib::draw_disk		EQU	genlib@0060
void gl_draw_clipped_disk (short x, short y, short radius, short color)
genlib::draw_clipped_disk	EQU	genlib@0061
genlib::render_disk		EQU	genlib@0063

genlib::draw_face		EQU	genlib@0029
genlib::draw_c_face		EQU	genlib@002A
genlib::draw_clipped_face	EQU	genlib@004E
genlib::draw_clipped_c_face	EQU	genlib@004F
genlib::render_triangle		EQU	genlib@005F

‘Input’
d0.w = x1 = X real coordinate of Point 1.
d1.w = y1 = Y real coordinate of Point 1.
d2.w = x2 = X real coordinate of Point 2.
d3.w = y2 = Y real coordinate of Point 2.
‘Output’
d0.w = New X coordinate of Point 1
d1.w = New Y coordinate of Point 1
d2.w = New X coordinate of Point 2
d3.w = New Y coordinate of Point 2
d4.w == 0 iff the line is outside the screen (can’t draw it).
‘Destroy’ d0-d4
‘Description’
It clips the line from Point 1 to Point 2. In asm, you pass directly the coordinates,
whereas in C, you pass the address of the coordinates (It is due to the fact that
C can’t return more than one argument).
‘See also’ gl_draw_clipped_line.
genlib::clip_line		EQU	genlib@0050
genlib::draw_line		EQU	genlib@0051
genlib::draw_clipped_line	EQU	genlib@0052

genlib::draw_bwhline_b		EQU	genlib@0059
genlib::draw_bwhline_w		EQU	genlib@005A
genlib::draw_hline_w		EQU	genlib@005B
genlib::draw_hline_lg		EQU	genlib@005C
genlib::draw_hline_dg		EQU	genlib@005D
genlib::draw_hline_b		EQU	genlib@005E
genlib::draw_hline_light	EQU	genlib@0064
genlib::draw_hline_shadow	EQU	genlib@0068
*/


/*
unsigned short fond_0[] = {0x50D2,0x2109,0xD42C,0x08F1,0x9E31,0x5183,0x2354,0xA331,0x0686,0x684D,0x8850,0x4CD7,0xD108,0xF187,0xC358,0x8424};
unsigned short fond_1[] = {0x2F09,0xDE36,0x08D3,0x370E,0x61CE,0x2E7C,0xDC28,0x1CCE,0xF879,0x91B0,0x73A3,0xB308,0x2237,0x0E78,0x3C27,0x78DB};

unsigned long animations_0[1][5][32] =
{
{
{0x00000000,0x00000000,0x00000000,0x08620000,0x04350000,0x05770000,0x3DF70000,0x1AEA0000,0x051C0000,0x03FC0000,0x01FE0000,0x03FF0000,0x004A0000,0x27FF0000,0x1FF60000,0x07C80000,0x03F00000,0x01600000,0x02300000,0x02700000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x00000000,0x08C60000,0x086B0000,0x08EF0000,0x3BEF0000,0x1DD60000,0x02380000,0x03FC0000,0x01FE0000,0x03FF0000,0x004A0000,0x27FF0000,0x1FF60000,0x07C80000,0x03F00000,0x01600000,0x02300000,0x02700000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x00000000,0x00860000,0x00D30000,0x00D70000,0x37DF0000,0x1BAE0000,0x04700000,0x03FC0000,0x01FE0000,0x03FF0000,0x004A0000,0x27FF0000,0x1FF60000,0x07C80000,0x03F00000,0x01600000,0x02300000,0x02700000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x00000000,0x010C0000,0x01A60000,0x01AE0000,0x2FBE0000,0x175C0000,0x08E00000,0x03FC0000,0x01FE0000,0x03FF0000,0x004A0000,0x27FF0000,0x1FF60000,0x07C80000,0x03F00000,0x01600000,0x02300000,0x02700000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x00000000,0x04300000,0x021A0000,0x02BA0000,0x1EFA0000,0x0D760000,0x038E0000,0x03FC0000,0x01FE0000,0x03FF0000,0x004A0000,0x27FF0000,0x1FF60000,0x07C80000,0x03F00000,0x01600000,0x02300000,0x02700000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000}
}
};

unsigned long animations_1[1][5][32] =
{
{
{0x00000000,0x00000000,0x18E60000,0x2DFF0000,0x2F7F0000,0x3FFF0000,0x3FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x13FE0000,0x27FF0000,0x2FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x03F00000,0x01E00000,0x02F00000,0x03F00000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x19CE0000,0x3FFF0000,0x1CFF0000,0x3FFF0000,0x3FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x13FE0000,0x27FF0000,0x2FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x03F00000,0x01E00000,0x02F00000,0x03F00000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x1B8E0000,0x3DFF0000,0x19FF0000,0x3FFF0000,0x3FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x13FE0000,0x27FF0000,0x2FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x03F00000,0x01E00000,0x02F00000,0x03F00000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x171C0000,0x2BFE0000,0x33EF0000,0x37FF0000,0x3FFF0000,0x3FFE0000,0x1FFC0000,0x0FFC0000,0x13FE0000,0x27FF0000,0x2FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x03F00000,0x01E00000,0x02F00000,0x03F00000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
{0x00000000,0x00000000,0x0C720000,0x17FF0000,0x27BF0000,0x2FFF0000,0x3FFF0000,0x1FFF0000,0x0FFE0000,0x0FFC0000,0x13FE0000,0x27FF0000,0x2FFF0000,0x3FFF0000,0x1FFE0000,0x0FFC0000,0x03F00000,0x01E00000,0x02F00000,0x03F00000,0x01E00000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000}
}
};

unsigned long animations_mask[1][5][32] =
{
{
{0xFFFFFFFF,0xE719FFFF,0xC2007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xC000FFFF,0x8000FFFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xE001FFFF,0xE003FFFF,0xFC0FFFFF,0xF807FFFF,0xF807FFFF,0xFC07FFFF,0xFC0FFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
{0xFFFFFFFF,0xE719FFFF,0xC2007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xC000FFFF,0x8000FFFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xE001FFFF,0xE003FFFF,0xFC0FFFFF,0xF807FFFF,0xF807FFFF,0xFC07FFFF,0xFC0FFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
{0xFFFFFFFF,0xE719FFFF,0xC2007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xC000FFFF,0x8000FFFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xE001FFFF,0xE003FFFF,0xFC0FFFFF,0xF807FFFF,0xF807FFFF,0xFC07FFFF,0xFC0FFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
{0xFFFFFFFF,0xE719FFFF,0xC2007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xC000FFFF,0x8000FFFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xE001FFFF,0xE003FFFF,0xFC0FFFFF,0xF807FFFF,0xF807FFFF,0xFC07FFFF,0xFC0FFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
{0xFFFFFFFF,0xE719FFFF,0xC2007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xC000FFFF,0x8000FFFF,0x80007FFF,0x80007FFF,0x80007FFF,0xC000FFFF,0xE001FFFF,0xE003FFFF,0xFC0FFFFF,0xF807FFFF,0xF807FFFF,0xFC07FFFF,0xFC0FFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF}
}
};
*/



// Main Function
void _main(void) {
    register short i = 0, j = 0, k = 0, l = 0;

//    unsigned short x1, y1, x2, y2;
    unsigned short t1 = 0, t2 = 0;
//    void *p;

//LCD_BUFFER lcd,lcd2;
//    SCR_RECT s;
//    WIN_RECT w;
    INT_HANDLER s5;

//printf("%c",!!BOUNDS_COLLIDE(m[0][6]+18,m[0][7]+3,m[1][4]+22,m[4][8]+14,(short)m[0][8]+32,(short)m[11][13]+14)+'0');
//printf("%c",!!BOUNDS_COLLIDEMOD(m[0][6]+18,m[0][7]+3,m[1][4]+22,m[4][8]+14,(short)m[0][8]+32,(short)m[11][13]+14)+'0');
//printf("%c",!!BOUNDS_COLLIDE2H(m[0][6]+18,m[0][7]+3,m[1][4]+22,m[4][8]+14,(short)m[0][8]+32,(short)m[11][13]+14,(short)m[11][13]+14)+'0');
//printf("%c",!!BOUNDS_COLLIDE2HMOD(m[0][6]+18,m[0][7]+3,m[1][4]+22,m[4][8]+14,(short)m[0][8]+32,(short)m[11][13]+14,(short)m[11][13]+14)+'0');
//printf("%c",!!BOUNDS_COLLIDE2HMOD2(m[0][6]+18,m[0][7]+3,m[1][4]+22,m[4][8]+14,m[0][8]+32,m[11][13]+14,m[11][13]+14)+'0');
//printf("%c",!!BOUNDS_COLLIDE2HMOD3(m[0][6]+18,m[0][7]+3,m[1][4]+22,m[4][8]+14,m[0][8]+32,m[11][13]+14,m[11][13]+14)+'0');

// TestCollide82h_R(x0,y0,x1,y1,h0,h1,s0,s1)
//printf("%c\n",!!TestCollide82h_R(0,0,8,0,11,8,sprite3_8,sprite3_8)+'0'); // NO (1 strict bottom-right of 0).
//printf("%c\n",!!TestCollide82h_R(8,0,0,0,10,8,sprite3_8,sprite3_8)+'0'); // NO (0 strict bottom-right of 1).
//printf("%c\n",!!TestCollide82h_R(0,8,8,0,9,8,sprite3_8,sprite3_8)+'0'); // NO (1 strict top-right of 0).
//printf("%c\n",!!TestCollide82h_R(8,0,0,8,10,8,sprite3_8,sprite3_8)+'0'); // NO (0 strict top-right of 1).

//printf("%c\n",!!TestCollide82h_R(0,0,7,6,5,8,sprite3_8,sprite3_8)+'0'); // NO (h0 too low).
//printf("%c\n",!!TestCollide82h_R(0,5,7,0,8,5,sprite3_8,sprite3_8)+'0'); // NO (h1 too low).

//printf("%c\n",!!TestCollide82h_R(1,1,8,3,11,5,sprite3_8,sprite3_8)+'0'); // YES (y1 > y0, y1+h1 <= y0+h0).
//printf("%c\n",!!TestCollide82h_R(8,3,7,2,4,9,sprite3_8,sprite3_8)+'0'); // YES (y1 <= y0, y1+h1 >= y0+h0).

//printf("%c\n",!!TestCollide82h_R(1,1,7,3,4,4,sprite3_8,sprite3_8)+'0'); // YES (y1 > y0, y1+h1 < y0+h0).
//printf("%c\n",!!TestCollide82h_R(1,3,7,1,4,3,sprite3_8,sprite3_8)+'0'); // YES (y1 <= y0, y1+h1 < y0+h0).

//printf("%c\n",!!TestCollide82h_R(0,0,7,1,9,8,sprite3_8,sprite3_8)+'0'); // YES.
//ngetchx();

//printf("%c\n",!!TestCollide82h_R(3,107,10,107,4,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');
//printf("%c\n",!!TestCollide8_R(3,107,10,107,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');

//printf("%c\n",!!TestCollide82h_R(105,103,111,104,4,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');
//printf("%c\n",!!TestCollide8_R(105,103,111,104,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');

//printf("%c\n",!!TestCollide82h_R(173,1,171,2,4,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');
//printf("%c\n",!!TestCollide8_R(173,1,171,2,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');

//printf("%c\n",!!TestCollide82h_R(102,59,102,60,4,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');
//printf("%c\n",!!TestCollide8_R(102,59,102,60,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');

//printf("%c\n",!!TestCollide82h_R(78,115,85,113,4,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');
//printf("%c\n",!!TestCollide8_R(78,115,85,113,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01}))+'0');
/*
srand(0);
for(i = 0; i < 65000; i++) {
    x1 = random(239-8);
    x2 = random(239-8);
    y1 = random(127-8);
    y2 = random(127-8);
    if (    (!!TestCollide82h_R(x1,y1,x2,y2,4,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01})))
         != (!!TestCollide8_R(x1,y1,x2,y2,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01})))) {
       printf_xy(0,10,"%hu %hu %hu %hu %hu",i,x1,y1,x2,y2);
       ngetchx();
       asm("illegal");
    }
}
*/
/*
srand(0);
for(i = 0; i < 65000; i++) {
    x1 = random(239-16);
    x2 = random(239-16);
    y1 = random(127-16);
    y2 = random(127-16);
    if (    (!!TestCollide162h_R(x1,y1,x2,y2,16,16,sprite_16,sprite2_16))
         != (!!TestCollide16_R(x1,y1,x2,y2,16,sprite_16,sprite2_16))) {
       printf_xy(0,10,"%hu %hu %hu %hu %hu",i,x1,y1,x2,y2);
       ngetchx();
       asm("illegal");
    }
}
*/

/*
GrayOn();

FillScreenWithGarbage_R(1234567891,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
FillScreenWithGarbage_R(1987654321,LCD_SIZE,GrayGetPlane(DARK_PLANE));
UpsideDownGrayClipSprite16_MASK_R(1,1,16,sprite_16,sprite_16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
ngetchx();
GrayOff();
*/
/*
GrayOn();

FillScreenWithGarbage_R(1234567891,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
FillScreenWithGarbage_R(1987654321,LCD_SIZE,GrayGetPlane(DARK_PLANE));
//ClipSpriteX8_AND_R(1,1,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(LIGHT_PLANE));
ClipSpriteX8_AND_R(1,1,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(DARK_PLANE));
ClipSpriteX8_AND_R(5,5,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(LIGHT_PLANE));
//ClipSpriteX8_AND_R(5,5,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(DARK_PLANE));
ngetchx();
ClipSpriteX8_OR_R(1,1,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(DARK_PLANE));
ClipSpriteX8_OR_R(5,5,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(LIGHT_PLANE));
ngetchx();
ClipSpriteX8_XOR_R(1,1,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(DARK_PLANE));
ClipSpriteX8_XOR_R(5,5,64,64/8,(unsigned char *)tictlogo64,GrayGetPlane(LIGHT_PLANE));
ngetchx();
GrayOff();
*/
/*
OSFastArrows = 2;
for (i = 0; i < 64; i++) {
    SpriteX8Get_R(i,0,21,LCD_MEM,(unsigned char *)dest_64,9);
    FastFillRect_R(LCD_MEM,i,0,i+9*8-1,20,A_NORMAL);
//    SpriteX8_MASK_R(i,0,21,(unsigned char *)dest_64,(unsigned char *)dest_64,9,LCD_MEM);
//    SpriteX8_AND_R(i,0,21,(unsigned char *)dest_64,9,LCD_MEM);
//    SpriteX8_BLIT_R(i,0,21,(unsigned char *)dest_64,(unsigned char *)0x400,9,LCD_MEM);

//    SpriteX8_XOR_R(i,0,21,(unsigned char *)dest_64,1,LCD_MEM);
    ClipSpriteX8_OR_R(i,0,21,9,(unsigned char *)dest_64,LCD_MEM);
//    SpriteX8_OR_R(i,0,21,(unsigned char *)dest_64,1,LCD_MEM);
    ngetchx();
}
*/
/*
OSFastArrows = 2;
for (i = -64; i < 64; i++) {
    ClipSpriteX8_OR_R(i,i,64,8,(unsigned char *)tictlogo64,LCD_MEM);
}
ngetchx();
exit(0);
*/
/*
OSFastArrows = 2;
for (i = -64; i < 64; i++) {
    ClipSpriteX8_OR_R(i+240,i,64,8,(unsigned char *)tictlogo64,LCD_MEM);
}
ngetchx();
exit(0);
*/

// The TICT logo is not defined properly: the size of an interlaced chunk
// is 3*8 bytes instead of 3*2 bytes...
/*
GrayOn();
FillScreenWithGarbage_R(1234567891,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
FillScreenWithGarbage_R(1987654321,LCD_SIZE,GrayGetPlane(DARK_PLANE));
for (i = -64; i < 240 + 64; i++) {
    GrayClipISpriteX16_MASK_R(i,1,64,(unsigned short *)mtictlogo64,4,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
}
ngetchx();
GrayOff();
*/
/*
if (!GrayOn()) exit(1);
//FillScreenWithGarbage_R(1234567891,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
//FillScreenWithGarbage_R(1987654321,LCD_SIZE,GrayGetPlane(DARK_PLANE));
//GrayFillScreen_R(0x00000000,0x00000000); // Fill screen white.
//GrayFillScreen_R(0xFFFFFFFF,0x00000000); // Fill screen light gray.
//GrayFillScreen_R(0x00000000,0xFFFFFFFF); // Fill screen dark gray.
GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF); // Fill screen black.
GrayClipISprite16_TRANW_R(1,1,16,isprite2_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GrayClipISprite16_TRANL_R(17,17,16,isprite2_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GrayClipISprite16_TRAND_R(33,33,16,isprite2_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GrayClipISprite16_TRANB_R(49,49,16,isprite2_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GrayClipISprite16_RPLC_R(65,65,16,isprite2_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
ngetchx();
GrayOff();
exit(0);
*/
/*
static unsigned char titre_0[] = {0x1F,0xFF,0xFC,0x00,0x6F,0xF9,0xBF,0x85,0xFF,0xC1,0x00,0x3F,0xFF,0xFC,0x44,0x06,0x29,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0x40,0x17,0xFC,0xDD,0x83,0xF4,0x90,0x80,0xBF,0xDF,0xE8,0x38,0x0C,0x11,0xFF,0xFF,0xFF,0x81,0xFF,0xFF,0x90,0x09,0xFF,0x69,0xE0,0xFC,0xC0,0x01,0x74,0xB7,0xD0,0x40,0x98,0xB1,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFD,0xFF,0xFF,0xE1,0xF1,0xF3,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x50,0xA0,0x00,0x00,0x22,0x80,0x22,0xA7,0x23,0x93,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x20,0x50,0xA0,0x00,0x00,0x22,0x80,0x76,0x3B,0x25,0x93,0xFF,0xFF,0xFF,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x20,0x00,0x00,0x00,0x80,0x16,0xA0,0x88,0xE7,0xFF,0xFF,0xFF,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x20,0x00,0x00,0x00,0x80,0x3F,0xF0,0x89,0x36,0xFF,0xFF,0xFF,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x00,0x00,0x01,0x00,0x40,0x71,0x1B,0xC6,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x00,0x00,0x01,0x00,0x80,0xF0,0x3E,0x84,0xFF,0xFF,0xFF,0xF0,0x3F,0x00,0x18,0x02,0x00,0x60,0xF0,0x60,0x08,0xC6,0x21,0x07,0x80,0xC2,0x7C,0x9E,0xFF,0xFF,0xFF,0xF0,0x17,0x00,0x00,0x02,0x00,0x00,0x00,0x40,0x08,0x42,0x00,0x01,0x00,0x88,0x73,0x3E,0xFF,0xFF,0xFF,0xF8,0x09,0x80,0x0C,0x00,0x00,0x20,0x00,0x70,0x00,0x42,0x00,0x02,0x00,0x10,0x37,0x7F,0xFF,0xFF,0xFF,0xFC,0x07,0x40,0x18,0x80,0x00,0x60,0x00,0x62,0x00,0x42,0x00,0x04,0x00,0x10,0x34,0x7F,0xFF,0xFF,0xFF,0xFE,0x02,0xB0,0xEE,0x00,0x0F,0xE0,0x00,0x78,0x00,0x42,0x00,0x08,0x00,0xA0,0x08,0x7F,0xFF,0xFF,0xFF,0xFF,0x01,0x30,0x98,0x00,0x19,0x20,0x00,0x60,0x00,0x42,0x00,0x10,0x00,0xE8,0x46,0x7F,0xFF,0xFF,0xFF,0xFF,0x80,0xF0,0xB0,0xC0,0x1C,0x60,0x00,0x43,0x00,0x42,0x00,0x30,0x94,0x78,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x50,0xA2,0x00,0x14,0xA0,0xF0,0x08,0x00,0x42,0x00,0x30,0xDE,0x31,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x30,0xA0,0x40,0x17,0xA0,0x90,0x01,0x00,0x42,0x00,0x10,0x7F,0xC2,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x30,0xA0,0x00,0x10,0x20,0x90,0x00,0x00,0x00,0x00,0x08,0x7F,0x05,0xFF,0xFF,0xFF,0xEF,0xFF,0xF0,0x00,0x10,0xA0,0x00,0x10,0x20,0x90,0x00,0x00,0x00,0x00,0x04,0xFD,0x0B,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x50,0xB0,0x00,0x1E,0x20,0xD0,0x40,0x04,0x00,0x01,0x03,0x32,0x17,0x7F,0xFF,0xFF,0xAB,0xFF,0xC0,0x00,0x98,0x90,0x01,0x17,0xE0,0xF0,0x40,0x04,0x00,0x11,0x82,0x1E,0x0E,0x3F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x18,0x98,0x31,0x1F,0xF0,0xF0,0x60,0xC6,0x08,0x31,0xC1,0x19,0x14,0x2F,0xFF,0xFF,0xEF,0xFF,0xE0,0x00,0x37,0x0F,0xFF,0xF0,0xF0,0x90,0xFF,0xFF,0xFF,0xFF,0x7F,0x03,0x08,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xD6,0x15,0xC0,0x7F,0xF9,0x83,0x05,0x02,0x00,0x03,0x05,0x02,0x87,0xFF,0xFF,0xFF,0xFF,0xC7,0xFF,0xFD,0xFE,0x13,0x80,0x70,0x3B,0x03,0x08,0x83,0x00,0x03,0x08,0x83,0x9F,0xFF,0xFF,0xFF,0xFF,0x45,0xFF,0xF0,0x0F,0x00,0xF6,0x30,0x1E,0x03,0x86,0xC1,0x00,0x03,0x86,0xC1,0xFB,0xFF,0xFF,0xFF,0xFF,0xC7,0xF8,0x65,0x01,0x03,0xC8,0x30,0x06,0x03,0x87,0xC1,0x00,0x03,0x87,0xC1,0xA6,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xC0,0x01,0x01,0xFE,0x02,0x07,0x03,0x83,0xC0,0x00,0x03,0x83,0xC0,0xE1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x78,0x20,0x00,0x7E,0x03,0x02,0x07,0x06,0xC0,0x00,0x07,0x06,0xC0,0xE0,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0x1F,0x3D,0xA0,0x38,0x03,0x00,0x0F,0x03,0x80,0x00,0x0F,0x03,0x80,0xC1,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0x87,0xFB,0xF0,0x3E,0x02,0x00,0x7F,0x02,0x80,0x00,0x7F,0x07,0x07,0xC2,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0x84,0x00,0x36,0x06,0x00,0x7C,0x01,0x80,0x00,0x7C,0x02,0x03,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x30,0x29,0x1C,0x00,0x38,0x00,0xC0,0x00,0x38,0x02,0x03,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x20,0x88,0x01,0x10,0x00,0x38,0x00,0xC0,0x00,0x38,0x00,0x03,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xB1,0xF4,0x00,0x00,0x00,0x3A,0x01,0xF0,0x00,0x3A,0x00,0x03,0x41,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x80,0x50,0x00,0x38,0x01,0xBC,0x00,0x38,0x00,0x03,0x41,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xFE,0x00,0x30,0x00,0x30,0x03,0x0C,0x00,0x30,0x03,0x07,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF2,0x76,0x00,0x18,0x00,0x70,0x03,0x04,0x00,0x70,0x03,0x0F,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE4,0x7F,0x00,0x10,0x00,0x38,0x01,0x84,0x03,0xE0,0x41,0x40,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x89,0x7F,0x80,0x50,0x00,0x38,0x01,0x0C,0x01,0xF1,0xE3,0x30,0x17,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0x7F,0xC0,0x70,0x00,0x50,0x01,0x0C,0x00,0x00,0xD1,0x1B,0x0F,0xFF,0xFF,0xC7,0xFF,0xFF,0xFF,0xFF,0x81,0x07,0xC0,0x60,0x00,0x60,0x03,0x38,0x00,0x00,0xE9,0x17,0xFF,0xEF,0xFF,0x45,0xFF,0xFF,0xFF,0xFF,0xF8,0x01,0xE0,0x40,0x00,0xE0,0x03,0xD0,0x00,0x01,0xFF,0x0C,0xFF,0xFF,0xFF,0xC7,0xFF,0xFF,0x87,0xFF,0xFF,0x80,0x77,0xC0,0x0F,0xC2,0x2B,0x80,0x00,0x20,0xFF,0x8E,0xFF,0xAB,0xFF,0xFF,0xFF,0xFF,0xB0,0xFF,0xFF,0xC0,0xDF,0xC0,0x0F,0x04,0x48,0x00,0x00,0x60,0x7F,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xD9,0x7F,0xFF,0xC0,0xFF,0x80,0x00,0x04,0x9C,0x00,0x00,0x01,0x6F,0xFF,0xFF,0xEF,0xFF,0xEF,0xFF,0xFF,0xEC,0x3F,0xFF,0xFF,0x81,0x40,0x00,0x09,0x0E,0x00,0x00,0x07,0x29,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF6,0x2F,0xFF,0xFF,0xC3,0x30,0x00,0x0A,0x07,0x00,0x00,0x03,0x11,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0x17,0xFF,0xFF,0xC0,0x38,0x00,0x94,0x0F,0x00,0x00,0x03,0xB1,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xED,0x83,0xFF,0xFF,0xE1,0xFC,0x01,0x28,0x03,0x00,0x00,0x03,0xF3,0xFF,0xF9,0xE0,0xFF,0xFF,0xFF,0xFF,0xFE,0xC1,0xFF,0xFF,0xFF,0x0C,0x01,0x50,0x03,0x00,0x00,0x03,0x93,0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xAB,0x61,0x7F,0xFF,0xF8,0xE0,0x22,0xA0,0x03,0x00,0x00,0x03,0x93,0xFF,0xFE,0x98,0xFF,0xFF,0xFF,0xFF,0xFF,0xB0,0x3F,0xFF,0xF8,0x0F,0x11,0x40,0x03,0x00,0x00,0x07,0xE7,0xFF,0x5F,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0x98,0x2F,0xFE,0x00,0xFF,0xA2,0x80,0x0E,0x00,0x00,0x0F,0x36,0xFB,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9C,0x06,0x00,0x0F,0xFF,0x2D,0x01,0x1C,0x00,0x00,0x00,0x1F,0xFC,0x55,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0x8E,0x01,0x00,0xFF,0xFE,0x92,0x00,0xFC,0x00,0x00,0x00,0x87,0xFF,0xCC,0x4F,0xFF,0xFF,0xFF,0xFF,0xFF,0x87,0x5E,0x8F,0xFF,0xFC,0x26,0x00,0x40,0x00,0x00,0x00,0x9F,0xFF,0xF0,0x0B,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xAF,0x7F,0xFF,0xF0,0x4E,0x00,0xE0,0x00,0x00,0x00,0xFB,0xFF,0xFD,0x83,0xFF,0xFF,0xFF,0xFF,0xFF,0xC1,0xD7,0x8F,0xFF,0x80,0x9E,0x00,0x74,0x00,0x00,0x00,0xA6,0xFF,0xFE,0x31,0x3F,0xFF,0xFF,0xFF,0xFF,0xE0,0xEB,0x33,0xFE,0x01,0x3F,0x40,0x7C,0x00,0x00,0x60,0xE1,0xFF,0xFF,0xC7,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x74,0x84,0x80,0x0E,0x7F,0x40,0x30,0x40,0x00,0xF0,0xE0,0xFF,0xFF,0xFD,0xF3,0xFF,0xFF,0xFF,0xFF,0xE0,0x3B,0x01,0x00,0x06,0xFF,0x30,0x00,0x80,0x00,0x6D,0xC1,0xFF,0xFF,0xFF,0xBE,0x7F,0xFF,0xFF,0xFF,0xF0,0x1E,0x40,0x17,0xCA,0xFF,0xB0,0x01,0x00,0xA1,0x51,0xF8,0x7F,0xFF,0xFF,0x87,0x1F,0xFF,0xFF,0xFF,0xF8,0x0F,0x90,0x5F,0xE3,0xFF,0x98,0x12,0x00,0x01,0x47,0xF0,0xBF,0xFF,0xFF,0xF1,0xC7,0xFF,0xFF,0xFF,0xFC,0x00,0xE1,0x7F,0xF3,0xFF,0x9C,0x25,0x02,0x04,0x4E,0xFD,0xCF,0xFF,0xFF,0xFE,0x6F,0xFF,0xFF,0xFF,0xFE,0x09,0x7F,0xFF,0xF8,0x0F,0xC3,0xE2,0x41,0x86,0xC3,0xFF,0xCB,0xFF,0xFF,0xFF,0xF3,0xFF,0xFF,0xFF,0xFF,0x10,0x80,0x00,0xF8,0x37,0xE7,0x84,0x00,0x73,0x62,0x7F,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xA5,0x00,0x41,0x38,0x9B,0xF1,0x09,0x80,0x23,0xC1,0xBF,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xAC,0x07,0xD8,0x28,0x4D,0xFE,0x30,0x00,0x01,0x20,0x9F,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xF8,0xE0,0x10,0xA6,0xFC,0x5E,0x80,0x07,0x9A,0xE7,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBD,0xFF,0x1B,0xA8,0xD2,0xF8,0xAC,0x8E,0x00,0xDF,0x1F,0xF2,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xB9,0xBB,0xED,0xDC,0xEC,0xF1,0x3C,0x07,0x00,0x7B,0x87,0xFD,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xB6,0x02,0xF6,0xEE,0xF6,0xC2,0x5D,0x11,0x82,0x7B,0x9F,0xFE,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xA8,0x00,0xFB,0x77,0x00,0x06,0xFD,0x80,0x81,0x38,0xFB,0x7F,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xA9,0xE1,0x7D,0xBB,0x80,0x0D,0xFA,0x9B,0xC0,0x92,0xA6,0x3F,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xF8,0xDE,0xD5,0xDE,0x1D,0xFA,0x93,0x80,0xC2,0xE1,0xFF,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0xBE,0x4F,0x6A,0xEE,0x3B,0xF8,0x0A,0x01,0xC1,0xE0,0xDF,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0xFF,0x0F,0xB7,0x77,0x5B,0xF8,0x0E,0x01,0xC0,0xC1,0x4B,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x07,0x8F,0xDB,0xBB,0xA9,0xF4,0x4A,0x03,0xC6,0x40,0x21,0xFD,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x18,0x0F,0x8F,0xED,0xDF,0xC3,0xF4,0x7E,0x17,0x84,0x30,0x98,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xB0,0x0F,0x8E,0xF6,0xED,0xC3,0xF4,0x75,0x07,0x9E,0x1B,0x58,0x7F,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x0F,0x8C,0x7B,0x65,0xC3,0xF6,0x01,0xFB,0x3E,0x17,0x7F,0x3F,0xCB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x03,0x1E,0x1D,0xA9,0xC7,0xE7,0x01,0x7C,0x7F,0x0C,0xB7,0x2F,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x07,0x1F,0xFE,0xC5,0xC7,0xE7,0x80,0xEC,0x7F,0x8E,0x6B,0x97,0xF8,0x7F,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x06,0x1F,0xFF,0x69,0xC7,0xEF,0xC0,0x60,0x7F,0xE7,0x97,0xC3,0xFD,0x3F,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x3E,0x7F,0xE7,0xAD,0xC7,0xEF,0xC0,0x80,0x7F,0xFF,0xBB,0x77,0xFE,0x2F,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x7C,0x38,0x2B,0xC5,0x87,0xCF,0xE0,0x07,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0xF0,0x10,0x0F,0xD1,0x87,0xCF,0xE3,0xBF,0xFF,0xFF,0xFF,0xBF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0x80,0x01,0x9F,0xC1,0xE5,0xC9,0x87,0xCF,0xE7,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xE7,0xFF,0xFF,0xEF,0xFF,0x00,0x03,0x8F,0xC7,0xF2,0x65,0x17,0xCF,0xFB,0xFF,0xFF,0xFF,0xFF,0xCB,0xFF,0xFB,0xFF,0xFF,0xFF,0xFE,0x00,0x07,0x87,0xDF,0xF8,0xA9,0x17,0x9F,0xF3,0xFF,0xFF,0xFF,0xFF,0xF1,0xFF,0xFD,0xFF,0xFF,0xAB,0xFC,0x00,0x1F,0xC3,0xBD,0xF8,0xA5,0x33,0x9F,0xF3,0xFF,0xFF,0xFF,0xFF,0xF8,0x7F,0xFE,0xFF,0xFF,0xFF,0xF8,0x00,0x3F,0xE1,0xB1,0xDC,0x30,0x43,0x9F,0xFB,0xFF,0xFF,0xFF,0xFF,0xFD,0x3F,0xFF,0xFF,0xFF,0xEF,0xF0,0x00,0x7F,0xF0,0xB0,0x1C,0x34,0x8D,0x9F,0xF7,0xFF,0xFF,0xFF,0xFF,0xFE,0x2F,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0xFF,0xF8,0x30,0x1E,0x31,0x1D,0x1F,0xF3,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0xFF,0xFC,0x70,0x16,0x35,0x19,0x1F,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0x80,0x01,0xFF,0xFF,0x60,0x1E,0x70,0x9A,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0x40,0x3E,0x70,0x77,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x07,0xFF,0xFF,0x80,0x3C,0x86,0xB7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x07,0xFF,0xFF,0x00,0x38,0x86,0x0B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x0F,0xFF,0xFF,0x00,0x73,0x1C,0x85,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x1F,0xFF,0xFE,0x01,0xC0,0x79,0xC2,0x8F,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xE0,0x00,0x3F,0xFF,0xFE,0x01,0xF0,0x23,0xE1,0x0F,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xE0,0x00,0x3F,0xFF,0xFC,0x03,0xFC,0x01,0xF0,0xB7,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x7F,0xFF,0xF8,0x03,0x7F,0xFC,0xF8,0x7B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0xFF,0xFF,0xF8,0x01,0xFF,0xFE,0x7C,0x3B,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xF0,0x02,0xFF,0xFF,0x3E,0x1D,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x01,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0x9F,0x0E,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0xE0,0x05,0xFF,0xFF,0xCF,0x87,0x7D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0xC0,0x03,0xFF,0xFF,0xE1,0xC3,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0xC0,0x0B,0xFF,0xFF,0xFC,0x71,0xBF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0x00,0x0F,0xFF,0xFF,0x80,0x0F,0xFF,0xFF,0xFF,0x00,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x0F,0xFF,0xFF,0x80,0x07,0xFF,0xFF,0xFF,0xF8,0x6F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x1F,0xFF,0xFF,0x00,0x17,0xFF,0xFF,0xFF,0xFC,0x37,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3F,0xFF,0xFF,0x00,0x1F,0xFF,0xFF,0xFF,0xFE,0x17,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3F,0xFF,0xFE,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x7F,0xFF,0xFE,0x00,0x2F,0xFF,0xFF,0xFF,0xFF,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x7F,0xFF,0xFE,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFC,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xFC,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xF8,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xF8,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xF8,0x00,0x5F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xF0,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xF0,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0xFF,0xFF,0xE0,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
static unsigned char titre_1[] = {0xFF,0xFF,0xFF,0x00,0x1F,0xFE,0x7E,0x03,0xF3,0x80,0x00,0x7F,0xFF,0xF8,0x38,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x0F,0xFF,0x3D,0x01,0xFB,0xC1,0x00,0x7F,0xFF,0xF0,0x40,0x00,0x6F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x07,0xFF,0x99,0x01,0xF9,0xF1,0x80,0xFB,0xCF,0xE0,0x00,0x00,0x4F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xD1,0xEF,0xFF,0xFF,0xFF,0xFD,0xFF,0xDD,0xC0,0x00,0x0F,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x21,0x90,0xC0,0x00,0x00,0x23,0x00,0x22,0x20,0xC0,0x6F,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x21,0x90,0xC0,0x00,0x00,0x23,0x00,0x76,0x24,0xC2,0x6F,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x21,0x90,0xC0,0x00,0x00,0x23,0x00,0xF6,0xBF,0x07,0x1E,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x21,0x90,0xC0,0x00,0x00,0x23,0x01,0xE9,0x7F,0x06,0x0F,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xE1,0xF0,0xFF,0xFF,0xFF,0xE3,0xFF,0xC0,0x3E,0x04,0x3F,0xFF,0xFF,0xFF,0xE0,0x7E,0x00,0x0C,0x06,0x20,0x21,0xF0,0xF0,0x18,0xC6,0x23,0x83,0x80,0x3E,0x00,0x7F,0xFF,0xFF,0xFF,0xF0,0x3F,0x00,0x18,0x02,0x00,0x61,0xF0,0xE0,0x08,0xC6,0x23,0x07,0x00,0x3C,0x00,0x7F,0xFF,0xFF,0xFF,0xF8,0x11,0x80,0x30,0x02,0x00,0xE0,0x00,0xC0,0x08,0xC6,0x22,0x0F,0x00,0x70,0x00,0xFF,0xFF,0xFF,0xFF,0xFC,0x08,0xF1,0xFF,0xE2,0x1F,0xE0,0x00,0xFF,0x88,0xC6,0x20,0x1E,0x00,0xE0,0x00,0xFF,0xFF,0xFF,0xFF,0xFE,0x04,0x71,0xFF,0x02,0x3F,0xE0,0x00,0xFC,0x08,0xC6,0x20,0x3C,0x00,0xE0,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0x31,0xFC,0x02,0x3F,0xA0,0x00,0xF0,0x08,0xC6,0x20,0x78,0x00,0x70,0x37,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,0xD1,0xB0,0x02,0x3E,0x21,0xF0,0xC0,0x08,0xC6,0x20,0xF0,0x00,0x70,0x39,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0xF1,0xA0,0x22,0x3F,0xA1,0xF0,0x80,0x88,0xC6,0x20,0x60,0x08,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x71,0xA1,0xE2,0x3F,0x61,0xF0,0x87,0x88,0xC6,0x20,0x20,0x0D,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x31,0xA3,0x82,0x30,0x61,0x90,0x8E,0x08,0xC6,0x20,0x10,0xBF,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x31,0xA0,0x02,0x30,0x21,0x90,0x80,0x08,0x00,0x22,0x08,0xFF,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x31,0xA0,0x02,0x30,0x21,0x90,0x80,0x08,0x00,0x23,0x04,0x7E,0x07,0xFF,0xFF,0xFF,0xEF,0xFF,0xE0,0x00,0x31,0x90,0x62,0x30,0x21,0x90,0xC1,0x8C,0x10,0x63,0x82,0x7C,0x0E,0xFF,0xFF,0xFF,0xC7,0xFF,0xC0,0x00,0x7F,0x9F,0xFF,0xF8,0x21,0x91,0xFF,0xFF,0xFF,0xFF,0xFF,0x18,0x1C,0x7F,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0x8F,0xFF,0xF0,0x1F,0x93,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x08,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x87,0xFE,0xE0,0x1F,0x97,0x9F,0x39,0xF7,0xCE,0x3E,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x1A,0x00,0x0F,0x0F,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xFE,0x00,0x0C,0x40,0x00,0x0E,0x00,0x07,0x00,0x00,0x00,0x07,0x00,0x0F,0xFF,0xBF,0xFF,0xBF,0x83,0xFF,0xFF,0xF0,0x0F,0xC8,0x00,0x04,0x00,0x0F,0x00,0x00,0x00,0x0F,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0x9E,0xFE,0x00,0xFE,0x00,0x00,0x00,0x0F,0x80,0x00,0x00,0x0F,0x80,0x41,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0x00,0x7E,0x00,0x3F,0x00,0x00,0x00,0x07,0x80,0x00,0x00,0x07,0x80,0x00,0x7F,0xFF,0xFF,0xFF,0xEF,0xFF,0x80,0x1F,0x00,0x1F,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x04,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x7F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFE,0x38,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x83,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x38,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x08,0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x03,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x80,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x83,0x80,0x07,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0xC1,0xC0,0x0F,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0xF0,0x80,0x00,0x00,0x00,0x20,0x00,0xF0,0x00,0x01,0xE3,0xE0,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0x00,0x00,0x00,0x00,0x60,0xC0,0x00,0x01,0xF7,0xF8,0xFF,0xFF,0xFF,0x83,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0xA0,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xEF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0x70,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xC7,0xFF,0xEF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x02,0xD0,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xEF,0xFF,0xEF,0xFF,0xFF,0xE4,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x09,0x80,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF2,0x7F,0xFF,0xFF,0xF6,0x00,0x00,0x13,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0x1F,0xFF,0xFF,0xFF,0xC0,0x00,0x26,0x00,0x00,0x00,0x00,0x6F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x8F,0xFF,0xFF,0xFF,0xC0,0x00,0x4C,0x00,0x00,0x00,0x00,0x4F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x47,0xFF,0xFF,0xFF,0xF8,0x00,0x98,0x00,0x00,0x00,0x00,0x0F,0xF3,0xFE,0x1F,0xFF,0xFF,0xFF,0xFF,0xEF,0x23,0xFF,0xFF,0xFF,0xF0,0x02,0x30,0x00,0x00,0x00,0x00,0x6F,0xFB,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xC7,0x90,0xFF,0xFF,0xFF,0x00,0x04,0x60,0x00,0x00,0x00,0x00,0x6F,0xFB,0x7F,0xE7,0xFF,0xFF,0xFF,0xFF,0xEF,0xC8,0x7F,0xFF,0xC0,0x07,0x88,0xC0,0x00,0x00,0x00,0x00,0x1E,0xFB,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE4,0x1F,0xF0,0x00,0x7F,0x91,0x80,0x00,0x00,0x00,0x00,0x0F,0xFF,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE2,0x0E,0x00,0x07,0xFF,0xC3,0x00,0x00,0x07,0x00,0x00,0x0F,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0x07,0x00,0x7F,0xFF,0x0F,0x00,0x00,0x0B,0x00,0x00,0x0F,0xFF,0xF0,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xE1,0x87,0xFF,0xFE,0x1F,0x00,0x00,0x16,0x00,0x00,0x0F,0xFF,0xFC,0x07,0xFF,0xFF,0xBF,0xFF,0xFF,0xFC,0x70,0xFF,0xFF,0xFC,0x3F,0x00,0x00,0x2C,0x00,0x00,0x07,0xFF,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x38,0x7F,0xFF,0xF0,0x7F,0x80,0x00,0x58,0x00,0x00,0x41,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1C,0xCF,0xFF,0x80,0xFF,0x80,0x00,0xB8,0x00,0x00,0x00,0xFF,0xFF,0xF8,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0x03,0xFF,0xC1,0xFF,0x80,0x01,0x30,0x00,0x00,0x00,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xC6,0x00,0xC0,0x21,0xFF,0xC0,0x02,0x60,0x00,0x90,0x00,0xFF,0xFF,0xFF,0xC1,0xFF,0xFF,0xFF,0xFF,0xFF,0xE1,0x81,0x0F,0xD1,0xFF,0xC0,0x04,0xC0,0x40,0x8C,0xF3,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x62,0x3F,0xE9,0xFF,0xE0,0x09,0x80,0xC0,0x0C,0xFF,0xFF,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x1C,0xFF,0xF5,0xFF,0xE0,0x13,0x01,0xC0,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0x97,0xFF,0xFF,0xFF,0xFF,0xF0,0x87,0xFF,0xFF,0xFF,0xFC,0x07,0x03,0xE0,0x07,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0x4F,0xF8,0x4E,0x83,0xE0,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x0A,0xFF,0x27,0xFF,0x9C,0x00,0x40,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xF8,0x25,0x1F,0x93,0xFF,0x19,0x00,0x00,0xC0,0x7F,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xFF,0x1F,0x8F,0x49,0xFE,0x3D,0x00,0x00,0x60,0x5F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0xFF,0xE7,0xC7,0x25,0xFC,0x7C,0x00,0x03,0x20,0x0F,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0xC7,0xF3,0xE3,0x13,0xF8,0xFC,0x00,0x03,0x80,0x0F,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xBF,0xFF,0xCF,0xF1,0xF9,0xF1,0x09,0xF1,0xF9,0x0E,0x01,0xC0,0x0F,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xDF,0xFC,0x7C,0xF8,0xFF,0xC1,0xF9,0x8F,0x00,0xE0,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDE,0x1E,0x3E,0x7C,0x41,0x03,0xF9,0x84,0x00,0x78,0x41,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x07,0x3F,0x3A,0x20,0x83,0xF9,0xCC,0x00,0x3C,0x00,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x01,0xBF,0x97,0x1F,0x47,0xF3,0x84,0x00,0x3E,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0xFF,0xCF,0x8F,0xA7,0xF3,0x80,0x00,0x3F,0x00,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x7D,0xE7,0xC7,0xD7,0xF3,0x84,0x00,0x3F,0x80,0x43,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x7C,0xF3,0xE3,0xFF,0xF3,0x80,0x00,0x7F,0xC0,0x51,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x7D,0x79,0xF3,0xFF,0xE3,0x8A,0x08,0x7F,0xE0,0x3C,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x7F,0xBC,0xFB,0xFF,0xE7,0xFE,0x04,0xFF,0xF8,0x9E,0x3F,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0xFF,0xFE,0x77,0xFF,0xE7,0xFE,0x03,0xFF,0xFF,0xDF,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0xFF,0xFF,0x3B,0xFF,0xE7,0xFF,0x13,0xFF,0xFF,0xF7,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x01,0xFF,0xFF,0x97,0xFF,0xC7,0xFF,0x9F,0xFF,0xFF,0xF9,0xF7,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x01,0xFE,0x1F,0xD3,0xFF,0xC7,0xFF,0x7F,0xFF,0xFF,0xFC,0xF9,0xFF,0x1F,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x03,0xFB,0xC7,0xFB,0xFF,0xC7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x0F,0xFF,0xF1,0xEF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x3F,0xFE,0x18,0xF7,0xFF,0x8F,0xFF,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x01,0x9F,0xF8,0x0C,0xFB,0xFF,0x8F,0xF7,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xEF,0xFC,0x00,0x07,0x8F,0xE0,0x06,0x77,0xFF,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0xF8,0x00,0x0F,0xC7,0xC0,0x07,0x7B,0xFF,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xF0,0x00,0x1F,0xE3,0xC0,0x03,0xFF,0xFF,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x3F,0xF1,0xC0,0x03,0xFB,0xFF,0x1F,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x7F,0xF8,0xC0,0x01,0xFF,0xFF,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x7F,0xFC,0x80,0x01,0xFB,0xFF,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x80,0x01,0xFF,0xFD,0x9F,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xBF,0xFE,0x00,0x01,0xFF,0xFF,0x80,0x01,0xFF,0xF8,0xDF,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x03,0xFF,0xFF,0x00,0x03,0xFF,0xF8,0x7F,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x03,0xFF,0xFE,0x00,0x07,0xFF,0xFC,0x7F,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x07,0xFF,0xFE,0x00,0x0F,0xFF,0xFE,0x3F,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x0F,0xFF,0xFC,0x00,0x3F,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x1F,0xFF,0xFC,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x1F,0xFF,0xF8,0x00,0x7F,0xFF,0xFF,0xCF,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x3F,0xFF,0xF0,0x00,0xFF,0xFF,0xFF,0x87,0xF9,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x7F,0xFF,0xF0,0x00,0xFF,0xFF,0xFF,0xC7,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x7F,0xFF,0xE0,0x01,0xFF,0xFF,0xFF,0xE3,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,0x00,0xFF,0xFF,0xC0,0x01,0xFF,0xFF,0xFF,0xF1,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xC0,0x03,0xFF,0xFF,0xFF,0xF8,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x01,0xFF,0xFF,0x80,0x07,0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0x80,0x07,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x0F,0xFF,0xFE,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x1F,0xFF,0xFE,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x1F,0xFF,0xFC,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3F,0xFF,0xFC,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x3F,0xFF,0xFC,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x7F,0xFF,0xF8,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xF8,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xF0,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xF0,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xF0,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xE0,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xFF,0xE0,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xC0,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};


//	register short i, j;
GrayOn();	
	for(i = 0; i < 128; i ++)
	{
		for(j = 0; j < 10; j ++)
		{
			*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*(127-i)+2*j+(TI89 ? 0: 5)) = *(titre_0+20*(127-i)+2*j);
			*(unsigned char *)(GetPlane(DARK_PLANE)+30*(127-i)+2*j+(TI89 ? 0: 5)) = *(titre_1+20*(127-i)+2*j);
			*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*i+2*j+1+(TI89 ? 0: 5)) = *(titre_0+20*i+2*j+1);
			*(unsigned char *)(GetPlane(DARK_PLANE)+30*i+2*j+1+(TI89 ? 0: 5)) = *(titre_1+20*i+2*j+1);
			if(!TI89)
			{
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*i) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*i) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*(127-i)+1) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*(127-i)+1) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*i+2) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*i+2) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*(127-i)+3) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*(127-i)+3) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*i+4) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*i+4) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*(127-i)+25) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*(127-i)+25) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*i+26) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*i+26) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*(127-i)+27) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*(127-i)+27) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*i+28) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*i+28) = 0xFF;
				*(unsigned char *)(GetPlane(LIGHT_PLANE)+30*(127-i)+29) = 0xFF;
				*(unsigned char *)(GetPlane(DARK_PLANE)+30*(127-i)+29) = 0xFF;
			}
		}
		asm("move.w #1000,%%d0; 0: dbf %%d0,0b" : : : "d0","cc");
	}
	
ngetchx();
GrayOff();
*/

// TODO: FIX these routines !
/*ClrScr();
for (i = 159; i >= 0; i--) {
FastDrawLine_R(LCD_MEM,0,0,i,99,A_XOR);
//ngetchx();
FastLine_Invert_R(LCD_MEM,0,0,i,99);
//ngetchx();
}*/




/*
// Simple test unrelated to ExtGraph: creating files with strange name and extension !
// As a side effect, TI-BASIC command DelVar does not want to delete this variable, throwing various
// errors depending on the name (not a variable name, syntax error) !
// The VAR-Link refuses archiving it, though.
HSym hsym = SymAdd(SYMSTR_CONST("no\x8C\x8B\x8E\xB5\xB8")); // PI CAP_PI CAP_SIGMA MU SUPER_PLUS
// HeapAlloc must be executed before DerefSym
// because of possible garbage collection.
HANDLE handle = HeapAlloc (100);
SYM_ENTRY *SymPtr = (DerefSym (hsym));
MULTI_EXPR *VarPtr = HeapDeref (SymPtr->handle = handle);
*(unsigned short *)VarPtr = 100-2;
*((unsigned char *)VarPtr+99) = OTH_TAG;
*((unsigned char *)VarPtr+98) = 0;
*((unsigned char *)VarPtr+97) = OTH_TAG;
*((unsigned char *)VarPtr+96) = 0x8C;
*((unsigned char *)VarPtr+95) = 0;
exit(0);
*/
/*
// Simple test unrelated to ExtGraph: comparing strings containing foreign caracters
// in a case-insensitive fashion.
printf_xy(0,0,"%c",!!cmpstri("\xD6","\xF6")+'0'); // Should be the same (0).
printf_xy(0,10,"%c",!!cmpstri("\xD5\xDF","\xF6\xFF")+'0'); // Should not be the same (1).
printf_xy(0,20,"%c",!!cmpstri("\xC6\x41","\xE6\x41")+'0'); // Should be the same (0).
ngetchx();
exit(0);
*/

//void FastTestLine_R(void *plane asm("%a0"),short x1 asm("%d0"),short y1 asm("%d1"),short x2 asm("%d2"),short y2 asm("%d3")) __attribute__((__regparm__));

/*
GrayOn();

//FillScreenWithGarbage_R(1234567891,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
//FillScreenWithGarbage_R(1987654321,LCD_SIZE,GrayGetPlane(DARK_PLANE));
GrayFillScreen_R(1234567891,1987654321);
//GraySingleSprite8_BLACK_R(19,19,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GraySingleSprite8_COLOR_R(29,29,8,sprite_8,COLOR_WHITE,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GraySingleSprite8_COLOR_R(29,39,8,sprite_8,COLOR_LIGHTGRAY,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GraySingleSprite8_COLOR_R(29,49,8,sprite_8,COLOR_DARKGRAY,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GraySingleSprite8_COLOR_R(29,59,8,sprite_8,COLOR_BLACK,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GraySingleSprite8_COLOR_R(39,29,8,sprite_8,COLOR_LIGHTGRAY,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GraySingleSprite8_COLOR_R(49,29,8,sprite_8,COLOR_DARKGRAY,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
GraySingleSprite8_COLOR_R(59,29,8,sprite_8,COLOR_BLACK,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//GraySingleSprite8_DGRAY_R(39,39,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//GraySingleSprite8_LGRAY_R(49,49,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//GraySingleSprite8_WHITE_R(59,59,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//GraySingleSprite8_XOR_R(69,69,8,sprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));

//extern void * __gray_used_mem;
printf_xy(0,0,"Light: %lp",GrayGetPlane(LIGHT_PLANE));
printf_xy(0,10,"Dark: %lp",GrayGetPlane(DARK_PLANE));
//printf_xy(0,20,"Mem: %lp",__gray_used_mem);

ngetchx();
GrayOff();
*/

/*
unsigned char i;
short t;

#undef SmapTypeStrings
#undef GetDataType
extern __ATTR_TIOS__ const char *SmapTypeStrings (short type);
extern __ATTR_TIOS__ short GetDataType (CESI ptr);

debug_printf_enabled = 1;
for (i = 0;;) {
    TRY
        t = GetDataType(&i);
		    if (t) {
            debug_printf("%hd: ",i);
            debug_printf("%hd\n",t);
        }
    ONERR
        debug_printf("%hd: Error\n",i);
    ENDTRY
    i++;
    if (i == 0) break;
}
for (i = 0; i < 17; i++) {
    debug_printf("\tdc.b \"%s\"\n",SmapTypeStrings(i));
}
exit(0);
*/
/*
unsigned char * plan0 = NULL, * plan1 = NULL;
unsigned char * vscreen_0 = NULL;
unsigned char * vscreen_1 = NULL;
vscreen_0 = malloc(LCD_SIZE);
vscreen_1 = malloc(LCD_SIZE);
ClrScr();
GrayOn();
plan0 = GrayGetPlane(0);
plan1 = GrayGetPlane(1);
l = 0;
k = 0;

do
{
k ++;
k %= 18000;
GrayClearScreen2B_R(vscreen_0, vscreen_1);

for(i = 0; i < 14; i++)
{
for(j = 0; j < 7; j++)
{
GraySprite16_OR_R(16*i, 16*j, 16, fond_0, fond_1, vscreen_0, vscreen_1);
}
}

for(i = 0; i < 105; i += 35)
{
GrayClipSprite32_MASK_R(i, 10, 32, animations_0[0][l], animations_1[0][l], animations_mask[0][l], animations_mask[0][l], vscreen_0, vscreen_1);
}

//l += (k%2 == 0 ? 1: 0);
if(k%2 == 0)
{
l ++;
}
l %= 5;

FastCopyScreen_R(vscreen_0, plan0);
FastCopyScreen_R(vscreen_1, plan1);

}while(!_keytest(RR_ESC));

GrayOff();
PortRestore();
free(vscreen_0);
free(vscreen_1);
exit(0);
*/


//    Sprite32_OR_R(17,0,6,sprite_32,LCD_MEM);
//    Sprite32_OR_R(0,17,6,sprite_32,LCD_MEM);
//    ClrScr();
/*
EXT_SETPIX_AN(lcd2,0,7);
EXT_SETPIX_AN(lcd2,4,7);
EXT_SETPIX(lcd,8,0);
EXT_SETPIX_AN(LCD_MEM,0,7);
EXT_SETPIX_AN(LCD_MEM,4,7);
*/
/*
printf("%c",EXT_GETPIX(GetPlane(LIGHT_PLANE),8,0));
printf("%c",EXT_GETPIX(GetPlane(LIGHT_PLANE),p->x_new,p->y_new));
printf("%c",EXT_GETPIX(LCD_MEM,8,0));
printf("%c",EXT_GETPIX(LCD_MEM,p->x_new,p->y_new));
*/
/*
EXT_SETPIX(GetPlane(LIGHT_PLANE),p->x_new,p->y_new);
EXT_CLRPIX(GetPlane(LIGHT_PLANE),p->x_new,p->y_new);
EXT_XORPIX(GetPlane(LIGHT_PLANE),p->x_new,p->y_new);
*/

//	unsigned char *src1 = splash_layer1, *src2 = splash_layer2, *dst1 = lcd, *dst2 = lcd2;

//GrayOn();
////    LCD_save(lcd);
////    LCD_save(lcd2);
//    gen_table();
/*
for (i = 0; i < LCD_HEIGHT; i++, dst1 += 30, dst2 += 30, src1 += 20, src2 += 20)
{
memcpy(dst1, src1, 20);
memcpy(dst2, src2, 20);
}
*/
/*
    if (!TI89) {
        FillScreenWithGarbage_R(0x384037EF,LCD_SIZE,lcd2);
        Scale1Plane240to160_R(lcd,lcd2);
        ClrScr();
        LCD_restore(lcd2);
        ngetchx();

        FillScreenWithGarbage_R(0x384037EF,LCD_SIZE,lcd);
        Scale1Plane160to240_R(lcd2,lcd);
        ClrScr();
        LCD_restore(lcd);
        ngetchx();
    }
    else {
        FillScreenWithGarbage_R(0x384037EF,LCD_SIZE,lcd2);
        Scale1Plane160to240_R(lcd,lcd2);
        ClrScr();
        LCD_restore(lcd2);
        ngetchx();

        FillScreenWithGarbage_R(0x384037EF,LCD_SIZE,lcd);
        Scale1Plane240to160_R(lcd2,lcd);
        ClrScr();
        LCD_restore(lcd);
        ngetchx();
    }
*/
/*
FastCopyScreen_R(lcd,GrayGetPlane(LIGHT_PLANE));
FastCopyScreen_R(lcd2,GrayGetPlane(DARK_PLANE));
memset(GrayGetPlane(LIGHT_PLANE)+3000,0,LCD_SIZE-3000);
memset(GrayGetPlane(DARK_PLANE)+3000,0,LCD_SIZE-3000);
ngetchx();

for (i = 0; i < 5; i++) {
GrayClearScreen();
screen_stretch(GrayGetPlane(LIGHT_PLANE),lcd);
screen_stretch(GrayGetPlane(DARK_PLANE),lcd2);

ngetchx();


GrayClearScreen();
Scale1Plane160to240_R(lcd,GrayGetPlane(LIGHT_PLANE));
Scale1Plane160to240_R(lcd2,GrayGetPlane(DARK_PLANE));

ngetchx();

}
*/

//Scale1Plane240to160_R(lcd,GrayGetPlane(LIGHT_PLANE));
//Scale1Plane240to160_R(lcd,GrayGetPlane(DARK_PLANE));
//Scale1Plane240to160_R(GrayGetPlane(LIGHT_PLANE),lcd);
//Scale1Plane240to160_R(GrayGetPlane(DARK_PLANE),lcd2);
//FastCopyScreen_R(GrayGetPlane(LIGHT_PLANE),lcd);
//FastCopyScreen_R(GrayGetPlane(DARK_PLANE),lcd2);
//ngetchx();

/*GrayClearScreen();
screen_stretch(GrayGetPlane(LIGHT_PLANE),lcd);
screen_stretch(GrayGetPlane(DARK_PLANE),lcd2);

FastCopyScreen_R(GrayGetPlane(LIGHT_PLANE),lcd);
FastCopyScreen_R(GrayGetPlane(DARK_PLANE),lcd2);
ngetchx();

GrayClearScreen();
Scale1Plane240to160_R(lcd,GrayGetPlane(LIGHT_PLANE));
Scale1Plane240to160_R(lcd2,GrayGetPlane(DARK_PLANE));

ngetchx();
*/
    PRG_setStart(0xCE);
//GrayOff();

/*
int j, k;
unsigned char * ptr;

    for (j=0;j<13;j++) {
        for (k=0;k<20;k++) {
            m[j][k] = random(8);
        }
    }

    ptr = (unsigned char *)m;
    for (j=13*20+1;(j--);) {
        *ptr++ = random(8);
    }

    ngetchx();
*/
/*
    unsigned long * p = (unsigned long *)((long)random(256)<<16);
    i = random(256);
    DEREFSMALL(p,i) = 0xFFEEDDCC;
    DEREFSMALL(sprite_16,4) = 0xFE4C;
    DEREFSMALL(foo,8) = (unsigned short *)0xF3E0;
*/
//    printf_xy(0,0,"%lX",DEREFSMALL(p,i));

//    ClipFastOutlinedCircle_R(LCD_MEM,30,30,25);
//    ClipFastOutlinedCircle_R(LCD_MEM,20,20,25);
//    FastOutlinedCircle_R(LCD_MEM,30,30,25);
//    DrawClipEllipse(30,30,25,25,&(SCR_RECT){{0,0,239,127}},A_NORMAL);
//    clip_ocircle(LCD_MEM,30,30,25);
//    GrayClipSprite32_BLIT_R(1,3,32,sprite_32,sprite_32,0xFFFFFFFF,LCD_MEM,LCD_MEM);
/*
    GrayClipSprite32_BLIT_R(1,127-32,32,sprite_32,sprite_32,0xFFFFFFFF,LCD_MEM,LCD_MEM);
    GrayClipSprite32_BLIT_R(1,128-32,32,sprite_32,sprite_32,0xFFFFFFFF,LCD_MEM,LCD_MEM);
    GrayClipSprite32_BLIT_R(1,129-32,32,sprite_32,sprite_32,0xFFFFFFFF,LCD_MEM,LCD_MEM);
*/
/*
    GrayClipSprite32_BLIT_R(1,127,32,sprite_32,sprite_32,0xFFFFFFFF,LCD_MEM,LCD_MEM);
    GrayClipSprite32_BLIT_R(1,128,32,sprite_32,sprite_32,0xFFFFFFFF,LCD_MEM,LCD_MEM);
    GrayClipSprite32_BLIT_R(1,129,32,sprite_32,sprite_32,0xFFFFFFFF,LCD_MEM,LCD_MEM);
*/
//    const char z[52]="01234567890123456789013245678901234567890123456789\0";
//    LCD_BUFFER lcd[2];
//    const char z2[52]="01234567890123456789013245678901234567890123456789\0";

/*
static const unsigned short sprite1[16] =
{
0b0000011111100000,
0b0001111111111000,
0b0011111111111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b1111111001111111,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000};

static const unsigned short sprite2[16] =
{
0b0000011111100000,
0b0001110000111000,
0b0011111001111100,
0b0111111111111110,
0b0111101111011110,
0b1111010110101111,
0b1111111111111111,
0b1111111111111111,
0b0111110000111110,
0b1110011111100111,
0b1110101111010111,
0b0111010000101110,
0b0111101111011110,
0b0011110000111100,
0b0001111111111000,
0b0000011111100000};
*/


    s5 = GetIntVec (AUTO_INT(5));
    SetIntVec (AUTO_INT(5), MyInt5);

//    FillScreenWithGarbage_R(0x384037EF,LCD_SIZE,LCD_MEM);
//    ClrScr();
//    for (i = 0; i < 16; i++) {
/*
        SpriteX8_MASK_R(i,i,8,sprite_8,sprite_8,1,LCD_MEM);
        SlowerSpriteX8_MASK_R(i+8,i+8,8,sprite_8,sprite_8,1,LCD_MEM);
        ngetchx();
*/
/*
        SpriteX8_BLIT_R(i,i,8,sprite_8,(unsigned char [1]){0x00},1,LCD_MEM);
        SlowerSpriteX8_BLIT_R(i+8,i+8,8,sprite_8,(unsigned char [1]){0xFF},1,LCD_MEM);
        ngetchx();
*/
/*
        SpriteX8_OR_R(i,i,8,sprite_8,1,LCD_MEM);
        SlowerSpriteX8_OR_R(i+8,i+8,8,sprite_8,1,LCD_MEM);
        ngetchx();
*/
/*
        SpriteX8_AND_R(i,i,8,sprite_8,1,LCD_MEM);
        SlowerSpriteX8_AND_R(i+8,i+8,8,sprite_8,1,LCD_MEM);
        ngetchx();
*/
/*
        SpriteX8_XOR_R(i,i,8,sprite_8,1,LCD_MEM);
        SlowerSpriteX8_XOR_R(i+8,i+8,8,sprite_8,1,LCD_MEM);
        ngetchx();
*/
/*
        SpriteX8_MASK_R(i,i,23,sprite_24,sprite_24,3,LCD_MEM);
        SlowerSpriteX8_MASK_R(32+i,32+i,32,sprite_32,sprite_32,4,LCD_MEM);
        ngetchx();
*/

/*
        SlowerSpriteX8_BLIT_R(i,i,23,sprite_24,(unsigned char [3]){0xFF,0,0},3,LCD_MEM);
        SlowerSpriteX8_BLIT_R(32+i,32+i,32,sprite_32,(unsigned long [1]){0xFFFFFFFF},4,LCD_MEM);
        ngetchx();
*/
/*
        SlowerSpriteX8_OR_R(i,i,23,sprite_24,3,LCD_MEM);
        SlowerSpriteX8_OR_R(32+i,32+i,32,sprite_32,4,LCD_MEM);
        ngetchx();
*/

//        SpriteX8_XOR_R(i,i,23,sprite_24,3,LCD_MEM);
//        SlowerSpriteX8_XOR_R(32+i,32+i,32,sprite_32,4,LCD_MEM);

/*
        SlowerSpriteX8_AND_R(i,i,23,sprite_24,3,LCD_MEM);
        SlowerSpriteX8_AND_R(32+i,32+i,32,sprite_32,4,LCD_MEM);
        ngetchx();
*/
//    }
//    asm("0: bra.s 0b");
/*
SpriteX8Get(0,0,40,LCD_MEM,dest_64,5);
SpriteX8X8_ROTATE_LEFT_R(40,dest_64,5,dest2_64);
SlowerSpriteX8_OR_R(40,40,40,dest2_64,5,LCD_MEM);
*/
//    if (!GrayOn()) goto end;


//    ngetchx();

//    GrayClipISprite8_AND_R(1,-3,8,isprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite8_BLIT_R(1,-3,8,isprite_8,0xFF,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite8_MASK_R(1,-3,8,msprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite8_OR_R(1,-3,8,isprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite8_RPLC_R(1,-3,8,isprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite8_TRANW_R(1,-3,8,isprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite8_TRANB_R(1,-3,8,isprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite8_XOR_R(1,-3,8,isprite_8,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));

//    GrayClipISprite16_AND_R(1,-3,16,isprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_BLIT_R(1,-3,16,isprite_16,0xFFFF,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_MASK_R(1,-3,16,msprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_OR_R(1,-3,16,isprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_RPLC_R(1,-3,16,isprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_TRANW_R(1,-3,16,isprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_TRANB_R(1,-3,16,isprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_XOR_R(1,-3,16,isprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));

//    GrayClipISprite32_AND_R(1,-3,32,isprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_BLIT_R(1,-3,32,isprite_32,0xFFFFFFFF,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_MASK_R(1,-3,32,msprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_OR_R(1,-3,32,isprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_RPLC_R(1,-3,32,isprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_TRANW_R(1,-3,32,isprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_TRANB_R(1,-3,32,isprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_XOR_R(1,-3,32,isprite_32,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    ngetchx();

//    GrayClipISprite8_BLIT_R(1,-3,8,isprite_8,0x00,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipSprite16_BLIT_R(1,-3,16,sprite_16,sprite_16,0x0000,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite16_BLIT_R(1,-3,16,isprite_16,0x0000,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    GrayClipISprite32_BLIT_R(1,-3,32,isprite_32,0x00000000,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//    ngetchx();

/*
//    srand(-1UL);
//    if (!GrayOn()) goto end;

    unsigned short * ptr = GetPlane(LIGHT_PLANE);
    for (unsigned short i = 0; i < LCD_SIZE/2; i++) {
        *ptr++ = random(RAND_MAX) + random(RAND_MAX);
    }
    ptr = GetPlane(DARK_PLANE);
    for (unsigned short i = 0; i < LCD_SIZE/2; i++) {
        *ptr++ = random(RAND_MAX) + random(RAND_MAX);
    }
*/

/*
    SetPlane(LIGHT_PLANE);
    ScrRectFill(&(SCR_RECT){{0,0,15,15}},&(SCR_RECT){{0,0,239,127}},A_NORMAL);
    SetPlane(DARK_PLANE);
    ScrRectFill(&(SCR_RECT){{0,0,15,15}},&(SCR_RECT){{0,0,239,127}},A_NORMAL);
*/
/*
    GraySprite16_TRANW_R(1,1,16,sprite1,sprite2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    OSFastArrows = 2;

// This test program is for VTI or HW1 only...
    memcpy((UCHAR*)GetPlane(LIGHT_PLANE)+60,LCD_MEM,LCD_SIZE-60);


    for (unsigned short i = 0; i <= 32; i++) {
        GrayFastGetBkgrnd32_R(i,0,16,GetPlane(LIGHT_PLANE),LCD_MEM,(USHORT*)dest_32);
        ScrRectFill(&(SCR_RECT){{i,0,i+31,15}},&(SCR_RECT){{0,0,239,127}},A_REVERSE);
        ngetchx();
        GrayFastPutBkgrnd32_R((USHORT*)dest_32,GetPlane(LIGHT_PLANE),LCD_MEM);
        ngetchx();
    }


    for (unsigned short i = 0; i <= 32; i++) {
        GrayFastGetBkgrnd16_R(i,0,16,GetPlane(LIGHT_PLANE),LCD_MEM,(USHORT*)dest_32);
        ScrRectFill(&(SCR_RECT){{i,0,i+15,15}},&(SCR_RECT){{0,0,239,127}},A_REVERSE);
        ngetchx();
        GrayFastPutBkgrnd16_R((USHORT*)dest_32,GetPlane(LIGHT_PLANE),LCD_MEM);
        ngetchx();
    }


    for (unsigned short i = 0; i <= 32; i++) {
        GrayFastGetBkgrnd8_R(i,0,8,GetPlane(LIGHT_PLANE),LCD_MEM,(USHORT*)dest_32);
        ScrRectFill(&(SCR_RECT){{i,0,i+7,7}},&(SCR_RECT){{0,0,239,127}},A_REVERSE);
        ngetchx();
        GrayFastPutBkgrnd8_R((USHORT*)dest_32,GetPlane(LIGHT_PLANE),LCD_MEM);
        ngetchx();
    }


    GrayOff();

    for (unsigned short i = 0; i <= 32; i++) {
        FastGetBkgrnd32_R(i,0,16,LCD_MEM,(USHORT*)dest_32);
        ScrRectFill(&(SCR_RECT){{i,0,i+31,15}},&(SCR_RECT){{0,0,239,127}},A_REVERSE);
        ngetchx();
        FastPutBkgrnd32_R((USHORT*)dest_32,LCD_MEM);
        ngetchx();
    }


    for (unsigned short i = 0; i <= 32; i++) {
        FastGetBkgrnd16_R(i,0,16,LCD_MEM,(USHORT*)dest_32);
        ScrRectFill(&(SCR_RECT){{i,0,i+15,15}},&(SCR_RECT){{0,0,239,127}},A_REVERSE);
        ngetchx();
        FastPutBkgrnd16_R((USHORT*)dest_32,LCD_MEM);
        ngetchx();
    }


    for (unsigned short i = 0; i <= 32; i++) {
        FastGetBkgrnd8_R(i,0,8,LCD_MEM,(USHORT*)dest_32);
        ScrRectFill(&(SCR_RECT){{i,0,i+7,7}},&(SCR_RECT){{0,0,239,127}},A_REVERSE);
        ngetchx();
        FastPutBkgrnd8_R((USHORT*)dest_32,LCD_MEM);
        ngetchx();
    }

    OSFastArrows = 0;
*/
/*
    GrayClearScreen_R();
    GrayClipISprite16_OR_R(2,-2,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(-1,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(9,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/

//UnpackBuffer(NULL,NULL);

/*
    ClrScr();
    PreshiftSprite16x16(sprite_16,preshiftbuf);
    t1 = counter;
    for (j=0; j<16; j++) {
        for (i=4000; (i--);) {
            PSprite16x16_OR_R(j,0,preshiftbuf,LCD_MEM);
        }
    }

    t1 = counter - t1;

    t2 = counter;
    for (j=0; j<16; j++) {
        for (i=4000; (i--);) {
            ClipSprite16_OR_R(j,0,16,sprite_16,LCD_MEM);
        }
    }

    t2 = counter - t2;

    printf_xy(0,0,"%hu",t1);
    printf_xy(0,10,"%hu",t2);

    goto end;
*/

/*
ClrScr();
SpriteX8_MIRROR_H_R(24,sprite_24,3,dest_24);
//SpriteX8_OR(0,0,24,sprite_24,3,LCD_MEM);
//SpriteX8_OR(24,24,24,dest_24,3,LCD_MEM);
ngetchx();
SpriteX8_MIRROR_V_R(24,sprite_24,3,dest_24);
//SpriteX8_OR(48,48,24,dest_24,3,LCD_MEM);
ngetchx();
SpriteX8_MIRROR_HV_R(24,sprite_24,3,dest_24);
//SpriteX8_OR(72,72,24,dest_24,3,LCD_MEM);
ngetchx();
*/

//    if (!GrayOn()) goto end;
// extern void SpriteX8_MIRROR_H_R(register short h asm("%d0"),register unsigned char* src asm("%a0"),register short bytewidth asm("%d1"),register unsigned char* dest asm("%a1")) __attribute__((__regparm__(4)));

/*
    GrayClearScreen_R();
    CreateSpriteShadowX8_R(8,1,sprite_8,sprite2_8,dest_8+2*8*sizeof(UCHAR),dest_8,dest_8+8*sizeof(UCHAR));
    GraySpriteX8_OR(0,0,8,dest_8,dest_8+8*sizeof(UCHAR),1,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySpriteX8_OR(8,0,8,sprite_8,sprite2_8,1,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    CreateSpriteShadowX8_R(16,2,(unsigned char*)sprite_16,(unsigned char*)sprite2_16,(unsigned char*)dest_16+2*16*sizeof(USHORT),(unsigned char*)dest_16,(unsigned char*)dest_16+16*sizeof(USHORT));
    GraySpriteX8_OR(0,0,16,(unsigned char*)dest_16,(unsigned char*)dest_16+16*sizeof(USHORT),2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySpriteX8_OR(16,0,16,(unsigned char*)sprite_16,(unsigned char*)sprite2_16,2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    CreateSpriteShadowX8_R(32,4,(unsigned char*)sprite_32,(unsigned char*)sprite2_32,(unsigned char*)dest_32+2*32*sizeof(ULONG),(unsigned char*)dest_32,(unsigned char*)dest_32+32*sizeof(ULONG));
    GraySpriteX8_OR(0,0,32,(unsigned char*)dest_32,(unsigned char*)dest_32+32*sizeof(ULONG),4,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySpriteX8_OR(32,0,32,(unsigned char*)sprite_32,(unsigned char*)sprite2_32,4,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();


    GrayClearScreen_R();
    CreateSpriteIShadowX8_R(8,1,sprite_8,sprite2_8,dest_8+2*8*sizeof(UCHAR),dest_8,dest_8+8*sizeof(UCHAR));
    GraySpriteX8_OR(0,0,8,dest_8,dest_8+8*sizeof(UCHAR),1,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySpriteX8_OR(8,0,8,sprite_8,sprite2_8,1,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    CreateSpriteIShadowX8_R(16,2,(unsigned char*)sprite_16,(unsigned char*)sprite2_16,(unsigned char*)dest_16+2*16*sizeof(USHORT),(unsigned char*)dest_16,(unsigned char*)dest_16+16*sizeof(USHORT));
    GraySpriteX8_OR(0,0,16,(unsigned char*)dest_16,(unsigned char*)dest_16+16*sizeof(USHORT),2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySpriteX8_OR(16,0,16,(unsigned char*)sprite_16,(unsigned char*)sprite2_16,2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    CreateSpriteIShadowX8_R(32,4,(unsigned char*)sprite_32,(unsigned char*)sprite2_32,(unsigned char*)dest_32+2*32*sizeof(ULONG),(unsigned char*)dest_32,(unsigned char*)dest_32+32*sizeof(ULONG));
    GraySpriteX8_OR(0,0,32,(unsigned char*)dest_32,(unsigned char*)dest_32+32*sizeof(ULONG),4,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySpriteX8_OR(32,0,32,(unsigned char*)sprite_32,(unsigned char*)sprite2_32,4,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/


//PreshiftSprite16x16(sprite_16,preshiftbuf);

/*
FastOutlineRect_R(LCD_MEM,0,0,158,98,A_XOR);
ngetchx();
*/
//TestCollide16(0,0,0,0,16,sprite_16,sprite_16);
/*
srand(0);
for(i = 0; i < 65000; i++) {
    x1 = random(239-16);
    x2 = random(239-16);
    y1 = random(127-16);
    y2 = random(127-16);
    if (    (!!TestCollide16_R(x1,y1,x2,y2,4,((unsigned short[4]){0x0E80,0x03E0,0x10F8,0xA0FE}),((unsigned short[4]){0x0880,0xE00A,0xD002,0x7001})))
         != (!!TestCollide16(x1,y1,x2,y2,4,((unsigned short[4]){0x0E80,0x03E0,0x10F8,0xA0FE}),((unsigned short[4]){0x0880,0xE00A,0xD002,0x7001})))) {
//    if (    (!!TestCollide16_R(x1, y1,x2,y2,4,((unsigned short[4]){0x0080,0x00E0,0x00F8,0x00FE}),((unsigned short[4]){0x0000,0x0000,0x0002,0x0001}))))
//         != (!!TestCollide16(x1,y1,x2,y2,4,((unsigned short[4]){0x0080,0x00E0,0x00F8,0x00FE}),((unsigned short[4]){0x0000,0x0000,0x0002,0x0001}))))) {
       printf_xy(0,0,"%hu %hu %hu %hu %hu",i,x1,y1,x2,y2);
       ngetchx();
       asm("illegal");
    }
}
*/
/*
srand(0);
for(i = 0; i < 65000; i++) {
    x1 = random(239-8);
    x2 = random(239-8);
    y1 = random(127-8);
    y2 = random(127-8);
    if (    (!!TestCollide8_R(x1,y1,x2,y2,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01})))
         != (!!TestCollide8(x1,y1,x2,y2,4,((unsigned char[4]){0x80,0xE0,0xF8,0xFE}),((unsigned char[4]){0x00,0x0A,0x02,0x01})))) {
       printf_xy(0,0,"%hu %hu %hu %hu %hu",i,x1,y1,x2,y2);
       ngetchx();
       asm("illegal");
    }
}
*/


/*
    if (!GrayOn()) goto end;
    for (j=0; j < 128-32; j++) {
        for (i=0; i<240-8*12; i++) {
            GraySpriteX8_MASK(i,j,32,msprite_32,msprite_32,msprite_32,msprite_32,12,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        }
    }
*/
//    GrayDrawRect(0,0,159,99,COLOR_WHITE,RECT_EMPTY);
//    GrayClearScreen_R();
//    PreshiftSprite16x16(sprite_16,preshiftbuf);
//    PreshiftGrayISprite16x16(isprite_16,preshiftbuf);
/*
    GrayClipPSprite16x16_OR_R(0,0,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(1,16,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(2,32,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(3,48,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(4,64,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(5,80,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(6,0,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(7,16,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(8,32,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(9,48,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(10,64,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(11,80,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(12,0,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(13,16,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(14,32,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GrayClipPSprite16x16_OR_R(15,48,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));

    ngetchx();

    GraySprite16_XOR_R(0,0,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(1,16,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(2,32,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(3,48,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(4,64,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(5,80,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(6,0,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(7,16,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(8,32,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(9,48,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(10,64,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(11,80,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(12,0,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(13,16,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(14,32,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    GraySprite16_XOR_R(15,48,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
    ngetchx();
*/

/*
    t1 = counter;
    for (j=0; j<16; j++) {
        for (i=2000; (i--);) {
            GrayPSprite16x16_OR_R(j,0,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
//            GrayClipPSprite16x16_OR_R(j,0,preshiftbuf,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        }
    }

    t1 = counter - t1;

    t2 = counter;
    for (j=0; j<16; j++) {
        for (i=2000; (i--);) {
            GrayClipSprite16_OR_R(j,0,16,sprite_16,sprite_16,GrayGetPlane(LIGHT_PLANE),GrayGetPlane(DARK_PLANE));
        }
    }

    t2 = counter - t2;

    printf_xy(0,0,"%hu",t1);
    printf_xy(0,10,"%hu",t2);

    goto end;
*/

/*
GrayFastOutlineRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_WHITE);
ngetchx();
GrayFastOutlineRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_LIGHTGRAY);
ngetchx();
GrayFastOutlineRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_DARKGRAY);
ngetchx();
GrayFastOutlineRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_BLACK);
ngetchx();

GrayFastFillRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_WHITE);
ngetchx();
GrayFastFillRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_LIGHTGRAY);
ngetchx();
GrayFastFillRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_DARKGRAY);
ngetchx();
GrayFastFillRect_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),0,0,158,98,COLOR_BLACK);
ngetchx();
*/

/*
EXT_SETPIX(LCD_MEM,0,0);
EXT_CLRPIX(LCD_MEM,0,0);
EXT_XORPIX(LCD_MEM,0,0);
printf_xy(0,0,"%c",EXT_GETPIX(LCD_MEM,0,0));
*/



/*
    GrayShadowPlanesX16_R(128,240/16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayIShadowPlanesX16_R(128,240/16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/


/*
FastFillRectX8_R(LCD_MEM,0,0,8,6);
FastEraseRectX8_R(LCD_MEM,0,0,8,6);
FastFillRectX8_R(LCD_MEM,0,0,8,6);
FastInvertRectX8_R(LCD_MEM,0,0,8,6);

    FadeOutToBlack_RL18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);
    FadeOutToWhite_LR18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);
    FadeOutToBlack_LR18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);
    FadeOutToWhite_RL18_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);
*/
/*
    printf_xy(0,0,"%lX",reverselongword(0x36F4C9D0));
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
*/
/*
    Sprite8_RPLC_R(0,0,8,sprite_8,GetPlane(DARK_PLANE));
    Sprite8_RPLC_R(9,0,8,sprite_8,GetPlane(DARK_PLANE));
    Sprite8_RPLC_R(14,0,8,sprite_8,GetPlane(DARK_PLANE));
    Sprite16_RPLC_R(9,0,16,sprite_16,GetPlane(DARK_PLANE));
    Sprite32_RPLC_R(26,0,32,sprite_32,GetPlane(DARK_PLANE));
*/
/*
    ClipSprite8_RPLC_R(-1,9,8,sprite_8,GetPlane(DARK_PLANE));
    ClipSprite8_RPLC_R(9,9,8,sprite_8,GetPlane(DARK_PLANE));
    ClipSprite8_RPLC_R(233,9,8,sprite_8,GetPlane(DARK_PLANE));

    ClipSprite16_RPLC_R(-1,17,16,sprite_16,GetPlane(DARK_PLANE));
    ClipSprite16_RPLC_R(17,17,16,sprite_16,GetPlane(DARK_PLANE));
    ClipSprite16_RPLC_R(225,17,16,sprite_16,GetPlane(DARK_PLANE));

    ClipSprite32_RPLC_R(-1,33,32,sprite_32,GetPlane(DARK_PLANE));
    ClipSprite32_RPLC_R(33,33,32,sprite_32,GetPlane(DARK_PLANE));
    ClipSprite32_RPLC_R(209,33,32,sprite_32,GetPlane(DARK_PLANE));
*/
/*
    GraySprite8_RPLC_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite8_RPLC_R(9,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite8_RPLC_R(14,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite16_RPLC_R(9,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite32_RPLC_R(26,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
*/
/*
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
*/
/*
    GrayClipSprite8_RPLC_R(-1,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_RPLC_R(9,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_RPLC_R(233,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    GrayClipSprite16_RPLC_R(-1,17,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_RPLC_R(17,17,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_RPLC_R(225,17,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    GrayClipSprite32_RPLC_R(-1,33,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_RPLC_R(33,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_RPLC_R(209,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
*/
/*
    ClearGrayScreen();
    Sprite32_OR_R(0,0,32,sprite_32,GetPlane(DARK_PLANE));
    ngetchx();
    GraySprite32_SHADOW_R(0,0,32,dest_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
GrayOff();
    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    Tile16x16_BLIT_R(0,0,sprite_16,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    Tile8x8_BLIT_R(0,0,sprite_8,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    Tile32x32_BLIT_R(0,0,sprite_32,0,LCD_MEM);
*/


/*
GrayOn();
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayITile16x16_BLIT_R(0,0,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayITile8x8_BLIT_R(0,0,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayITile32x32_BLIT_R(0,0,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
*/


/*
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayTile16x16_BLIT_R(0,0,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayTile8x8_BLIT_R(0,0,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayTile32x32_BLIT_R(0,0,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
*/

/*
    FastFillScreen_R(LCD_MEM);
    Sprite8_AND_R(0,0,8,sprite_8,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Sprite8_OR_R(0,0,8,sprite_8,LCD_MEM);
    Sprite8_XOR_R(0,0,8,sprite_8,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite8_RPLC_R(0,0,8,sprite_8,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite8_BLIT_R(0,0,8,sprite_8,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite8_MASK_R(0,0,8,sprite_8,sprite_8,LCD_MEM);
    ngetchx();

    FastFillScreen_R(LCD_MEM);
    Sprite8_AND_R(8,8,8,sprite_8,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Sprite8_OR_R(8,8,8,sprite_8,LCD_MEM);
    Sprite8_XOR_R(8,8,8,sprite_8,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite8_RPLC_R(8,8,8,sprite_8,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite8_BLIT_R(8,8,8,sprite_8,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite8_MASK_R(8,8,8,sprite_8,sprite_8,LCD_MEM);
    ngetchx();
*/
/*
    FastFillScreen_R(LCD_MEM);
    Sprite16_AND_R(0,0,16,sprite_16,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Sprite16_OR_R(0,0,16,sprite_16,LCD_MEM);
    Sprite16_XOR(0,0,16,sprite_16,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite16_RPLC_R(0,0,16,sprite_16,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite16_BLIT_R(0,0,16,sprite_16,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite16_MASK_R(0,0,16,sprite_16,sprite_16,LCD_MEM);
    ngetchx();

    FastFillScreen_R(LCD_MEM);
    Sprite16_AND_R(16,16,16,sprite_16,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Sprite16_OR_R(16,16,16,sprite_16,LCD_MEM);
    Sprite16_XOR_R(16,16,16,sprite_16,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite16_RPLC_R(16,16,16,sprite_16,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite16_BLIT_R(16,16,16,sprite_16,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite16_MASK_R(16,16,16,sprite_16,sprite_16,LCD_MEM);
    ngetchx();
*/
/*
    FastFillScreen_R(LCD_MEM);
    Sprite32_AND_R(0,0,32,sprite_32,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Sprite32_OR_R(0,0,32,sprite_32,LCD_MEM);
    Sprite32_XOR_R(0,0,32,sprite_32,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite32_RPLC_R(0,0,32,sprite_32,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite32_BLIT_R(0,0,32,sprite_32,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite32_MASK_R(0,0,32,sprite_32,sprite_32,LCD_MEM);
    ngetchx();

    FastFillScreen_R(LCD_MEM);
    Sprite32_AND_R(32,32,32,sprite_32,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Sprite32_OR_R(32,32,32,sprite_32,LCD_MEM);
    Sprite32_XOR_R(32,32,32,sprite_32,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite32_RPLC_R(32,32,32,sprite_32,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite32_BLIT_R(32,32,32,sprite_32,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Sprite32_MASK_R(32,32,32,sprite_32,sprite_32,LCD_MEM);
    ngetchx();
*/

/*
    FastFillScreen_R(LCD_MEM);
    ClipSprite8_AND_R(-2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_AND_R(0,0,8,sprite_8,LCD_MEM);
    ClipSprite8_AND_R(2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_AND_R(9,8,8,sprite_8,LCD_MEM);
    ClipSprite8_AND_R(232,0,8,sprite_8,LCD_MEM);
    ClipSprite8_AND_R(234,0,8,sprite_8,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    ClipSprite8_OR_R(-2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_OR_R(0,0,8,sprite_8,LCD_MEM);
    ClipSprite8_OR_R(2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_OR_R(9,8,8,sprite_8,LCD_MEM);
    ClipSprite8_OR_R(232,0,8,sprite_8,LCD_MEM);
    ClipSprite8_OR_R(234,0,8,sprite_8,LCD_MEM);
    ClipSprite8_XOR_R(-2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_XOR_R(0,0,8,sprite_8,LCD_MEM);
    ClipSprite8_XOR_R(2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_XOR_R(9,8,8,sprite_8,LCD_MEM);
    ClipSprite8_XOR_R(232,0,8,sprite_8,LCD_MEM);
    ClipSprite8_XOR_R(234,0,8,sprite_8,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite8_RPLC_R(-2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_RPLC_R(0,0,8,sprite_8,LCD_MEM);
    ClipSprite8_RPLC_R(2,0,8,sprite_8,LCD_MEM);
    ClipSprite8_RPLC_R(9,8,8,sprite_8,LCD_MEM);
    ClipSprite8_RPLC_R(232,0,8,sprite_8,LCD_MEM);
    ClipSprite8_RPLC_R(234,0,8,sprite_8,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite8_BLIT_R(-2,0,8,sprite_8,0,LCD_MEM);
    ClipSprite8_BLIT_R(0,0,8,sprite_8,0,LCD_MEM);
    ClipSprite8_BLIT_R(2,0,8,sprite_8,0,LCD_MEM);
    ClipSprite8_BLIT_R(9,8,8,sprite_8,0,LCD_MEM);
    ClipSprite8_BLIT_R(232,0,8,sprite_8,0,LCD_MEM);
    ClipSprite8_BLIT_R(234,0,8,sprite_8,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite8_MASK_R(-2,0,8,sprite_8,sprite_8,LCD_MEM);
    ClipSprite8_MASK_R(0,0,8,sprite_8,sprite_8,LCD_MEM);
    ClipSprite8_MASK_R(2,0,8,sprite_8,sprite_8,LCD_MEM);
    ClipSprite8_MASK_R(9,8,8,sprite_8,sprite_8,LCD_MEM);
    ClipSprite8_MASK_R(232,0,8,sprite_8,sprite_8,LCD_MEM);
    ClipSprite8_MASK_R(234,0,8,sprite_8,sprite_8,LCD_MEM);
    ngetchx();
*/
/*
    FastFillScreen_R(LCD_MEM);
    ClipSprite16_AND_R(-2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_AND_R(0,0,16,sprite_16,LCD_MEM);
    ClipSprite16_AND_R(2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_AND_R(9,16,16,sprite_16,LCD_MEM);
    ClipSprite16_AND_R(224,0,16,sprite_16,LCD_MEM);
    ClipSprite16_AND_R(226,0,16,sprite_16,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    ClipSprite16_OR_R(-2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_OR_R(0,0,16,sprite_16,LCD_MEM);
    ClipSprite16_OR_R(2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_OR_R(9,16,16,sprite_16,LCD_MEM);
    ClipSprite16_OR_R(224,0,16,sprite_16,LCD_MEM);
    ClipSprite16_OR_R(226,0,16,sprite_16,LCD_MEM);
    ClipSprite16_XOR_R(-2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_XOR_R(0,0,16,sprite_16,LCD_MEM);
    ClipSprite16_XOR_R(2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_XOR_R(9,16,16,sprite_16,LCD_MEM);
    ClipSprite16_XOR_R(224,0,16,sprite_16,LCD_MEM);
    ClipSprite16_XOR_R(226,0,16,sprite_16,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite16_RPLC_R(-2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_RPLC_R(0,0,16,sprite_16,LCD_MEM);
    ClipSprite16_RPLC_R(2,0,16,sprite_16,LCD_MEM);
    ClipSprite16_RPLC_R(9,16,16,sprite_16,LCD_MEM);
    ClipSprite16_RPLC_R(224,0,16,sprite_16,LCD_MEM);
    ClipSprite16_RPLC_R(226,0,16,sprite_16,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite16_BLIT_R(-2,0,16,sprite_16,0,LCD_MEM);
    ClipSprite16_BLIT_R(0,0,16,sprite_16,0,LCD_MEM);
    ClipSprite16_BLIT_R(2,0,16,sprite_16,0,LCD_MEM);
    ClipSprite16_BLIT_R(9,16,16,sprite_16,0,LCD_MEM);
    ClipSprite16_BLIT_R(224,0,16,sprite_16,0,LCD_MEM);
    ClipSprite16_BLIT_R(226,0,16,sprite_16,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite16_MASK_R(-2,0,16,sprite_16,sprite_16,LCD_MEM);
    ClipSprite16_MASK_R(0,0,16,sprite_16,sprite_16,LCD_MEM);
    ClipSprite16_MASK_R(2,0,16,sprite_16,sprite_16,LCD_MEM);
    ClipSprite16_MASK_R(9,16,16,sprite_16,sprite_16,LCD_MEM);
    ClipSprite16_MASK_R(224,0,16,sprite_16,sprite_16,LCD_MEM);
    ClipSprite16_MASK_R(226,0,16,sprite_16,sprite_16,LCD_MEM);
    ngetchx();
*/
/*
    FastFillScreen_R(LCD_MEM);
    ClipSprite32_AND_R(-2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_AND_R(0,0,32,sprite_32,LCD_MEM);
    ClipSprite32_AND_R(2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_AND_R(9,32,32,sprite_32,LCD_MEM);
    ClipSprite32_AND_R(208,0,32,sprite_32,LCD_MEM);
    ClipSprite32_AND_R(210,0,32,sprite_32,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    ClipSprite32_OR_R(-2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_OR_R(0,0,32,sprite_32,LCD_MEM);
    ClipSprite32_OR_R(2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_OR_R(9,32,32,sprite_32,LCD_MEM);
    ClipSprite32_OR_R(208,0,32,sprite_32,LCD_MEM);
    ClipSprite32_OR_R(210,0,32,sprite_32,LCD_MEM);
    ClipSprite32_XOR_R(-2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_XOR_R(0,0,32,sprite_32,LCD_MEM);
    ClipSprite32_XOR_R(2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_XOR_R(9,32,32,sprite_32,LCD_MEM);
    ClipSprite32_XOR_R(208,0,32,sprite_32,LCD_MEM);
    ClipSprite32_XOR_R(210,0,32,sprite_32,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite32_RPLC_R(-2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_RPLC_R(0,0,32,sprite_32,LCD_MEM);
    ClipSprite32_RPLC_R(2,0,32,sprite_32,LCD_MEM);
    ClipSprite32_RPLC_R(9,32,32,sprite_32,LCD_MEM);
    ClipSprite32_RPLC_R(208,0,32,sprite_32,LCD_MEM);
    ClipSprite32_RPLC_R(210,0,32,sprite_32,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite32_BLIT_R(-2,0,32,sprite_32,0,LCD_MEM);
    ClipSprite32_BLIT_R(0,0,32,sprite_32,0,LCD_MEM);
    ClipSprite32_BLIT_R(2,0,32,sprite_32,0,LCD_MEM);
    ClipSprite32_BLIT_R(9,32,32,sprite_32,0,LCD_MEM);
    ClipSprite32_BLIT_R(208,0,32,sprite_32,0,LCD_MEM);
    ClipSprite32_BLIT_R(210,0,32,sprite_32,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    ClipSprite32_MASK_R(-2,0,32,sprite_32,sprite_32,LCD_MEM);
    ClipSprite32_MASK_R(0,0,32,sprite_32,sprite_32,LCD_MEM);
    ClipSprite32_MASK_R(2,0,32,sprite_32,sprite_32,LCD_MEM);
    ClipSprite32_MASK_R(9,32,32,sprite_32,sprite_32,LCD_MEM);
    ClipSprite32_MASK_R(208,0,32,sprite_32,sprite_32,LCD_MEM);
    ClipSprite32_MASK_R(210,0,32,sprite_32,sprite_32,LCD_MEM);
    ngetchx();
*/

/*
    FastFillScreen_R(LCD_MEM);
    Tile16x16_AND_R(0,0,sprite_16,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Tile16x16_OR_R(0,0,sprite_16,LCD_MEM);
    Tile16x16_XOR_R(0,0,sprite_16,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Tile16x16_RPLC_R(0,0,sprite_16,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Tile16x16_BLIT_R(0,0,sprite_16,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Tile16x16_MASK_R(0,0,sprite_16,sprite_16,LCD_MEM);
    ngetchx();
*/

/*
    FastFillScreen_R(LCD_MEM);
    Tile8x8_AND_R(0,0,sprite_8,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Tile8x8_OR_R(0,0,sprite_8,LCD_MEM);
    Tile8x8_XOR_R(0,0,sprite_8,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Tile8x8_RPLC_R(0,0,sprite_8,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Tile8x8_BLIT_R(0,0,sprite_8,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Tile8x8_MASK_R(0,0,sprite_8,sprite_8,LCD_MEM);
    ngetchx();
*/
/*
    FastFillScreen_R(LCD_MEM);
    Tile32x32_AND_R(0,0,sprite_32,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Tile32x32_OR_R(0,0,sprite_32,LCD_MEM);
    Tile32x32_XOR_R(0,0,sprite_32,LCD_MEM);
    ngetchx();
    FastClearScreen_R(LCD_MEM);
    Tile32x32_RPLC_R(0,0,sprite_32,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Tile32x32_BLIT_R(0,0,sprite_32,0,LCD_MEM);
    ngetchx();
    FastFillScreen_R(LCD_MEM);
    Tile32x32_MASK_R(0,0,sprite_32,sprite_32,LCD_MEM);
    ngetchx();
*/


//if (!GrayOn()) goto end;
/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_AND(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite8_OR(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite8_XOR(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_RPLC_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_BLIT(0,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_MASK(0,0,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_SMASK_R(0,0,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite8_TRANB_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite8_TRANW_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_AND(9,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite8_OR(9,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite8_XOR(9,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_RPLC_R(9,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_BLIT(9,9,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_MASK(9,9,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite8_SMASK_R(9,9,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite8_TRANB_R(9,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite8_TRANW_R(9,9,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_AND(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite16_OR(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite16_XOR(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_RPLC_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_BLIT(0,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_MASK(0,0,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_SMASK_R(0,0,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite16_TRANB_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite16_TRANW_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_AND(9,9,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite16_OR(9,9,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite16_XOR(9,9,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_RPLC_R(9,9,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_BLIT(9,9,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_MASK(9,9,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite16_SMASK_R(9,9,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite16_TRANB_R(9,9,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite16_TRANW_R(9,9,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_AND(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite32_OR(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite32_XOR(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite32_RPLC_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_BLIT(0,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_MASK(0,0,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_SMASK_R(0,0,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite32_TRANB_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite32_TRANW_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_AND(9,9,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite32_OR(9,9,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite32_XOR(9,9,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GraySprite32_RPLC_R(9,9,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_BLIT(9,9,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_MASK(9,9,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GraySprite32_SMASK_R(9,9,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite32_TRANB_R(9,9,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GraySprite32_TRANW_R(9,9,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/

/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite8_AND_R(-2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_AND_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_AND_R(2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_AND_R(9,8,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_AND_R(232,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_AND_R(234,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayClipSprite8_OR_R(-2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_OR_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_OR_R(2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_OR_R(9,8,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_OR_R(232,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_OR_R(234,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_XOR_R(-2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_XOR_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_XOR_R(2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_XOR_R(9,8,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_XOR_R(232,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_XOR_R(234,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite8_RPLC_R(-2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_RPLC_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_RPLC_R(2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_RPLC_R(9,8,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_RPLC_R(232,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_RPLC_R(234,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite8_BLIT_R(-2,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_BLIT_R(0,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_BLIT_R(2,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_BLIT_R(9,8,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_BLIT_R(232,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_BLIT_R(234,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite8_MASK_R(-2,0,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_MASK_R(0,0,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_MASK_R(2,0,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_MASK_R(9,8,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_MASK_R(232,0,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_MASK_R(234,0,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite8_SMASK_R(-2,0,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_SMASK_R(0,0,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_SMASK_R(2,0,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_SMASK_R(9,8,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_SMASK_R(232,0,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_SMASK_R(234,0,8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipSprite8_TRANB_R(-2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANB_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANB_R(2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANB_R(9,8,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANB_R(232,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANB_R(234,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipSprite8_TRANW_R(-2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANW_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANW_R(2,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANW_R(9,8,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANW_R(232,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite8_TRANW_R(234,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite16_AND_R(-2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_AND_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_AND_R(2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_AND_R(9,16,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_AND_R(224,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_AND_R(226,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayClipSprite16_OR_R(-2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_OR_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_OR_R(2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_OR_R(9,16,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_OR_R(224,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_OR_R(226,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_XOR_R(-2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_XOR_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_XOR_R(2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_XOR_R(9,16,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_XOR_R(224,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_XOR_R(226,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite16_RPLC_R(-2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_RPLC_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_RPLC_R(2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_RPLC_R(9,16,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_RPLC_R(224,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_RPLC_R(226,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite16_BLIT_R(-2,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_BLIT_R(0,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_BLIT_R(2,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_BLIT_R(9,16,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_BLIT_R(224,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_BLIT_R(226,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite16_MASK_R(-2,0,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_MASK_R(0,0,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_MASK_R(2,0,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_MASK_R(9,16,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_MASK_R(224,0,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_MASK_R(226,0,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite16_SMASK_R(-2,0,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_SMASK_R(0,0,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_SMASK_R(2,0,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_SMASK_R(9,16,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_SMASK_R(224,0,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_SMASK_R(226,0,16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipSprite16_TRANB_R(-2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANB_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANB_R(2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANB_R(9,16,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANB_R(224,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANB_R(226,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipSprite16_TRANW_R(-2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANW_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANW_R(2,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANW_R(9,16,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANW_R(224,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite16_TRANW_R(226,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite32_AND_R(-2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_AND_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_AND_R(2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_AND_R(9,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_AND_R(208,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_AND_R(210,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayClipSprite32_OR_R(-2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_OR_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_OR_R(2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_OR_R(9,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_OR_R(208,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_OR_R(210,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_XOR_R(-2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_XOR_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_XOR_R(2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_XOR_R(9,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_XOR_R(208,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_XOR_R(210,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite32_RPLC_R(-2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_RPLC_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_RPLC_R(2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_RPLC_R(9,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_RPLC_R(208,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_RPLC_R(210,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite32_BLIT_R(-2,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_BLIT_R(0,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_BLIT_R(2,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_BLIT_R(9,32,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_BLIT_R(208,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_BLIT_R(210,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite32_MASK_R(-2,0,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_MASK_R(0,0,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_MASK_R(2,0,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_MASK_R(9,32,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_MASK_R(208,0,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_MASK_R(210,0,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite32_SMASK_R(-2,0,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_SMASK_R(0,0,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_SMASK_R(2,0,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_SMASK_R(9,32,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_SMASK_R(208,0,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_SMASK_R(210,0,32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipSprite32_TRANB_R(-2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANB_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANB_R(2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANB_R(9,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANB_R(208,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANB_R(210,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayClipSprite32_TRANW_R(-2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANW_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANW_R(2,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANW_R(9,32,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANW_R(208,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipSprite32_TRANW_R(210,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/

/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite8_AND_R(-2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_AND_R(0,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_AND_R(2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_AND_R(9,8,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_AND_R(232,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_AND_R(234,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayClipISprite8_OR_R(-2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_OR_R(0,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_OR_R(2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_OR_R(9,8,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_OR_R(232,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_OR_R(234,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_XOR_R(-2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_XOR_R(0,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_XOR_R(2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_XOR_R(9,8,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_XOR_R(232,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_XOR_R(234,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite8_RPLC_R(-2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_RPLC_R(0,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_RPLC_R(2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_RPLC_R(9,8,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_RPLC_R(232,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_RPLC_R(234,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite8_BLIT_R(-2,0,8,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_BLIT_R(0,0,8,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_BLIT_R(2,0,8,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_BLIT_R(9,8,8,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_BLIT_R(232,0,8,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_BLIT_R(234,0,8,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite8_MASK_R(-2,0,8,msprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_MASK_R(0,0,8,msprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_MASK_R(2,0,8,msprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_MASK_R(9,8,8,msprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_MASK_R(232,0,8,msprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_MASK_R(234,0,8,msprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipISprite8_TRANB_R(-2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANB_R(0,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANB_R(2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANB_R(9,8,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANB_R(232,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANB_R(234,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipISprite8_TRANW_R(-2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANW_R(0,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANW_R(2,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANW_R(9,8,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANW_R(232,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite8_TRANW_R(234,0,8,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite16_AND_R(-2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_AND_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_AND_R(2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_AND_R(9,16,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_AND_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_AND_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayClipISprite16_OR_R(-2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_OR_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_OR_R(2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_OR_R(9,16,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_OR_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_OR_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_XOR_R(-2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_XOR_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_XOR_R(2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_XOR_R(9,16,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_XOR_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_XOR_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite16_RPLC_R(-2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_RPLC_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_RPLC_R(2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_RPLC_R(9,16,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_RPLC_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_RPLC_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite16_BLIT_R(-2,0,16,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_BLIT_R(0,0,16,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_BLIT_R(2,0,16,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_BLIT_R(9,16,16,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_BLIT_R(224,0,16,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_BLIT_R(226,0,16,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite16_MASK_R(-2,0,16,msprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_MASK_R(0,0,16,msprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_MASK_R(2,0,16,msprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_MASK_R(9,16,16,msprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_MASK_R(224,0,16,msprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_MASK_R(226,0,16,msprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipISprite16_TRANB_R(-2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANB_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANB_R(2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANB_R(9,16,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANB_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANB_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipISprite16_TRANW_R(-2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANW_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANW_R(2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANW_R(9,16,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANW_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite16_TRANW_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite32_AND_R(-2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_AND_R(0,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_AND_R(2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_AND_R(9,32,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_AND_R(208,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_AND_R(210,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayClipISprite32_OR_R(-2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_OR_R(0,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_OR_R(2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_OR_R(9,32,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_OR_R(208,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_OR_R(210,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_XOR_R(-2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_XOR_R(0,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_XOR_R(2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_XOR_R(9,32,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_XOR_R(208,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_XOR_R(210,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite32_RPLC_R(-2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_RPLC_R(0,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_RPLC_R(2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_RPLC_R(9,32,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_RPLC_R(208,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_RPLC_R(210,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite32_BLIT_R(-2,0,32,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_BLIT_R(0,0,32,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_BLIT_R(2,0,32,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_BLIT_R(9,32,32,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_BLIT_R(208,0,32,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_BLIT_R(210,0,32,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R(0xFFFFFFFF,0xFFFFFFFF);
    GrayClipISprite32_MASK_R(-2,0,32,msprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_MASK_R(0,0,32,msprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_MASK_R(2,0,32,msprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_MASK_R(9,32,32,msprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_MASK_R(208,0,32,msprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_MASK_R(210,0,32,msprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipISprite32_TRANB_R(-2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANB_R(0,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANB_R(2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANB_R(9,32,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANB_R(208,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANB_R(210,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    FillScreenWithGarbage_R(0x7E8F1C43,LCD_SIZE,GrayGetPlane(LIGHT_PLANE));
    FillScreenWithGarbage_R(0xA8F54897,LCD_SIZE,GrayGetPlane(DARK_PLANE));
    GrayClipISprite32_TRANW_R(-2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANW_R(0,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANW_R(2,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANW_R(9,32,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANW_R(208,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayClipISprite32_TRANW_R(210,0,32,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/


/*
    GrayFillScreen_R();
    GrayTile8x8_AND_R(0,0,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile8x8_OR_R(0,0,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayTile8x8_XOR_R(0,0,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile8x8_RPLC_R(0,0,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile8x8_BLIT_R(0,0,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile8x8_MASK_R(0,0,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile8x8_SMASK_R(0,0,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile8x8_TRANB_R(0,0,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile8x8_TRANW_R(0,0,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R();
    GrayTile16x16_AND_R(0,0,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile16x16_OR_R(0,0,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayTile16x16_XOR_R(0,0,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile16x16_RPLC_R(0,0,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile16x16_BLIT_R(0,0,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile16x16_MASK_R(0,0,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile16x16_SMASK_R(0,0,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile16x16_TRANB_R(0,0,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile16x16_TRANW_R(0,0,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R();
    GrayTile32x32_AND_R(0,0,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile32x32_OR_R(0,0,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayTile32x32_XOR_R(0,0,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile32x32_RPLC_R(0,0,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile32x32_BLIT_R(0,0,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile32x32_MASK_R(0,0,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile32x32_SMASK_R(0,0,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayTile32x32_TRANB_R(0,0,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayTile32x32_TRANW_R(0,0,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/

/*
    GrayFillScreen_R();
    GrayITile8x8_AND_R(0,0,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile8x8_OR_R(0,0,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayITile8x8_XOR_R(0,0,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile8x8_RPLC_R(0,0,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile8x8_BLIT_R(0,0,isprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile8x8_MASK_R(0,0,msprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile8x8_TRANB_R(0,0,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile8x8_TRANW_R(0,0,isprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R();
    GrayITile16x16_AND_R(0,0,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile16x16_OR_R(0,0,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayITile16x16_XOR_R(0,0,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile16x16_RPLC_R(0,0,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile16x16_BLIT_R(0,0,isprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile16x16_MASK_R(0,0,msprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile16x16_TRANB_R(0,0,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile16x16_TRANW_R(0,0,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/
/*
    GrayFillScreen_R();
    GrayITile32x32_AND_R(0,0,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile32x32_OR_R(0,0,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GrayITile32x32_XOR_R(0,0,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile32x32_RPLC_R(0,0,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile32x32_BLIT_R(0,0,isprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile32x32_MASK_R(0,0,msprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayFillScreen_R();
    GrayITile32x32_TRANB_R(0,0,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
    GrayClearScreen_R();
    GrayITile32x32_TRANW_R(0,0,isprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/


/*
    GrayClearScreen_R();
    GrayClipISprite16_OR_R(-2,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(0,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(9,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(224,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();

    GrayClearScreen_R();
    GrayClipISprite16_OR_R(226,0,16,isprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    ngetchx();
*/




//GrayOff();

//    ClearGrayScreen();
//    SpriteX8_MIRROR_HV_R(16,(unsigned char*)sprite_16,2,(unsigned char*)dest_16);
    /*
    asm("
    move.l %%a2,-(%%sp)
    lea sprite_16(%%pc),%%a0
    lea dest_16(%%pc),%%a1
    lea dest2_16(%%pc),%%a2
| 1
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

| 2
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

| 3
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

| 4
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

| 5
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

| 6
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

| 7
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

| 8
    move.l (%%a0)+,%%d0
    or.l (%%a1)+,%%d0
    move.l %%d0,(%%a2)+

    move.l (%%sp)+,%%a2
    " : : : "d0","a0","a1");
    */


/*
ClrScr();
    for(i=0; i<240; i++) {
        FastFilledRect_Draw_R(LCD_MEM,0,0,i,99);
    }

        FastFillRect(LCD_MEM,0,0,239,99,A_NORMAL);
*/
//    ClrScr();
/*    asm("or.w %d0,(%a0); eor.w %d0,(%a0); and.w %d0,(%a0);
         or.w %d1,(%a0); eor.w %d1,(%a0); and.w %d1,(%a0);");*/
// 8150, B150, C150, 8350, B350, C350.
//    asm("move.w #0x0400,%%d0; trap #1;" : : : "d0","d1");

/*
    if(!GrayOn()) goto end;

    FadeOutToBlack_CWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToWhite_CCWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToBlack_CCWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToWhite_CWS1_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToBlack_LR_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToWhite_RL_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToBlack_RL_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToWhite_LR_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,20);

    FadeOutToBlack_TB_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

    FadeOutToWhite_BT_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

    FadeOutToBlack_BT_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

    FadeOutToWhite_TB_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),128,30,200);

    GrayOff();
*/
/*
    end:
    SetIntVec(AUTO_INT(5),s5);
    return;
*/
/*
SlowFillRect_R(LCD_MEM,0,17,159,81,A_NORMAL);
//ScrRectFill(&(SCR_RECT){{0,17,159,81}},&(SCR_RECT){{0,0,239,127}},A_XOR);
FillLines2(&(WIN_RECT){0,81,159,81},
           &(WIN_RECT){0,17,159,17},
           &(SCR_RECT){{0,0,239,127}},
           A_XOR);
*/
/*
asm("bset %d0,(%a0);        bclr %d0,(%a0);        bchg %d0,(%a0);
     bset %d2,0(%a0,%a1.w); bclr %d2,0(%a0,%a1.w); bchg %d2,0(%a0,%a1.w)");
// 01D0, 0190, 0150, 05F09000, 05B09000, 05709000.
*/
/*
memset(&lcd[0],0xFFFF,LCD_SIZE);
memset(&lcd[1],0xFFFF,LCD_SIZE);

    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000*20);
    for (i = -300; i < 300; i++) {
        for (j = -300; j < 300; j++) {
            GrayClipSprite32_MASK_R(i,j,32,sprite_32,sprite_32,sprite_32,sprite_32,&lcd[0],&lcd[1]);
        }
    }

GrayOn();
memcpy(GetPlane(LIGHT_PLANE),&lcd[0],LCD_SIZE);
memcpy(GetPlane(DARK_PLANE),&lcd[1],LCD_SIZE);
FontSetSys(F_4x6);
DrawStr(0,0,z,A_REPLACE);
DrawStr(0,6,z2,A_REPLACE);
ngetchx();
GrayOff();
*/
/*
    asm("move.w #0xFFFF,%%d0
    blt.s __ok1__
    nop
    __ok1__:
    move.w #0x7FFF,%%d0
    blt.s __ok2__
    nop
    __ok2__:
    nop" : : : "d0","cc");
*/

//EXT_XORPIX(LCD_MEM,x,y);
/*
FastLine_Invert_R(LCD_MEM,0,0,159,99);
FastLine_Draw_R(LCD_MEM,0,0,159,99);
FastLine_Erase_R(LCD_MEM,0,0,159,99);
FastLine_Invert_R(LCD_MEM,0,0,79,99);
FastLine_Draw_R(LCD_MEM,0,0,79,99);
FastLine_Erase_R(LCD_MEM,0,0,79,99);
*/

/*
GrayOn();
memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
GraySpriteX8_AND(0,0,16,(unsigned char*)sprite_16,(unsigned char*)sprite_16_2,2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
GraySpriteX8_BLIT(16,16,16,(unsigned char*)sprite_16,(unsigned char*)sprite_16_2,(unsigned char*)dest_32,2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
GraySpriteX8_MASK(32,32,16,(unsigned char*)sprite_16,(unsigned char*)sprite_16_2,(unsigned char*)sprite_16,(unsigned char*)sprite_16_2,2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
GKeyIn(NULL,0);

GrayClearScreen();
GraySpriteX8_OR(48,48,16,(unsigned char*)sprite_16,(unsigned char*)sprite_16_2,2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
GraySpriteX8_XOR(64,64,16,(unsigned char*)sprite_16,(unsigned char*)sprite_16_2,2,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
GKeyIn(NULL,0);

GrayOff();
*/
/*
ClrScr();
Sprite32_OR_R(0,0,32,sprite_32,LCD_MEM);
SpriteX8X8_ROTATE_LEFT_R(32,(unsigned char*)sprite_32,4,(unsigned char*)dest_32);
SpriteX8_MIRROR_H_R(32,(unsigned char*)dest_32,4,(unsigned char*)dest2_32);
Sprite32_OR_R(32,32,32,dest2_32,LCD_MEM);

SpriteX8X8_RL_MH_R(32,(unsigned char*)sprite_32,4,(unsigned char*)dest_32);
Sprite32_OR_R(32,0,32,dest_32,LCD_MEM);

GKeyIn(NULL,0);
*/
/*
ClrScr();
Sprite32_OR_R(0,0,32,sprite_32,LCD_MEM);
Sprite32_OR_R(0,32,32,sprite_32,LCD_MEM);

SpriteX8X8_ROTATE_RIGHT_R(32,(unsigned char*)sprite_32,4,(unsigned char*)dest_32);
Sprite32_OR_R(32,0,32,dest_32,LCD_MEM);
SpriteX8X8_ROTATE_RIGHT_R(32,(unsigned char*)dest_32,4,(unsigned char*)dest2_32);
Sprite32_OR_R(64,0,32,dest2_32,LCD_MEM);
//memcpy(sprite_32,dest2_32,32*4);
SpriteX8X8_ROTATE_RIGHT_R(32,(unsigned char*)dest2_32,4,(unsigned char*)dest_32);
Sprite32_OR_R(96,0,32,dest_32,LCD_MEM);
SpriteX8X8_ROTATE_RIGHT_R(32,(unsigned char*)dest_32,4,(unsigned char*)dest2_32);
Sprite32_OR_R(128,0,32,dest2_32,LCD_MEM);

SpriteX8X8_ROTATE_LEFT_R(32,(unsigned char*)sprite_32,4,(unsigned char*)dest_32);
Sprite32_OR_R(32,32,32,dest_32,LCD_MEM);
SpriteX8X8_ROTATE_LEFT_R(32,(unsigned char*)dest_32,4,(unsigned char*)dest2_32);
Sprite32_OR_R(64,32,32,dest2_32,LCD_MEM);
//memcpy(sprite_32,dest2_32,32*4);
SpriteX8X8_ROTATE_LEFT_R(32,(unsigned char*)dest2_32,4,(unsigned char*)dest_32);
Sprite32_OR_R(96,32,32,dest_32,LCD_MEM);
SpriteX8X8_ROTATE_LEFT_R(32,(unsigned char*)dest_32,4,(unsigned char*)dest2_32);
Sprite32_OR_R(128,32,32,dest2_32,LCD_MEM);

GKeyIn(NULL,0);
*/
/*
SpriteX8X8_ROTATE_LEFT_R(32,(unsigned char*)sprite_32,4,(unsigned char*)dest_32);
SpriteX8X8_ROTATE_RIGHT_R(32,(unsigned char*)sprite_32,4,(unsigned char*)dest_32);
DrawClipRect(&(WIN_RECT){31,31,64,64},&(SCR_RECT){{0,0,239,127}},A_REPLACE);
Sprite32_OR_R(32,32,32,dest_32,LCD_MEM);
Sprite32_OR_R(96,32,32,sprite_32,LCD_MEM);
*/
/*
DoubleSpriteDimensionsX8_R(16,(unsigned char*)sprite_16,2,(unsigned char*)dest_32);
Sprite16_OR_R(0,0,16,sprite_16,LCD_MEM);
Sprite32_OR_R(0,0,32,dest_32,LCD_MEM);

DoubleSpriteDimensions16x16_R(sprite_16,dest_32);
Sprite16_XOR_R(0,0,16,sprite_16,LCD_MEM);
Sprite32_XOR_R(0,0,32,dest_32,LCD_MEM);
*/
/*
    FastCopyScreen(LCD_MEM,lcd);
    ClrScr();

    FastCopyScreen(lcd,LCD_MEM);

    FastCopyScreen_R(LCD_MEM,lcd);
    ClrScr();

    FastCopyScreen_R(lcd,LCD_MEM);
*/
    /*
    GrayOn();
    memset(GetPlane(LIGHT_PLANE),0xAAAA,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0x5555,LCD_SIZE);
    FastCopyGrayScreen(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),lcd);

    memset(GetPlane(LIGHT_PLANE),0x5555,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xAAAA,LCD_SIZE);
    FastCopyGrayScreen_R(GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE),lcd);

    GrayOff();
    */
/*
    for (i=20000;(i--);) {
        x1 = random(10);
        x2 = random(10);
        y1 = random(80);
//        if (x1 > x2) { j = x1; x1 = x2; x2 = j; }
//        if (y1 > y2) { j = y1; y1 = y2; y2 = j; }

//        s.l = (long)x1<<24|(long)y1<<16|x2<<8|y2;
//        ScrRectFill(&s,&(SCR_RECT){{0,0,239,127}},A_NORMAL);

        FastInvertRectX8(LCD_MEM,x1,y1,20,x2);
        if(x2) FastFilledRect_R(LCD_MEM,x1<<3,y1,(x1<<3)+(x2<<3)-1,y1+20,A_XOR);
    }

    ngetchx();
*/
/*
    for (i=5000;(i--);) {
        x1 = random(160);
        x2 = random(160);
        y1 = random(100);
        y2 = random(100);
        if (x1 > x2) { j = x1; x1 = x2; x2 = j; }
        if (y1 > y2) { j = y1; y1 = y2; y2 = j; }

        s.l = (long)x1<<24|(long)y1<<16|x2<<8|y2;
        ScrRectFill(&s,&(SCR_RECT){{0,0,239,127}},A_NORMAL);

        FastFilledRect(LCD_MEM,x1,y1,x2,y2,A_REVERSE);
    }
    asm("0: bra.s 0b");

    FastOutlinedRect(LCD_MEM,1,1,9,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,9,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,17,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,17,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,31,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,31,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,33,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,33,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,47,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,47,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,63,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,63,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,65,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,65,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,79,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,79,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,81,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,81,99},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastOutlinedRect(LCD_MEM,1,1,159,99,A_NORMAL);
    DrawClipRect(&(WIN_RECT){1,1,159,99},&(SCR_RECT){{0,0,239,127}},A_XOR);
*/
/*
    FastFilledRect(LCD_MEM,1,1,3,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,3,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,10,2,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,10,2}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,17,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,17,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,25,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,25,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,32,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,32,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,43,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,43,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,55,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,55,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,66,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,66,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,77,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,77,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,77,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,77,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,88,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,88,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,88,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,88,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,99,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,99,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,110,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,110,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,121,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,121,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,132,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,132,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,143,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,143,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,154,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,154,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,165,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,165,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,31,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,31,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,63,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,63,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,64,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,64,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    FastFilledRect(LCD_MEM,1,1,65,4,A_NORMAL);
    ScrRectFill(&(SCR_RECT){{1,1,65,4}},&(SCR_RECT){{0,0,239,127}},A_XOR);


    FastFilledRect(LCD_MEM,1,1,62,97,A_XOR);
    ScrRectFill(&(SCR_RECT){{1,1,62,97}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    memset(LCD_MEM,0xAAAA,LCD_SIZE);
    FastFilledRect(LCD_MEM,1,1,63,98,A_REPLACE);
    ScrRectFill(&(SCR_RECT){{1,1,63,98}},&(SCR_RECT){{0,0,239,127}},A_XOR);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    FastFilledRect(LCD_MEM,0,0,239,127,A_REVERSE);
    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ScrRectFill(&(SCR_RECT){{0,0,239,127}},&(SCR_RECT){{0,0,239,127}},A_REVERSE);
*/

/*
    for (i=5000;(i--);) {
        x1 = random(160);
        x2 = random(160);
        y1 = random(100);
        y2 = random(100);
        DrawLine(x1,y1,x2,y2,A_XOR);
        FastDrawLine_ExtendeD(LCD_MEM,x1,y1,x2,y2,A_XOR);
    }
    asm("0: bra 0b");
*/

/*    DrawLine(1,98,159,97,A_XOR);
    FastDrawLine(LCD_MEM,1,98,159,97,A_XOR);*/

    /*
    _Sprite8Get(6,0,8,LCD_MEM,dest2);
    _Sprite8_OR(80,40,8,dest2,LCD_MEM);

    Sprite8Get(6,0,8,LCD_MEM,dest2);
    _Sprite8_OR(0,40,8,dest2,LCD_MEM);

    _Sprite8Get(6,100-8,8,LCD_MEM,dest2);
    _Sprite8_OR(120,40,8,dest2,LCD_MEM);

    Sprite8Get(6,100-8,8,LCD_MEM,dest2);
    _Sprite8_OR(40,40,8,dest2,LCD_MEM);
    */


/*
GrayOff();

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    Sprite8_BLIT_R(0,0,8,sprite_8,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    Sprite16_BLIT_R(0,0,16,sprite_16,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    Sprite32_BLIT_R(0,0,32,sprite_32,0,LCD_MEM);
*/
/*
GrayOff();

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite8_BLIT_R(-4,0,8,sprite_8,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite16_BLIT_R(-4,0,16,sprite_16,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite32_BLIT_R(-4,0,32,sprite_32,0,LCD_MEM);


    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite8_BLIT_R(0,0,8,sprite_8,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite16_BLIT_R(0,0,16,sprite_16,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite32_BLIT_R(0,0,32,sprite_32,0,LCD_MEM);


    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite8_BLIT_R(236,0,8,sprite_8,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite16_BLIT_R(236,0,16,sprite_16,0,LCD_MEM);

    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    ClipSprite32_BLIT_R(236,0,32,sprite_32,0,LCD_MEM);
*/


/*
if (!GrayOn()) goto end;
GrayClearScreen_R();
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite16_BLIT_R(0,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite8_BLIT_R(0,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite32_BLIT_R(0,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite16_BLIT_R(-4,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite8_BLIT_R(-4,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite32_BLIT_R(-4,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));


    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite16_BLIT_R(0,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite8_BLIT_R(0,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite32_BLIT_R(0,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));


    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite16_BLIT_R(232,0,16,sprite_16,sprite_16,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite8_BLIT_R(236,0,8,sprite_8,sprite_8,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GrayClipSprite32_BLIT_R(228,0,32,sprite_32,sprite_32,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
*/
/*
    ClrScr();
    GrayOn();
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite16_AND_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0,LCD_SIZE);
    GraySprite16_OR_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite16_XOR_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0x0,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0x0,LCD_SIZE);
    GraySprite16_TRANW_R(0,0,16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite16_BLIT_R(0,0,16,sprite_16,sprite_16,0,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite16_MASK_R(0,0,16,sprite_16,sprite_16,sprite_16,sprite_16,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));


    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite8_AND_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0,LCD_SIZE);
    GraySprite8_OR_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite8_XOR_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0x0,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0x0,LCD_SIZE);
    GraySprite8_TRANW_R(0,0,8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite8_BLIT_R(0,0,8,sprite_8,sprite_8,0,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite8_MASK_R(0,0,8,sprite_8,sprite_8,sprite_8,sprite_8,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));


    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite32_AND_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0,LCD_SIZE);
    GraySprite32_OR_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    GraySprite32_XOR_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0x0,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0x0,LCD_SIZE);
    GraySprite32_TRANW_R(0,0,32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
//    GrayClipSprite32_BLIT_R(0,0,32,sprite_32,sprite_32,0,0,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));
//    memset(GetPlane(LIGHT_PLANE),0xFFFF,LCD_SIZE);
//    memset(GetPlane(DARK_PLANE),0xFFFF,LCD_SIZE);
    GraySprite32_MASK_R(0,0,32,sprite_32,sprite_32,sprite_32,sprite_32,GetPlane(LIGHT_PLANE),GetPlane(DARK_PLANE));

    GrayOff();
*/
/*
ClrScr();
DoubleSpriteDimensions16x16_R(sprite_16,dest_32);
Sprite16_OR_R(0,0,16,sprite_16,LCD_MEM);
Sprite32_OR_R(0,0,32,dest_32,LCD_MEM);
*/
/*
    memset(LCD_MEM,0xFFFF,LCD_SIZE);

    Sprite32_AND(1,0,32,sprite_32,LCD_MEM);
    _Sprite32_AND(81,0,32,sprite_32,LCD_MEM);
    _Sprite32_AND(1,40,32,sprite_32,LCD_MEM);
*/
/*
    Sprite32_OR(0,0,32,sprite_32,LCD_MEM);
    DoubleSpriteDimensionsX8_R(32,(UCHAR*)sprite_32,4,(UCHAR*)dest_64);
    SpriteX8_OR(40,0,64,(UCHAR*)dest_64,8,LCD_MEM);
*/
/*
    Sprite8_OR(0,0,8,sprite_8,LCD_MEM);
    DoubleSpriteDimensionsX8_R(8,(UCHAR*)sprite_8,1,(UCHAR*)dest_16);
    Sprite16_OR(40,0,16,dest_16,LCD_MEM);
*/
/*
    Sprite32_OR(0,0,32,sprite_32,LCD_MEM);
    SpriteX8_MIRROR_H(32,(UCHAR*)sprite_32,4,(UCHAR*)dest_32);
    Sprite32_OR(40,0,32,dest_32,LCD_MEM);
    SpriteX8_MIRROR_H_R(32,(UCHAR*)sprite_32,4,(UCHAR*)dest_32);
    Sprite32_XOR(40,0,32,dest_32,LCD_MEM);
*/
/*
    GKeyIn(NULL,0);
    ClrScr();
*/
/*
    Sprite16_OR(0,0,16,sprite_16,LCD_MEM);
    SpriteX8_MIRROR_V(16,(UCHAR*)sprite_16,2,(UCHAR*)dest_16);
    Sprite16_OR(40,0,16,dest_16,LCD_MEM);
    SpriteX8_MIRROR_V_R(16,(UCHAR*)sprite_16,2,(UCHAR*)dest_16);
    Sprite16_XOR(40,0,16,dest_16,LCD_MEM);

    GKeyIn(NULL,0);
*/
//    ClrScr();

/*    _Sprite16_OR(0,0,16,sprite_16,LCD_MEM);
    _Sprite16_OR(1,1,16,sprite_16,LCD_MEM);*/
/*    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    _Sprite16_OR(12,0,16,sprite_16,LCD_MEM);
    _Sprite16_AND(12,0,16,sprite_16,LCD_MEM);*/
/*    _Sprite16_AND(13,16,16,sprite_16,LCD_MEM);
    _Sprite16_AND(14,32,16,sprite_16,LCD_MEM);
    _Sprite16_AND(15,48,16,sprite_16,LCD_MEM);
    _Sprite16_AND(16,64,16,sprite_16,LCD_MEM);
    _Sprite16_AND(17,80,16,sprite_16,LCD_MEM);*/
/*Sprite16_AND(12,16,16,sprite_16,LCD_MEM);*/

/*
    for (i=0,j=0;i<=127;i++,j++) {
        FastDrawHLine_faster_stkparm(LCD_MEM,0,i,j,A_NORMAL);
    }

    for (i=127,j=127;i<=239;i++,j--) {
        FastDrawHLine_faster_stkparm(LCD_MEM,0,i,j,A_NORMAL);
    }
*/
    /*
    memset(LCD_MEM,0xFFFF,LCD_SIZE);
    Sprite8_AND(0,0,8,sprite_8,LCD_MEM);
    Sprite8_AND(1,8,8,sprite_8,LCD_MEM);
    Sprite8_AND(2,16,8,sprite_8,LCD_MEM);
    Sprite8_AND(3,24,8,sprite_8,LCD_MEM);
    Sprite8_AND(4,32,8,sprite_8,LCD_MEM);
    Sprite8_AND(5,40,8,sprite_8,LCD_MEM);
    Sprite8_AND(6,48,8,sprite_8,LCD_MEM);
    Sprite8_AND(7,56,8,sprite_8,LCD_MEM);
    Sprite8_AND(8,0,8,sprite_8,LCD_MEM);
    Sprite8_AND(9,8,8,sprite_8,LCD_MEM);
    Sprite8_AND(10,16,8,sprite_8,LCD_MEM);
    Sprite8_AND(11,24,8,sprite_8,LCD_MEM);
    Sprite8_AND(12,32,8,sprite_8,LCD_MEM);
    Sprite8_AND(13,40,8,sprite_8,LCD_MEM);
    Sprite8_AND(14,48,8,sprite_8,LCD_MEM);
    Sprite8_AND(15,56,8,sprite_8,LCD_MEM);

    _Sprite8_AND(16,0,8,sprite_8,LCD_MEM);
    _Sprite8_AND(17,8,8,sprite_8,LCD_MEM);
    _Sprite8_AND(18,16,8,sprite_8,LCD_MEM);
    _Sprite8_AND(19,24,8,sprite_8,LCD_MEM);
    _Sprite8_AND(20,32,8,sprite_8,LCD_MEM);
    _Sprite8_AND(21,40,8,sprite_8,LCD_MEM);
    _Sprite8_AND(22,48,8,sprite_8,LCD_MEM);
    _Sprite8_AND(23,56,8,sprite_8,LCD_MEM);
    _Sprite8_AND(24,0,8,sprite_8,LCD_MEM);
    _Sprite8_AND(25,8,8,sprite_8,LCD_MEM);
    _Sprite8_AND(26,16,8,sprite_8,LCD_MEM);
    _Sprite8_AND(27,24,8,sprite_8,LCD_MEM);
    _Sprite8_AND(28,32,8,sprite_8,LCD_MEM);
    _Sprite8_AND(29,40,8,sprite_8,LCD_MEM);
    _Sprite8_AND(30,48,8,sprite_8,LCD_MEM);
    _Sprite8_AND(31,56,8,sprite_8,LCD_MEM);

    GKeyIn(NULL,0);
    */

    /*
    Sprite32_OR(1,0,32,sprite,LCD_MEM);
    _Sprite32_OR(81,0,32,sprite,LCD_MEM);
    _Sprite32_OR(1,40,32,sprite,LCD_MEM);

    GKeyIn(NULL,0);
    */
    /*
    for (i=0; i < 1000; i++) {
        FastDrawVLine(LCD_MEM,random(160),random(100),random(100),A_NORMAL);
    }
//    */
//memset(LCD_MEM,0xFFFF,LCD_SIZE);
//    t1 = FiftyMsecTick;

//GrayOff();
    t1 = counter;
    OSFreeTimer(USER_TIMER);
    OSRegisterTimer(USER_TIMER,1000*20);
//    for (i = 159-0+1; (i--);) {
    for (i = 2500+1; (i--);) {
//        SpriteX8_MIRROR_V(32,(unsigned char *)sprite,4,(unsigned char *)dest);
        /*Sprite32_OR(0,20,32,csprite,LCD_MEM);
        Sprite32_OR(80,20,32,dest,LCD_MEM);
        GKeyIn(NULL,0);*/

//        clip_ocircle(LCD_MEM,30,30,25);
//        ClipFastOutlinedCircle_R(LCD_MEM,30,30,25);
//        FastOutlinedCircle_R(LCD_MEM,30,30,25);
//        old_ocircle(LCD_MEM,30,30,25);
/*        DrawClipEllipse (30,30,25,25,&(SCR_RECT){{0,0,159,99}},A_NORMAL);
ClrScr();
        DrawClipEllipse (30,30,25,25,&(SCR_RECT){{0,0,159,99}},A_NORMAL);
        old_ocircle(LCD_MEM,30,30,25);*/

//        for (j = 99-0+1; (j--);) {

//            FastFillRect_R(LCD_MEM,0,0,i,j,A_NORMAL);
//            FastFilledRect_Draw_R(LCD_MEM,0,0,i,j);
//            FastFilledRect_Erase_R(LCD_MEM,0,0,i,j);
//            FastFilledRect_Invert_R(LCD_MEM,0,0,i,j);
//            Sprite8_OR(i,j,8,sprite_8,LCD_MEM);
//            Sprite16_AND(i,j,16,sprite_16,LCD_MEM);
//            Sprite32_XOR(i,j,32,sprite_32,LCD_MEM);
//            _SpriteX8_OR(i,j,32,(unsigned char *)sprite_32,4,LCD_MEM);
//        }
//        ClrScr();
//        if ((OSTimerExpired(USER_TIMER))) break;
    }

/*for(i=160;(i--);)
for(j=100;(j--);)
FastDrawHLine_faster_regparm(LCD_MEM,0,i,j,A_REVERSE);
for(i=0;i<160;i++)
for(j=100;(j--);)
FastDrawHLine_faster_regparm(LCD_MEM,i,0,j,A_REVERSE);
*/
/*
    for (i = 0; i < 128; i++) {
        for (j = 0; j < 240; j++) {
            FastDrawHLine_faster_regparm(LCD_MEM,0,j,i,A_NORMAL);
        }
    }
    */
//for(x=160;(x--);;)
//    for (i = 127+1; (i--);) {
//        for (j = 239+1; (j--);) {
//            FastFilledRect_R(LCD_MEM,0,0,j,i,A_XOR);
//            FastFilledRect(LCD_MEM,0,0,j,i,A_NORMAL);
//        }
//    }

//    t1 = FiftyMsecTick - t1;
    t1 = counter - t1;

//    ClrScr();
//memset(LCD_MEM,0xFFFF,LCD_SIZE);

//    t2 = FiftyMsecTick;
    t2 = counter;
//    i = 0;
//    OSFreeTimer(USER_TIMER);
//    OSRegisterTimer(USER_TIMER,10*20);
//    for (i = 159-0+1; (i--);) {
    for (i = 2500+1; (i--);) {
//        SpriteX8_MIRROR_V(32,(unsigned char *)sprite,4,(unsigned char *)dest);
        /*Sprite32_OR(0,20,32,sprite,LCD_MEM);
        Sprite32_OR(80,20,32,dest,LCD_MEM);
        GKeyIn(NULL,0);*/
//        Circle_Clipped(LCD_MEM,30,30,25);
//        DrawClipEllipse(30,30,25,25,&(SCR_RECT){{0,0,159,99}},A_NORMAL);
//        for (j = 99-0+1; (j--);) {
/*            SCR_RECT s = {{0,0,i,j}};
            ScrRectFill(&s,&(SCR_RECT){{0,0,239,127}},A_NORMAL);*/
//            _Sprite8_OR(i,j,8,sprite_8,LCD_MEM);
//            _Sprite16_AND(i,j,16,sprite_16,LCD_MEM);
//            _Sprite32_XOR(i,j,32,sprite_32,LCD_MEM);
//            SpriteX8_OR(i,j,32,(unsigned char *)sprite_32,4,LCD_MEM);
//        }
//        ClrScr();
//        if ((OSTimerExpired(USER_TIMER))) break;
    }
/*
    for (i = 0; i < 128; i++) {
        for (j = 0; j < 240; j++) {
            FastDrawHLine(LCD_MEM,0,j,i,A_NORMAL);
        }
    }
*/
//    s = (SCR_RECT){{0,0,239,127}};
//    for (i = 127+1; (i--);) {
//        s = (SCR_RECT){{0,0,239,i}};
//        for (j = 239+1; (j--);) {
//            SCR_RECT s = (SCR_RECT){{0,0,j,i}};
//            ScrRectFill(&s,&(SCR_RECT){{0,0,239,127}},A_XOR);
//            s.l -= 0x00000100;
//        }
//        s.l -= 0x00000001;
//    }
    t2 = counter - t2;
//    printf_xy(0,0,"%lu",t1);
    printf_xy(0,0,"%hu",t1);
//    printf_xy(0,10,"%lu",FiftyMsecTick-t2);
    printf_xy(0,10,"%hu",t2);

//    end:
//    GrayOff();
    SetIntVec(AUTO_INT(5),s5);
    GKeyFlush();

    GKeyIn(NULL,0);
}
