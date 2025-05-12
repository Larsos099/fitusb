#include "ostype.hpp"

os getOS(){
    #ifdef _WIN32
    return MSWIN;
#elif defined(__linux__)
    return UNIX;
#elif defined(__APPLE__)
    return UNIX;
#else
    return ERR;
#endif
}