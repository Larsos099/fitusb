#include "main.hpp"
#include "process.hpp"
#include "util.hpp"
int main(int argc, char* argv[]){
    v<s> argl{};
    bool vb = false;
    bool getos = false;
    bool listdev = false;
    bool fl = false;
    verbose v{};
    for(int i = 0; i < argc; i++){
        argl.push_back(std::string(argv[i])); // because C-Strings are disgusting
    }
    if(findInVec(argl, s("-v"))){
        vb = true;
        v = YES;
    }
    if(findInVec(argl, s("-gos"))){
        getos = true;
    }
    if(findInVec(argl, s("-ld"))){
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
    s out{};
    int r{};
    Process proc(out, r);
    os osys = getOS();
    if(listdev){
        v = YES;
        proc.Exec(osys, v, LISTDEV);
    }
    if(fs::exists(argl[2])){
        fl = true;
    }
    if((v) && fl){
        proc.Exec(osys, v, "tree"); // Flash ISO to USB with verbose argl[2] is always the ISO and argl[3] always the USB
        std::cout << out << std::endl;
    }
    if(!(v) && !listdev && !getos){
        s isofile = argl[2];
        s absoluteIsofile = fs::absolute(isofile);
        s devicePath = argl[3];
    }
    return 0;
}