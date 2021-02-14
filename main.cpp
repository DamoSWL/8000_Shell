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
    Commands* cmds = create_commands();

    while(1)
    {
       
        memset(newCmd,'\0',MAX_COUNT);
        fgets(newCmd,MAX_LENGTH,stdin);
        parse_cmd_line(newCmd,cmds,0);
        execute_cmd(cmds);

        reset_commands(cmds);
        
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
            else if(strncmp(commands->cmds[0]->cmd_name,"ls",strlen("ls")) == 0)
            {
                ls_short();
            }
        }
        else
        {
            if(strncmp(commands->cmds[0]->cmd_name,"ls",strlen("ls")) == 0)
            {
                if(strncmp(commands->cmds[0]->argument[0],"-r",strlen("-r")) == 0)
                {
                    ls_with_r();
                }
                else if(strncmp(commands->cmds[0]->argument[0],"-l",strlen("-l")) == 0)
                {
                    if(commands->cmds[0]->argc == 1)
                    {
                        ls_with_l();
                    }
                    else if(commands->cmds[0]->argc == 2)
                    {
                        char filename[MAX_LENGTH] = {'\0'};
                        strncpy(filename,commands->cmds[0]->argument[1],strlen(commands->cmds[0]->argument[1])-1);
                        ls_with_l_filename(filename);
                    }
                    else{}
                    
                }
                else if(strncmp(commands->cmds[0]->argument[0],"-s",strlen("-s")) == 0)
                {
                    if(commands->cmds[0]->argc == 1)
                    {
                        ls_with_s();
                    }
                    else if(commands->cmds[0]->argc == 2)
                    {
                        char filename[MAX_LENGTH] = {'\0'};
                        strncpy(filename,commands->cmds[0]->argument[1],strlen(commands->cmds[0]->argument[1])-1);
                        ls_with_s_filename(filename);
                    }
                    else{}
                    
                }
                else if(strncmp(commands->cmds[0]->argument[0],"--file-type",strlen("--file-type")) == 0)
                {
                    if(commands->cmds[0]->argument[1][0] == '*' && commands->cmds[0]->argument[1][1] == '.' && strlen(commands->cmds[0]->argument[1])>2)
                    {
                        char extension[MAX_LENGTH] = {'\0'};
                        strncpy(extension,commands->cmds[0]->argument[1]+2,strlen(commands->cmds[0]->argument[1])-3);
                        ls_with_file_type(extension);
                    }
                    else
                    {
                        puts("invalid format of file extension");
                        return;
                    }
                    
                }
            }
        }
        
    }
}




