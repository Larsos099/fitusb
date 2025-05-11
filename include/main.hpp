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
    #include<process.h>
#elif defined(__linux__)
    #include<cstdio>
#elif defined(__APPLE__)
    #include <unistd.h>
    #include <cstdlib>
#else
    #error "unsupported os."
#endif
using s = std::string;
template <typename T>
using v = std::vector<T>;
namespace fs = std::filesystem;

