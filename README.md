# fitusb (Flash (ISO-)Image to USB)

## Table of Contents
- ### [1. fitusb requirements](#fitusb-build-requirements)
- ### [2. Why fitusb?](#why-fitusb)
- ### [3. How do I use fitusb?](#how-do-i-use-fitusb)
- ### [4. How do I get fitusb?](#how-do-i-get-fitusb)
    - #### [Windows](#for-windows)
    - #### [Linux/MacOS](#for-linuxmacos)
## fitusb build requirements
To build fitusb and use it, you need the following:
- GCC/G++ >= 15.1 (On Windows MinGW)

- CMake >= 3.20

- _(optional, but recommended) Ninja_

- (lsblk on Linux-Systems)
## Why _fitusb_?
Fitusb is a simple, leightweight ISO-Flasher.

It's completely written in C++, and practically native

It only needs one dependency on Linux Systems, and that is lsblk.

Otherwise it's completely written in C++ Standard Library and Native WinAPI for Windows.

Use fitusb, flashing a bootable USB with only 2 CLI Arguments.

## How do I use _fitusb_?

With just a few arguments.
```sh
fitusb [-gos] [-ld] [-v] <ISO-Image-path> <Device-Path/Device-Number>
# On Windows, you use Device numbers to select the drive, on Linux/MacOS device Paths.
```

Example ISO-Flashing Syntax
```sh
# For Windows
.\fitusb archlinux-x86_64.iso 3 -v
# For Linux/MacOS
./fitusb ~/Downloads/archlinux-x86_64.iso /dev/sdb
```

Example output of -ld on Windows:
```
.\fitusb -ld
Listing removable physical drives:
Please take the number after the \\.\PhysicalDrive for flashing.
----------------------------------------------------------------
Drive #1: \\.\PhysicalDrive2
  Removable: Yes
  Hotpluggable: No
  Size: 58.24 GB (62537072640 bytes)

Total removable drives found: 1
```
In this Example, you use drive number 1.

Example of -gos on Windows:
```sh
.\fitusb -gos
#Output:
WINDOWS
```
You specify 
```
-v
```
To get more detailed, verbose output.

## How do I get fitusb?

To get fitusb, you need to clone its Git-Repo

```sh
git clone https://github.com/Larsos099/fitusb
```

Now you just have to configure it and build it:

### For Windows:
```ps1
.\conf_win.bat
# After this is finished, you run
.\build_win.bat
```

### For Linux/MacOS:

```sh
./conf.sh
# After this is finished, you run
./build.sh
```
## And thats it, there should be a executable of your System-Type in the build directory named fitusb.