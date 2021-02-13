
#include <cstring>
#include <cstdio>
#include "util.h"

int pipeline_flag(const char* cmdLine)
{
    int index = 0;
    int flag = 0;

    while(cmdLine[index] != '\0')
    {
        if(cmdLine[index] == '|')
        {
            flag = 1;
             break;
        }

        index++;

    }

    return flag;
}



Commands* parse_cmd_line(const char* cmdLine)
{
    Commands* commands = new Commands;
    commands->cmd_count = 0;

    for(int i=0; i<MAX_COUNT; i++)
    {
        Command* singleCmd = new Command;
        singleCmd->argc = 0;
        singleCmd->cmd_name = nullptr;

        for(int j=0; j<MAX_COUNT; j++)
        {
            singleCmd->argument[j] = nullptr;
        }

        commands->cmds[i] = singleCmd;
    }

    

    if(pipeline_flag(cmdLine) == 0)
    {
        int count = 0;
        char* tokens = strtok((char*)cmdLine," ");
        while(tokens)
        {
            count++;
            tokens = strtok(NULL, " ");          
        }

        if(count == 1)
        {
            char* tokens = strtok((char*)cmdLine," ");
            commands->cmd_count = 1;
            commands->cmds[0]->argc = 0;
            
            commands->cmds[0]->cmd_name = new char[MAX_LENGTH];
            memset(commands->cmds[0]->cmd_name,'\0',MAX_LENGTH);
            strncpy(commands->cmds[0]->cmd_name,tokens,strlen(tokens));

        }

        
    }


    return commands;
}