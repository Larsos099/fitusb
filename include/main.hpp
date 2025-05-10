#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdexcept>
using s = std::string;
namespace fs = std::filesystem;
template<typename T>
using v = std::vector<T>;
#endif // MAIN_HPP