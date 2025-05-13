#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<filesystem>
#include<stdexcept>
#include<sstream>
#include<algorithm>
#include "verbose.hpp"
#ifdef _WIN32
    #include<Windows.h>
    #include<setupapi.h>
    #include<winioctl.h>
    #include<fileapi.h>
    #include<ShlObj.h>
    #include<regex>
    #include<shellapi.h>
    #define DRIVE_PREFIX "\\\\.\\PhysicalDrive"
    // Using Native WinAPI to Flash USB... (i hate this.)
    constexpr DWORD BUFFER_SIZE = 1024 * 1024;
#elif defined(__unix__)
    #include<cstdio>
    #include<unistd.h> 
    #define LISTDEV "lsblk"
    #define FLASH_TOOL "dd"
#elif defined(__APPLE__)
    #include <unistd.h>
    #include <cstdlib>
    #include <cstdio>   
    #define LISTDEV "diskutil list"
    #define FLASH_TOOL "dd"
#else
    #error "unsupported os."
#endif
using s = std::string;
template <typename T>
using v = std::vector<T>;
namespace fs = std::filesystem;

