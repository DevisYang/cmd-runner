#ifndef CMD_RUNNER_CMD_RUNNER_H
#define CMD_RUNNER_CMD_RUNNER_H
#include <string>
namespace zx {
    struct CmdRes {
        std::string StdoutString;
        std::string StderrString;
        int ExitCode;
    };
    bool CommandExecute(const std::string& cmd, CmdRes& res);
}

#endif //CMD_RUNNER_CMD_RUNNER_H
