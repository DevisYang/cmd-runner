#include "cmd_runner.h"
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

namespace zx {
    const int MAX_COMMAND_SIZE = 4096;
    const int MAX_COMMAND_ARGS_COUNT = 127;

    void CommandConvert(char *buffer, char *args[]) {
        int size = strlen(buffer)+1;
        int i = 0, j = 0;
        char *head = buffer;
        while (i < size) {
            if (head[0] == '"') {
                if (buffer[i] == '"' && head != buffer + i) {
                    args[j++] = head;
                    buffer[i + 1] = '\0';
                    i += 2;
                    head = buffer + i;
                    continue;
                }
                i++;
                continue;
            }

            if (buffer[i] == ' ' || buffer[i] == '\0') {
                args[j++] = head;
                buffer[i] = '\0';
                i++;
                head = buffer + i;
            }
            i++;
        }
    }

    bool CommandExecute(const std::string &cmd, CmdRes &res) {
        assert(cmd.size() < MAX_COMMAND_SIZE);
        int fd_out[2];
        int fd_err[2];
        int ret = pipe(fd_out);
        if (ret == -1) {
            return false;
        }
        ret = pipe(fd_err);
        if (ret == -1) {
            return false;
        }
        pid_t pid = fork();
        if (pid == 0) {
            close(fd_out[0]);
            close(fd_err[0]);
            dup2(fd_out[1], STDOUT_FILENO);
            dup2(fd_err[1], STDERR_FILENO);
            char buffer[MAX_COMMAND_SIZE] = {0};
            strcpy(buffer, cmd.c_str());
            char *args[MAX_COMMAND_ARGS_COUNT] = {nullptr};
            CommandConvert(buffer, args);
            execvp(args[0], args);
            perror("execvp");
            return -1;
        } else if (pid > 0) {
            res.StderrString.clear();
            res.StdoutString.clear();
            close(fd_out[1]);
            close(fd_err[1]);
            char buffer[1024] = {0};
            while(true) {
                int len = read(fd_out[0], buffer, sizeof(buffer));
                if(len == 0) {
                    break;
                }
                res.StdoutString.append(std::string(buffer, len));
            }
            while(true) {
                int len = read(fd_err[0], buffer, sizeof(buffer));
                if(len == 0) {
                    break;
                }
                res.StderrString.append(std::string(buffer, len));
            }
            close(fd_err[0]);
            close(fd_out[0]);
            int status = 0;
            wait(&status);
            res.ExitCode = WEXITSTATUS(status);
        }
        return true;
    }
}