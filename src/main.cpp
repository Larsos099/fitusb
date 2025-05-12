#include "main.hpp"
#include "process.hpp"
#include "util.hpp"
#include "wintool.hpp"
int main(int argc, char* argv[]){
    bool getHelp = false;
    v<s> argl{};
    bool getos = false;
    bool listdev = false;
    bool fl = false;
    #if defined(_WIN32)
    WinTool wt{};
    #endif
    s iso = "0"; s device = "0";
    s out{};
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
    #if defined(__unix__) || defined(__APPLE__)
    if(geteuid() != 0 && !getHelp){
        throw std::runtime_error("This program must be run as root. (sudo)\n");
    }
    #elif defined(_WIN32)
    // elevatewin32(); (soon to be implemented in util.hpp)
    #endif
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
        #if defined(__unix__) || defined(__APPLE__)
        if(fs::exists(argl[i]) && !findInStr(argl[i], "/dev/")) iso = fs::absolute(argl[i]);
        if(fs::exists(argl[i]) && findInStr(argl[i], "/dev/")) device = fs::absolute(argl[i]);
        #elif defined(_WIN32)
        if(fs::exists(argl[i])) { iso = fs::absolute(argl[i]).string(); }
        try {
            if((std::stoi(argl[i]) == 0)) device = argl[i];
        }
        catch (const std::invalid_argument &ex){
            std::cout << "Drive Argument Recognition failed. likely std::stoi. " <<  "argl[" << std::to_string(i) << "]" <<std::endl << ex.what() << std::endl;
        }
        #endif
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
    #if defined(__unix__ )|| (__APPLE__)
    if(listdev){
        proc.Exec(osys, v, LISTDEV);
    }
    #elif defined(_WIN32)
    if(listdev){
        wt.listDevices(out);
        std::cout << out << std::endl;
    }
    #endif

    #if defined(__unix__) || defined(__APPLE__)
    if(fl){
        if(!fs::exists(iso) || !fs::exists(device)) throw std::errc::no_such_file_or_directory;
        std::ostringstream ss;
        ss << FLASH_TOOL << " if=" << iso << " of=" << device << " bs=1M && sync";
        s flash = ss.str();
        proc.Exec(osys, v, flash);
    }
    #elif defined(_WIN32)
    if(fl){
        std::error_code ec;
        bool isoOK = fs::exists(iso, ec);
        if(ec){
            std::cerr << "File Error (ISO): " << ec.message() << std::endl;
        }
        else {
            
            wt.flash(iso, std::stoi(device), v);
            wt.getOutput(out);
            std::cout << out << std::endl;
        }
    }
    #endif
    if(getHelp){
        if(osys == UNIX){
            std::cout << "usage:\n"
                      << "1. sudo fitusb [-h -v -gos -ld]\n"
                      << "2. sudo fitusb <Path-to-Iso> <device> (-v)\n"
                      << "[!] The order of the Arguments does not matter.\n"
                      << "[!] fitusb MUST be run as root (sudo fitusb).\n";
        }
        else if(osys == MSWIN) {
            std::cout << "usage:\n"
                      << "1. fitusb [-h -v -gos -ld]\n"
                      << "2. fitusb <Path-to-ISO> <Windows-Drive-Number>\n"
                      << "[*] Example for Drive Number:\n"
                      << "fitusb C:\\Users\\Albert\\Downloads\\Windows7Ultimate.iso 5\n"
                      << "[!] fitusb MUST be run as Administrator.\n";
        }
    }
    return 0;
}