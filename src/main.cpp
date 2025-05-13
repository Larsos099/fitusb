#include "main.hpp"
#include "process.hpp"
#include "util.hpp"
#include "help.hpp"
#if defined(_WIN32)
#include "wintool.hpp"
#endif

int main(int argc, char* argv[]){
    v<s> argl{};
    bool getos = false;
    bool listdev = false;
    bool fl = false;
    bool getHelp = false;
    bool no_others = false;
    os osys = getOS();
    s iso = "0"; s device = "0";
    s out{};
    verbose v{};
    #if defined(_WIN32)
    WinTool wt{};
    #endif
    for(int i = 0; i < argc; i++){
        argl.push_back(std::string(argv[i])); // because C-Strings are disgusting
    }
    if(argc == 1){
        throw std::runtime_error("This program must be used with arguments. Run with -h to list options.\n");

    }
    if(findInVec(argl, "-h")){
        os z = getOS();
        helpPrompt(z);
        getHelp = true;
    }
    #if defined(__unix__) || defined(__APPLE__)
    if(geteuid() != 0 && !getHelp){
        throw std::runtime_error("This program must be run as root. (sudo)\n");
    }
    #elif defined(_WIN32)
    if(IsUserAnAdmin() == FALSE) wt.elevate(argc, argv);
    #endif
    if(findInVec(argl, "-ld")){
        listdev = true;
    }
    if(findInVec(argl, "-v")){
        v = YES;
    }
    if(findInVec(argl, "-gos")){
        getos = true;
    }
    if(!getos && !listdev) {
        no_others = true;
    }
    Process proc{};
    if(getos){
        os ro = getOS();
        switch(ro){
            case 0: {std::cout << "UNIX/UNIX-LIKE" << std::endl;} break;
            case 1: {std::cout << "WINDOWS" << std::endl;} break;
            case 2: {std::cout << "MACOS" << std::endl;} break;
            case 3: {std::cout << "UNSUPPORTED" << std::endl;} break;
        };
        std::cin.get();
        exit(0);
    }
    #if defined(__unix__)|| (__APPLE__)
    if(listdev){
        proc.Exec(osys, v, LISTDEV);
        std::cout << proc.output << std::endl;
        exit(0);
    }
    #elif defined(_WIN32)
    if(listdev){
        wt.listDevices(out);
        std::cout << out << std::endl;
        std::cin.get();
        exit(0);
    }
    #endif
    for(int i = 1; i < argc; i++){
        #if defined(__unix__) || defined(__APPLE__)
        if(fs::exists(argl[i]) && !findInStr(argl[i], "/dev/")) iso = fs::absolute(argl[i]);
        if(fs::exists(argl[i]) && findInStr(argl[i], "/dev/")) device = fs::absolute(argl[i]);
        #elif defined(_WIN32)
        if(fs::exists(argl[i])) { iso = fs::absolute(argl[i]).string(); }
        if(isInt(argl[i])) device = argl[i];
        
        
        #endif
    }
    if(iso == "0" || device == "0" && no_others) throw std::invalid_argument("Please specify Device and ISO-File");
    else if(iso != "0" && device != "0") fl = true;
    #if defined(__unix__) || defined(__APPLE__)
    if(fl){
        if(!fs::exists(iso) || !fs::exists(device)) throw std::errc::no_such_file_or_directory;
        std::ostringstream ss;
        ss << FLASH_TOOL << " status=progress"<< " if=" << iso << " of=" << device << " bs=1M && sync >&1";
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
            wt.unlock(std::stoi(device));
            wt.unmount(std::stoi(device));
            wt.flash(iso, std::stoi(device), v);
            std::cin.get();
        }
        return 0;
    }
    #endif
    return 0;
}