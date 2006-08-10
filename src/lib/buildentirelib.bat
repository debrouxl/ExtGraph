@echo off
tprbuilder extgraph.tpr
call buildlib.bat
copy extgraph.a ..\..\lib
@echo on
