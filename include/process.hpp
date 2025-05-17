#pragma once
#include "main.hpp"
#include "ostype.hpp"
class Process {
public:
    s output{};
    int returnCode = 0;
    Process();
    void Exec(os operatingSystemType, verbose v, s cmd);
    
};