@echo off
cd lib
call buildlib.bat
cd..
@echo off
cd demos
call builddemos.bat
cd..
@echo off
call cleanup.bat
@echo on
