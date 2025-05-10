#include "process.hpp"

Process::Process(int &retCode, s &out) {};

void Process::executeCommandUnix(s cmd){
    int pipeFileDescriptor[2];
    if(pipe(pipeFileDescriptor) == -1){
        Process::retCode = 3;
    }
    pid_t processId = fork();
    if(processId == -1){
        Process::retCode = 2;
        return;
    }
    if(processId == 0){
        close(pipeFileDescriptor[0]); 
        dup2(pipeFileDescriptor[1], STDOUT_FILENO);
        close(pipeFileDescriptor[1]);
        int r = execlp(cmd.c_str(), nullptr);
        if(r != 0) {
            throw std::runtime_error(out);
        }
        Process::retCode = 1;
        Process::out = "err\n";
        throw std::runtime_error("Could not open subprocess.");
    }
    else{
        close(pipeFileDescriptor[1]);

        char buf[256];
        ssize_t bytesRead;
        std::string output;

        while ((bytesRead = read(pipeFileDescriptor[0], buf, sizeof(buf)-1)) > 0) {
            buf[bytesRead] = '\0';
            output += buf;
        }

        close(pipeFileDescriptor[0]);
        waitpid(processId, nullptr, 0);

        std::cout << output << std::endl;
    }

}
s Process::getOutPut(){
    return out;
}