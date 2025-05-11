#pragma once
#include "main.hpp"
#include "ostype.hpp"
class Process {
public:
    s output{};
    int returnCode;
    Process(s &output, int &returnCode);
    void Exec(os operatingSystemType, verbose v, s cmd);
};