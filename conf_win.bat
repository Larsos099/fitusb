@echo off

set "minGW-make=mingw-make32.exe"
set "ninja=ninja.exe"
set "tool=0"
if exist "%ninja%"(
    echo "Found Ninja"
    set "tool=1"
    cmake --preset win32-ninja
)
if exist "%minGW-make%" (
    echo "Found mingw-make32.exe"
    set "tool=1"
    cmake --preset win32
)
if "%tool%" == "0" (
    echo "Could not Find either Ninja, nor %minGW-make%\n Please Install one of them.\n (Preffered Ninja)"
)
else (
    
)