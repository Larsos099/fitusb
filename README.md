# fitusb (Flash (ISO-)Image to USB)

## 1. What is _fitusb_?
fitusb is a custom Multi-Platform Image to USB flash tool coded in C++
## 2. Why _fitusb_?
fitusb is very easy to use with its simple CLI Syntax

It also has basically no dependencies, its 100% Coded in Standard C++ Library, Standard C Library and WinAPI.

So it's basically native to everything that can run C++ and has lsblk installed.
## 3. How do I get _fitusb_?
you just build it from source (using CMake)
## 4. How do I use _fitusb_?
you use fitusb in the terminal of your choice like this:

Unix-Style:
```sh
fitusb <ISO-Image-path> <device> (-v)
```
Windows-Style:
```sh
fitusb [-v -gos -ld] <ISO-Image-Path> <Device-Number>
```
to list the devices, you use the following argument:
```sh
fitusb -ld
```
to get the OS detected by fitusb you use:
```sh
fitusb -gos
```
the order of the Arguments does not matter
# 5. Building _fitusb_
## 5.1 Requirements
- GCC/G++ v15.1 _(on Windows MinGW)_
- CMake 3.20
- _**(LINUX SYSTEMS ONLY) lsblk**_
- _(Optional, but Recommended): Ninja_
## 5.2 How to build _fitusb_
you go into the fitusb directory, where you cloned it into.

Now you type into your terminal of your choice: (Linux or MacOS)
```sh
./conf.sh
```
Now you type into your terminal of choice: (Windows)
```sh
.\conf_win.bat
```
then you type in (On Linux or MacOS)
```sh
./build.sh
```
or if you use windows, do this:
```sh
.\build_win.bat
```
and there you go, you should see an fitusb executable in the build folder.