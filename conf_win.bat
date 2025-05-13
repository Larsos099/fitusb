@echo off

set minGW-make=mingw32-make.exe
set "ninja=ninja.exe"
set "tool=0"

echo Checking for Ninja...
where.exe %ninja% >nul 2>&1
if %errorlevel% == 0 (
    echo Found Ninja
    set "tool=1"
    cmake --preset win32-ninja
    exit
)

echo Checking for MinGW Make...
where.exe %minGW-make% >nul 2>&1
if %errorlevel% == 0 (
    echo Found mingw32-make.exe
    set "tool=1"
    cmake --preset win32
    exit
)

if "%tool%" == "0" (
    echo Could not find either Ninja, nor %minGW-make%
    echo Please install one of them. (Preferred: Ninja)
)
