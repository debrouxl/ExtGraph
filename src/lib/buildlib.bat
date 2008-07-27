@REM @echo off
@echo ======= building extgraph library =======
@REM 2.00 Beta 5: fixing (temporarily ?) a regression of GCC 4.0 using directory changes.
cd Misc
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c versiondef.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfill.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfillmf.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfill_R.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfillmf_R.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfill_noshade_R.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfillmf_noshade_R.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c FilledTriangle_R.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c ClipFilledTriangle_R.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c GrayFilledTriangle_R.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c GrayClipFilledTriangle_R.c
cd ..\Grayutil
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawrect2b.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c grayinvertrect2b.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawline2b.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c grayfastdrawline2b.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c grayfastdrawhline2b.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawstr2b.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawstrext2b.c
cd ..\Rect
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c FastOutlineRect.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c FastOutlineRect_R.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c GrayFastOutlineRect_R.c
tigcc -Os -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections -Wa,--all-relocs -D_GENERIC_ARCHIVE -c GrayFastFillRect_R.c
cd ..

..\..\bin\m68k-coff-ar -rv extgraph.a Misc\versiondef.o Misc\floodfill.o Misc\floodfillmf.o Misc\floodfill_R.o Misc\floodfillmf_R.o Misc/floodfill_noshade_R.o Misc/floodfillmf_noshade_R.o Misc\FilledTriangle_R.o Misc\ClipFilledTriangle_R.o Misc\GrayFilledTriangle_R.o Misc\GrayClipFilledTriangle_R.o
..\..\bin\m68k-coff-ar -rv extgraph.a Grayutil\graydrawrect2b.o Grayutil\grayinvertrect2b.o Grayutil\graydrawline2b.o Grayutil\grayfastdrawline2b.o Grayutil\grayfastdrawhline2b.o Grayutil\graydrawstr2b.o Grayutil\graydrawstrext2b.o
..\..\bin\m68k-coff-ar -rv extgraph.a Rect\FastOutlineRect.o Rect\FastOutlineRect_R.o Rect\GrayFastOutlineRect_R.o Rect\GrayFastFillRect_R.o

copy extgraph.a ..\..\lib
REM del extgraph.a
@echo on
