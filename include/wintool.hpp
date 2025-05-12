#if defined(_WIN32)
#pragma once
#include "main.hpp"

class WinTool {
public:
    WinTool();
    void getOutput(s &out);
    void flash(const s isofile, const int devnum, verbose v);
    void listDevices(s &out);
private:
    s output{};
};
#endif 