@echo off
@echo ======= building demos =======
@call buildsep.bat demo1
@call buildcmp.bat demo2
@call buildcmp.bat demo3
@call buildcmp.bat demo4
@call buildcmp.bat demo5
@echo demo6
@call buildsep.bat demo6
@call buildcmp.bat demo7
@call buildcmp.bat demo8
@call buildcmp.bat demo9
@call buildcmp.bat demo10
@call buildsep.bat demo11
@echo demo12
@call buildsep.bat demo12 ..\..\lib\gray.o
@call buildsep.bat demo13 ..\..\lib\gray.o
@call buildsep.bat demo14 ..\..\lib\gray.o
@echo demo15
@call buildsep.bat demo15 ..\..\lib\gray.o
@call buildsep.bat demo16 ..\..\lib\gray.o
@call buildsep.bat demo17 ..\..\lib\gray.o
@echo demo18
@call buildcmp.bat demo18
@call buildcmp.bat demo19 ..\..\lib\gray.o
@call buildcmp.bat demo20
@call buildcmp.bat demo21
@call buildsep.bat demo22 ..\..\lib\gray.o
@echo demo24
@call buildsep.bat demo24 ..\..\lib\gray.o
@call buildsep.bat demo25 ..\..\lib\gray.o
@tigcc demo26.asm ..\..\lib\extgraph.a ..\..\lib\tilemap.a ..\..\lib\gray.o
@move demo26.89z ..\..\bin89
@move demo26.9xz ..\..\bin92pv200
@move demo26.v2z ..\..\bin92pv200
@call buildcmp.bat demo27
@call buildsep.bat demo28
@call buildsep.bat demo29
@call buildcmp.bat demo30
@call buildsep.bat demo31
@call buildcmp.bat demo32
@call buildcmp.bat demo33
@pause
@echo on
