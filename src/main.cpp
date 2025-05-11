#include "main.hpp"
#include "process.hpp"
#include "util.hpp"
int main(int argc, char* argv[]){
    v<s> argl{};
    bool vb = false;
    bool getos = false;
    bool listdev = false;
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
        proc.Exec(osys, v, "lsblk");
    }
    if((v)){
        proc.Exec(osys, v, "tree");
        std::cout << out << std::endl;
    }
    return 0;
}