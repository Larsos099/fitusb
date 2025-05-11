#pragma once
#include "main.hpp"
enum os {
    UNIX,
    WIN32,
    MAC,
    ERR
};

os getOS();