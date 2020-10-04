#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

const int MAX_ARGS_NUMBER = 256;

void ExecShell(){
    cout << getlogin() << ">";
    string line;
    getline(cin,line);
    vector<string> args;
    
    // 以空格为分隔符，寻找line的子串
    int begin = 0; int end = -1;
    for(int i = 0; i < line.size(); i++){
        // 遇到字符
        if(line[i]!= ' ' && i != line.size()-1) {
            end ++;
            continue;
        }
        // 字符串末尾
        if(i == line.size()-1){
            end = i;
            string arg = line.substr(begin,end-begin+1);
            args.push_back(arg);
        }
        // 遇到空格分隔符
        else if(line[i] == ' ') {
            string arg = line.substr(begin,end -begin+1);
            args.push_back(arg);
            begin = i+1;
            end = i;
        }
    }

    char ** argvs = (char**) malloc( sizeof(char*) * MAX_ARGS_NUMBER );

    int argidx = 0;
    for (string s : args) {

        char *_argv = new char[s.length() + 1];
        strcpy(_argv, s.c_str());

        argvs[argidx ++] = _argv;
    }
    
    pid_t pid;
    pid = fork();
    if(pid == 0){
        cout <<"创建了一个子进程.."<<endl;
        if(execvp(argvs[0],argvs) == -1){
            // 如果execvp函数有返回值-1说明执行过程中有错误发生
            cout <<"指令运行错误!" <<endl;
        }
    }
    if(pid < 0 ){
        cout <<"进程创建失败！"<<endl;
    }
    else{
        // 主进程等待子进程结束
        wait(NULL);
        cout <<"返回到主进程.."<<endl;
    }
    

}
int main(){
    while(true){
       ExecShell();
    }
}