| C prototype: void GrayClipFastOutlinedCircle_R(void *plane asm("%a0"),short xcenter asm("%d0"),short ycenter asm("%d1"),short radius asm("%d2"), void(*drawfunc)(short x1 asm("%d0"), short x2 asm("%d1"), void * addrs asm("%a0")) asm("%a2"));
|
| Routine based on Exploder's routine written in C, using EXT_SETPIX.
| Rewritten in plain assembly by Lionel, using an algorithm different from
| that of Exploder's routine.

.text
.globl GrayClipFastOutlinedCircle_R
.even

GrayClipFastOutlinedCircle_R:
| Not yet implemented, thanks to Oliver Hoog for the report.
    rts
