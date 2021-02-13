#include <iostream>
#include <string>
#include <sstream>
#include "util.h"
#include <cstring>
#include <cstdio>
#include "function.h"

using namespace std;




int main(int argc, char* argv[]) 
{

    char* newCmd = new char[MAX_LENGTH];


    while(1)
    {
        memset(newCmd,'\0',MAX_COUNT);
        fgets(newCmd,MAX_LENGTH,stdin);
        Commands* cmds = nullptr;
        cmds = parse_cmd_line(newCmd);

        execute_cmd(cmds);



    }

    return 0;
}

void execute_cmd(Commands* commands)
{
    if(commands->cmd_count == 1)
    {
        if(commands->cmds[0]->argc == 0)
        {
            if(strncmp(commands->cmds[0]->cmd_name,"exit",strlen("exit")) == 0)
            {
                exit(0);
            }
            else if(strncmp(commands->cmds[0]->cmd_name,"pwd",strlen("pwd")) == 0)
            {
                pwd();
                putchar('\n');
            }
        }
    }
}




