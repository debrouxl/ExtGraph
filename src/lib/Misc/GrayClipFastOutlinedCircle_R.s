| C prototype: void GrayClipFastOutlinedCircle_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),short radius asm("%d2"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addrs asm("%a0")) asm("%a2"));
|
| Routine based on Exploder's routine written in C, using EXT_SETPIX.
| Rewritten in plain assembly by Lionel, using an algorithm different from
| that of Exploder's routine.
| Bench on a circle of radius 25 drawn at (30;30), real 89 HW2 AMS 2.05, 
| PRG_getStart() = 0xCE: 45 ticks to draw 2000 circles, ~1100 circles / sec.

.text
.globl GrayClipFastOutlinedCircle_R
.even

GrayClipFastOutlinedCircle_R:
| Not yet implemented, thanks to Oliver Hoog for the report.
    rts
