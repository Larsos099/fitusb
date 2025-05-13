#if defined(_WIN32)
#pragma once
#include "main.hpp"
#pragma comment(lib, "setupapi.lib")

class WinTool {
public:
    WinTool();
    void elevate(int argc, char* argv[]);
    void flash(const s isofile, const int devnum, verbose v);
    void listDevices(s &out);
    void unlock(const int devnum);
    void unmount(const int devnum);
    double getSize(const s isofile);
private:
    s output{};
};
#endif 