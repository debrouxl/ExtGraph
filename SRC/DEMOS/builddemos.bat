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
@call buildsep.bat demo12
@call buildsep.bat demo13
@call buildsep.bat demo14
@echo demo15
@call buildsep.bat demo15
@call buildsep.bat demo16
@call buildsep.bat demo17
@echo demo18
@call buildcmp.bat demo18
@call buildcmp.bat demo19
@call buildcmp.bat demo20
@call buildcmp.bat demo21
@call buildsep.bat demo22
@echo demo24
@call buildsep.bat demo24
@call buildsep.bat demo25
@tigcc demo26.asm ..\..\lib\extgraph.a ..\..\lib\tilemap.a
@move demo26.89z ..\..\bin89
@move demo26.9xz ..\..\bin92p
@move demo26.v2z ..\..\binv200
@pause
@echo on