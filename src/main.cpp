#include "main.hpp"
#include "process.hpp"
#include "util.hpp"
int main(int argc, char* argv[]){
    bool getHelp = false;
    v<s> argl{};
    bool getos = false;
    bool listdev = false;
    bool fl = false;
    s iso = "0"; s device = "0";
    verbose v{};
    for(int i = 0; i < argc; i++){
        argl.push_back(std::string(argv[i])); // because C-Strings are disgusting
    }
    if(argc == 1){
        throw std::runtime_error("This program must be used with arguments. Run with -h to list options.\n");

    }
    if(findInVec(argl, "-h")){
        getHelp = true;
    }
    if(geteuid() != 0 && !getHelp){
        throw std::runtime_error("This program must be run as root. (sudo)\n");
    }
    if(findInVec(argl, "-v")){
        v = YES;
    }
    if(findInVec(argl, "-gos")){
        getos = true;
    }
    if(findInVec(argl, "-ld")){
        listdev = true;
    }
    for(int i = 1; i < argc; i++){
        if(fs::exists(argl[i]) && !findInStr(argl[i], "/dev/")) iso = fs::absolute(argl[i]);
        if(fs::exists(argl[i]) && findInStr(argl[i], "/dev/")) device = fs::absolute(argl[i]);

    }
    if(iso == "0" || device == "0") throw std::invalid_argument("Please specify Device and ISO-File");
    else if(iso != "0" && device != "0") fl = true;
    if(getos){
        os ro = getOS();
        switch(ro){
            case 0: {std::cout << "UNIX/UNIX-LIKE" << std::endl;} break;
            case 1: {std::cout << "WINDOWS" << std::endl;} break;
            case 2: {std::cout << "MACOS" << std::endl;} break;
            case 3: {std::cout << "UNSUPPORTED" << std::endl;} break;
        };
    }
    Process proc{};
    os osys = getOS();
    if(listdev){
        proc.Exec(osys, v, LISTDEV);
    }
    if(fl){
        if(!fs::exists(iso) || !fs::exists(device)) throw std::errc::no_such_file_or_directory;
        std::ostringstream ss;
        ss << FLASH_TOOL << " if=" << iso << " of=" << device << " bs=1M && sync";
        s flash = ss.str();
        proc.Exec(osys, v, flash);
    }
    if(getHelp){
        std::cout << "usage:\n"
                  << "1. sudo fitusb [-h -v -gos -ld]\n"
                  << "2. sudo fitusb <Path-to-Iso> <device> (-v)\n";
    }
    return 0;
}