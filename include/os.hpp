#ifndef OS_HPP
#define OS_HPP
#include "main.hpp"
enum osType{
    WIN32,
    UNIX,
    NSP
};
class OperatingSystem {
public:
    OperatingSystem();
    osType getOS();
    bool set();
    s enumElementStr(osType os);
private:
    osType type;
};
#endif // OS_HPP