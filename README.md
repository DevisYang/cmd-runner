# Linux下C语言执行指令，返回标准输出、标准错误以及指令退出码
## 编译
编译前需要安装G++以及cmake

```shell script
git clone https://gitee.com/msgy/cmd-runner.git
cd cmd-runner
mkdir build
cd build
cmake ..
make
```
## 运行
main.cpp中是调用指令执行函数的测试程序，test_cmd是测试程序，在main.cpp会调用test_cmd程序进行测试。执行如下指令进行测试：
```shell script
./cmd_runner
```