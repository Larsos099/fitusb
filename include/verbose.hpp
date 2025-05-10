#ifndef VERBOSE_HPP
#define VERBOSE_HPP
#include "os.hpp"
#include "process.hpp"
#include <stdexcept> 
    void runVerbose(osType os, Process &process, s cmd){
        OperatingSystem osC{};
        std::cout << "running process: " << osC.enumElementStr(os) << " way.\n";
        if(os == UNIX){
            std::cout << "running dd\n";
            try{
                process.executeCommandUnix("iwctl -f");
                return;
            }
            catch (const std::exception &ex){
                std::cerr << ex.what() << std::endl;
                return;
            }
        }
    }
#endif // VERBOSE_HPP