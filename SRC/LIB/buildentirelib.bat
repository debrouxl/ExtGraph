@echo off
tprbuilder extgraph.tpr
call buildib.bat
copy extgraph.a ..\..\lib
@echo on
