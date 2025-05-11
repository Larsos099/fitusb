#include "main.hpp"
#include "process.hpp"
#include "util.hpp"
int main(int argc, char* argv[]){
    bool getHelp = false;
    v<s> argl{};
    bool vb = false;
    bool getos = false;
    bool listdev = false;
    bool fl = false;
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
        vb = true;
        v = YES;
    }
    if(findInVec(argl, "-gos")){
        getos = true;
    }
    if(findInVec(argl, "-ld")){
        listdev = true;
    }
    
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
        v = YES;
        proc.Exec(osys, v, LISTDEV);
    }
    if(argc > 2 && fs::exists(argl[1])){
        fl = true;
    }
    if((v) && fl){
        std::ostringstream ss;
        std::string iso = fs::absolute(argl[1]);
        if(!(fs::exists(argl[2]))) {
            throw fs::filesystem_error("USB-Device not found.", argl[2], std::make_error_code(std::errc::no_such_file_or_directory));
        }
        ss << "sudo " << FLASH_TOOL << " if=" << iso << " of=" << argl[2] << " bs=1m && sync"; // sudo dd if=Ventoy of=/dev/USBSTICK bs=1M && sync
        s flash = ss.str();
        proc.Exec(osys, v, flash);
    }
    if(!(v) && !listdev && !getos && !getHelp){
        s isofile = argl[2];
        s absoluteIsofile = fs::absolute(isofile);
        s devicePath = argl[3];
    }
    if(getHelp){
        std::cout << "usage:\n"
                  << "1. sudo fitusb [-h -v -gos -ld]\n"
                  << "2. sudo fitusb <Path-to-Iso> <device> (-v)\n";
    }
    return 0;
}