#include "process.hpp"

Process::Process() {};

void Process::Exec(os operatingSystemType, verbose v, s cmd) {
    if(operatingSystemType == UNIX && v == YES){
        std::cout << "Executing following command: " << cmd << std::endl;
        FILE* pipe = popen(cmd.c_str(), "r");
        if(!pipe){
            throw std::system_error();
        }
        std::ostringstream cmdOut;
        char c;
        while((c = fgetc(pipe)) != EOF){
            std::cout << "Reading command output..." << std::endl;
            // if(feof(pipe)) break;
            cmdOut << c;
        }  
        std::cout << "Finished reading command output" << std::endl;
        if((pclose(pipe))){
            throw std::system_error();
        }
        output =cmdOut.str();
        return;
    }
    if(operatingSystemType == UNIX && v == NO){
        FILE* pipe = popen(cmd.c_str(), "r");
        if(!pipe) throw std::system_error();
        std::ostringstream cmdOut;
        char c;
        while((c = fgetc(pipe)) != EOF){
            cmdOut << c;
        }
        if((pclose(pipe))) throw std::system_error();
        output = cmdOut.str();
    }
}