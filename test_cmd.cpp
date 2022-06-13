//
// Created by devis on 2022/6/13.
//
#include <iostream>
int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr<<"参数不满足要求，至少需要一个返回码参数"<<std::endl;
        return -1;
    }
    long code = strtol(argv[1], nullptr, 10);
    std::cerr<<"这是来自test_cmd的错误信息"<<std::endl;
    for(int i = 1; i < argc; i++) {
        std::cout<<"这是第"<<i<<"项命令行参数："<<argv[i]<<std::endl;
    }
    return int(code);
}