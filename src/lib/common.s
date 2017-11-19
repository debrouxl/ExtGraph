| The usual definitions, for a 240-pixel-wide plane directly usable for screen output.
.if PLANE_BYTE_WIDTH == 30

| Compute 15 * height as (16-1).
.macro COMPUTE_HALF_PLANE_BYTE_WIDTH inoutreg, auxreg
    move.w   \inoutreg,\auxreg
    lsl.w    #4,\inoutreg
    sub.w    \auxreg,\inoutreg
.endm

| Definitions for a 272-pixel-wide plane used by the tilemap engine.
.elseif PLANE_BYTE_WIDTH == 34

| Compute 17 * height as (16+1).
.macro COMPUTE_HALF_PLANE_BYTE_WIDTH inoutreg, auxreg
    move.w   \inoutreg,\auxreg
    lsl.w    #4,\inoutreg
    add.w    \auxreg,\inoutreg
.endm

| Definitions for a 320-pixel-wide plane (two 89/89T screens).
.elseif PLANE_BYTE_WIDTH == 40

| Compute 20 * height as (4+1)*4.
| lsl.w #2,\inoutreg would be smaller, but slightly slower, than these pairs of add.w \inoutreg,\inoutreg.
.macro COMPUTE_HALF_PLANE_BYTE_WIDTH inoutreg, auxreg
    move.w   \inoutreg,\auxreg
    add.w    \inoutreg,\inoutreg
    add.w    \inoutreg,\inoutreg
    add.w    \auxreg,\inoutreg
    add.w    \inoutreg,\inoutreg
    add.w    \inoutreg,\inoutreg
.endm

| Definitions for a 480-pixel-wide plane (two 92+/V200 screens).
.elseif PLANE_BYTE_WIDTH == 60

| Compute 30 * height as (16-1)*2.
.macro COMPUTE_HALF_PLANE_BYTE_WIDTH inoutreg, auxreg
    move.w   \inoutreg,\auxreg
    lsl.w    #4,\inoutreg
    sub.w    \auxreg,\inoutreg
    add.w    \inoutreg,\inoutreg
.endm

.else

.error "Unhandled PLANE_BYTE_WIDTH value"

.endif
