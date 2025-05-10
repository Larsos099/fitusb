#ifndef PROC_HPP
#define PROC_HPP
#include "main.hpp"
class Process {
    public:
    Process(int &retCode, s &out);
    void executeCommandUnix(s cmd);
    s getOutPut();
    private:
    int retCode;
    s out;
};

#endif // PROC_HPP