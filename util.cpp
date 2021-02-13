
#include <cstring>
#include <cstdio>
#include "util.h"
#include <cstdlib>

using namespace std;


Commands* create_commands()
{
    Commands* commands = new Commands;
    commands->cmd_count = 0;

    for(int i=0; i<MAX_COUNT; i++)
    {
        Command* singleCmd = new Command;
        singleCmd->argc = 0;
        singleCmd->cmd_name = new char[MAX_LENGTH];
        memset(singleCmd->cmd_name,'\0',MAX_LENGTH);

        for(int j=0; j<MAX_COUNT; j++)
        {
            singleCmd->argument[j] = new char[MAX_LENGTH];
            memset(singleCmd->argument[j],'\0',MAX_LENGTH);
        }

        commands->cmds[i] = singleCmd;
    }

    return commands;
}

void reset_commands(Commands* cmds)
{
    cmds->cmd_count = 0;
    for(int i=0; i<MAX_COUNT; i++)
    {
        cmds->cmds[i]->argc = 0;
        memset(cmds->cmds[i]->cmd_name,'\0',MAX_LENGTH);
        for(int j=0; j<MAX_COUNT; j++)
        {
            memset(cmds->cmds[i]->argument[j],'\0',MAX_LENGTH);
        }
    }

}

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



void parse_cmd_line(const char* cmdLine, Commands* commands,int index)
{

    char cmd[MAX_LENGTH] = {'\0'};
    memset(cmd,'\0',MAX_LENGTH);
    strncpy(cmd,cmdLine,strlen(cmdLine));

    if(pipeline_flag(cmdLine) == 0)
    {
        int count = 0;
        char* tokens = strtok((char*)cmd," ");
        while(tokens)
        {
            count++;
            tokens = strtok(NULL, " ");   
                  
        }

        if(count == 1)
        {
            tokens = strtok((char*)cmd," ");
            commands->cmd_count = 1;
            commands->cmds[index]->argc = 0;         
            strncpy(commands->cmds[index]->cmd_name,tokens,strlen(tokens));


        }
        else
        {
            memset(cmd,'\0',MAX_LENGTH);
            strncpy(cmd,cmdLine,strlen(cmdLine));

          
            tokens = strtok((char*)cmd, " ");            
            commands->cmd_count = 1;
            commands->cmds[index]->argc = count-1;
            
            strncpy(commands->cmds[index]->cmd_name,tokens,strlen(tokens));

            
            for(int i=0; i<count-1; i++)
            {    
                tokens = strtok(NULL, " ");          
                strncpy(commands->cmds[index]->argument[i],tokens,strlen(tokens));
                 
            }

        }
    
    }

}