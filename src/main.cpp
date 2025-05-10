#include "main.hpp"
#include "process.hpp"
#include "os.hpp"
#include "verbose.hpp"
int main(int argc, char* argv[]){
    s isoFile = {};
    v<s> argl = {};
    if(argc == 1){
        return 1;
    }
    for(int i = 0; i < argc; i++){
        argl.push_back(std::string(argv[i])); 
    }
    OperatingSystem os{};
    s output{};
    int returnCode{};
    Process agent(returnCode, output);
    osType runningOn{};
    if(os.set()){
        runningOn = os.getOS();
    }
    else {
        return 2;
    }
    if(runningOn == UNIX){
        runVerbose(runningOn, agent, "d<");
        return 0;
    }
}
