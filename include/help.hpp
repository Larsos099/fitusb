#pragma once
#include "ostype.hpp"
void helpPrompt(os z){
    if(z == UNIX){
            std::cout << "usage:\n"
                      << "1. sudo fitusb [-h -v -gos -ld]\n"
                      << "2. sudo fitusb <Path-to-Iso> <device> (-v)\n"
                      << "[!] The order of the Arguments does not matter.\n"
                      << "[!] fitusb MUST be run as root (sudo fitusb).\n";
        }
        else if(z == MSWIN) {
            std::cout << "usage:\n"
                      << "1. fitusb [-h -v -gos -ld]\n"
                      << "2. fitusb <Path-to-ISO> <Windows-Drive-Number>\n"
                      << "[*] Example for Drive Number:\n"
                      << "fitusb C:\\Users\\Albert\\Downloads\\Windows7Ultimate.iso 5\n"
                      << "[!] fitusb MUST be run as Administrator.\n";
        }
        exit(0);
}