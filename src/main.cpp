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
    s out{};
    int r{};
    Process proc(out, r);
    os osys = getOS();
    if((v)){
        proc.Exec(osys, v, "tree");
        std::cout << out << std::endl;
    }
    return 0;
}