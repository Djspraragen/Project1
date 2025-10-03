@echo off 
rem Author LD Mabesele

REM create a bin folder if it does not exist
if not exist "..\bin" mkdir "..\bin"
echo Compilling.....

g++ -std=c++20 -fmodules-ts EntLib.cpp main.cpp -o ..\bin\app.exe

echo running....
..\bin\app.exe 20 30 5 10

pause
