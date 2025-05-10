#include "os.hpp"
OperatingSystem::OperatingSystem() {};

osType OperatingSystem::getOS() {
    return type;
}
bool OperatingSystem::set() {
    #if defined(_WIN32)
        type = WIN32;
    #elif defined(__linux__)
        type = UNIX;
    #elif defined(__APPLE__)
        type = UNIX;
    #else
        type = NSP;
    #endif
   if(type){
    return true;
   }
   else{
    return false;
   }
}
s OperatingSystem::enumElementStr(osType os){
    switch(os){
        case osType::NSP: {return "Not-Supported";} break;
        case osType::UNIX: {return "UNIX/UNIX-LIKE";} break;
        case osType::WIN32: {return "WINDOWS";} break;
        default: {return "UNKNOWN";} break;
    }
}
