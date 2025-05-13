#if defined(_WIN32)
#pragma once
#include "main.hpp"
#pragma comment(lib, "setupapi.lib")

class WinTool {
public:
    WinTool();
    bool elevate();
    void flash(const s isofile, const int devnum, verbose v);
    void listDevices(s &out);
    void unlock(const int devnum);
    void unmount(const int devnum);
private:
    s output{};
};
#endif 