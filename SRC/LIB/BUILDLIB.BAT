@REM @echo off
@echo ======= building extgraph library =======
@REM 2.00 Beta 5: fixing (temporarily ?) a regression of GCC 4.0 using directory changes.
cd Misc
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c versiondef.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfill.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfillmf.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfill_R.c
tigcc -O3 -fno-omit-frame-pointer -Wall -W -Wwrite-strings -ftracer -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c floodfillmf_R.c
cd ..\Grayutil
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawrect2b.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c grayinvertrect2b.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawline2b.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c grayfastdrawline2b.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c grayfastdrawhline2b.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawstr2b.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c graydrawstrext2b.c
cd ..\Rect
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c FastOutlineRect.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c FastOutlineRect_R.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c GrayFastOutlineRect_R.c
tigcc -Os -fomit-frame-pointer -Wall -W -Wwrite-strings -ffunction-sections -fdata-sections --optimize-code --cut-ranges -Wa,--all-relocs -D_GENERIC_ARCHIVE -c GrayFastFillRect_R.c
cd ..

m68k-coff-ar -rv extgraph.a Misc\versiondef.o
m68k-coff-ar -rv extgraph.a Misc\floodfill.o
m68k-coff-ar -rv extgraph.a Misc\floodfillmf.o
m68k-coff-ar -rv extgraph.a Misc\floodfill_R.o
m68k-coff-ar -rv extgraph.a Misc\floodfillmf_R.o
m68k-coff-ar -rv extgraph.a Grayutil\graydrawrect2b.o
m68k-coff-ar -rv extgraph.a Grayutil\grayinvertrect2b.o
m68k-coff-ar -rv extgraph.a Grayutil\graydrawline2b.o
m68k-coff-ar -rv extgraph.a Grayutil\grayfastdrawline2b.o
m68k-coff-ar -rv extgraph.a Grayutil\grayfastdrawhline2b.o
m68k-coff-ar -rv extgraph.a Grayutil\graydrawstr2b.o
m68k-coff-ar -rv extgraph.a Grayutil\graydrawstrext2b.o
m68k-coff-ar -rv extgraph.a Rect\FastOutlineRect.o
m68k-coff-ar -rv extgraph.a Rect\FastOutlineRect_R.o
m68k-coff-ar -rv extgraph.a Rect\GrayFastOutlineRect_R.o
m68k-coff-ar -rv extgraph.a Rect\GrayFastFillRect_R.o

copy extgraph.a ..\..\lib
REM del extgraph.a
@echo on
