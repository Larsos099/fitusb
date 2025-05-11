# fitusb (Flash (ISO-)Image to USB)

## 1. What is _fitusb_?
fitusb is a custom Multi-Platform Image to USB flash tool coded in C++
## 2. Why _fitusb_?
fitusb is very easy to use with its simple CLI Syntax
## 3. How do I get _fitusb_?
you just build it from source (using CMake) or download it from Sources like the AUR
## 4. How do I use _fitusb_?
you use fitusb in the terminal of your choice like this:
```sh
fitusb <ISO-Image-path> <device> (-v)
```
to list the devices, you use the following argument:
```sh
fitusb -ld
```
to get the OS detected by fitusb you use:
```sh
fitusb -gos
```
# 5. Building _fitusb_
## 5.1 Requirements
- Some C++ Compiler with C++17 support
- CMake 3.16
- _**(UNIX SYSTEMS ONLY) lsblk**_
## 5.2 How to build _fitusb_
you go into the fitusb directory, where you cloned it into.

Now you type into your terminal of choice:
```sh
cmake .
```
then you type in (On Linux or MacOS)
```sh
cmake --build ./build
```
or if you use windows
```sh
cmake --build .\build
```
and there you go, you should see an fitusb executable in the build folder.