#include <iostream>

#include "cmd_runner.h"
#include <thread>
#include <cstring>
#include <unistd.h>

int main() {

    std::thread h([]{
        zx::CmdRes res;
        char cmd[] = R"(./test_cmd -1 123 "1234 214567 sssggsa" "ssf1123 fftyu89 sa12354")";
//        char cmd[] = "ls -h -l";

        zx::CommandExecute(cmd, res);
        std::cout<<"["<<getpid()<<"]退出码："<<res.ExitCode<<std::endl;
        std::cout<<"["<<getpid()<<"]标准输出："<<std::endl<<res.StdoutString<<std::endl;
        std::cout<<"["<<getpid()<<"]标准错误："<<std::endl<<res.StderrString<<std::endl;
    });
    h.join();
    return 0;
}
