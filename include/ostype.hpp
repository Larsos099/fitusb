#pragma once
#include "main.hpp"
enum os {
    UNIX,
    MSWIN,
    MAC,
    ERR
};

os getOS();