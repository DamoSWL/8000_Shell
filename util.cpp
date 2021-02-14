
#include <cstring>
#include <cstdio>
#include "util.h"
#include <cstdlib>

using namespace std;

/***********************************************************
 * Function: create_commands
 * 
 * Description: create the container for the commands
 * 
 * Return: return the pointer to the container
 * 
 *
 * ***********************************************************/

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



/***********************************************************
 * Function: reset_commands
 * 
 * Description: reset the contatiner
 * 
 * Input: return the pointer to the container
 * 
 *
 * ***********************************************************/

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

/***********************************************************
 * Function: pipeline_flag
 * 
 * Description: check whether the command line contain the pipeline
 * 
 * return : return 0 or 1
 * 
 *
 * ***********************************************************/

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

/***********************************************************
 * Function: parse_cmd_line
 * 
 * Description: parse the command line and store the command in the container
 * 
 * Input : @cmdLine, the original command line
 *         @commands, the pointer to the container
 *         @index, the index of position in the container to store the command
 * 
 *
 * ***********************************************************/

void parse_cmd_line(const char* cmdLine, Commands* commands,int index)
{

    char cmd[MAX_LENGTH] = {'\0'};
    memset(cmd,'\0',MAX_LENGTH);
    strncpy(cmd,cmdLine,strlen(cmdLine));

    if(pipeline_flag(cmdLine) == 0)//if there is no pipeline meaning only one command 
    {
        int count = 0;
        char* tokens = strtok((char*)cmd," ");
        while(tokens)
        {
            count++;
            tokens = strtok(NULL, " ");   
                  
        }

        if(count == 1)  //if there is only one command  option
        {
            tokens = strtok((char*)cmd," ");
            commands->cmd_count = 1;
            commands->cmds[index]->argc = 0;         
            strncpy(commands->cmds[index]->cmd_name,tokens,strlen(tokens));


        }
        else  // multiple command options
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