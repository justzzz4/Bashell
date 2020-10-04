# Bashell


程序主体为ExecShell()函数。

函数大致分为三部分，第一部分为处理用户输入，其中用到了Vector数组，将用户输入的字符串以空格作为分隔符，将分割后的子串存入Vector数组中。

第二部分是将Vector数组转换为execvp（）函数所需的参数 char* args[]。

第三部分是fork() 子进程，子进程调用execvp（）函数，其中该函数第一个参数为要运行的文件，只需给出文件名，不需要完整路径，该函数会在PATH中寻找路径，因此，我们将args[0]作为第一个参数。第二个参数即为完整命令，将args 二维数组传入，如果失败则会给出运行错误提示。父进程中调用wait()函数被阻塞，当wait 函数接收到信号量或者子进程结束时，继续执行父进程，代码中wait(NULL)无参数，即只有子进程结束时继续执行父进程。

