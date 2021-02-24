#include <iostream>
#include <string>
#include <sstream>
#include "util.h"
#include <cstring>
#include <cstdio>
#include "function.h"

using namespace std;

/********************************************************************
 * Function: init_shell_path
 * 
 * Description: initialize the working directory of the shell, and make
 * the ~/csci-shell/home as the current working directory of the shell
 * 
 * 
 *************************************************************************/

void init_shell_path()
{

    char* home_path = getenv("HOME");
    char shell_path[MAX_LENGTH] = {'\0'};

    strncpy(shell_path,home_path,strlen(home_path));
    strncat(shell_path,"/csci-shell",strlen("/csci-shell"));
    
    DIR* dir = nullptr;
    dir = opendir(shell_path);
    umask(0);
    if(!dir)
    {
        mkdir(shell_path,0755);    
    }

    strncat(shell_path,"/home",strlen("/home"));
    dir = opendir(shell_path);
    if(!dir)
    {
        mkdir(shell_path,0755);    
    }

    chdir(shell_path);
    if(dir)
    {
        closedir(dir);
    }

}

/********************************************************************
 * Function:  print_prefix
 * 
 * Description: print the prefix before the input command from the user
 * 
 * 
 *************************************************************************/


void print_prefix()
{
    char* user = getenv("USER");
    char* directory = get_current_dir_name();

    char prefix[MAX_LENGTH] = {'\0'};
    snprintf(prefix,MAX_LENGTH,"%s@%s:%s$ ",user,"localhost",directory);
    write(STDOUT_FILENO,prefix,strlen(prefix));

    
}


int main(int argc, char* argv[]) 
{

    char* newCmd = new char[MAX_LENGTH];
    Commands* cmds = create_commands();

    init_shell_path();


    while(1)
    {
       
        memset(newCmd,'\0',MAX_COUNT);
        print_prefix();
        //fgets
        fgets(newCmd,MAX_LENGTH,stdin);
        parse_cmd_line(newCmd,cmds,0);
        execute_cmd(cmds);

        reset_commands(cmds);
        
    }

    return 0;
}
/**************************************************************
 * Function: execute_cmd
 * 
 * Description: execute the command, in this function we compare 
 * the commands and token, and execute the relevant function according the 
 * the results from the comparsion
 * 
 * Input: commands, containing the commands in each line
 * 
 *
 * ***************************************************************/
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
            else if(strncmp(commands->cmds[0]->cmd_name,"ls",strlen("ls")) == 0)  // execute ls
            {
                ls_short();
            }
            else if(strncmp(commands->cmds[0]->cmd_name,"cd",strlen("cd")) == 0)  //execute cd, changing directory
            {
                changing_directory(commands->cmds[0]->argument[0]);
            }
        }
        else
        {
            if(strncmp(commands->cmds[0]->cmd_name,"ls",strlen("ls")) == 0)
            {
                if(strncmp(commands->cmds[0]->argument[0],"-r",strlen("-r")) == 0)  //execute ls -r
                {
                    ls_with_r();
                }
                else if(strncmp(commands->cmds[0]->argument[0],"-l",strlen("-l")) == 0)  
                {
                    if(commands->cmds[0]->argc == 1)
                    {
                        ls_with_l();  //execute ls -l
                    }
                    else if(commands->cmds[0]->argc == 2)
                    {
                        char filename[MAX_LENGTH] = {'\0'};
                        strncpy(filename,commands->cmds[0]->argument[1],strlen(commands->cmds[0]->argument[1])-1);
                        ls_with_l_filename(filename);  //execute ls -l filename
                    }
                    else{}
                    
                }
                else if(strncmp(commands->cmds[0]->argument[0],"-s",strlen("-s")) == 0)
                {
                    if(commands->cmds[0]->argc == 1)
                    {
                        ls_with_s();  //execute ls -s 
                    }
                    else if(commands->cmds[0]->argc == 2)
                    {
                        char filename[MAX_LENGTH] = {'\0'};
                        strncpy(filename,commands->cmds[0]->argument[1],strlen(commands->cmds[0]->argument[1])-1);
                        ls_with_s_filename(filename);  //execute ls -s  filename
                    }
                    else{}
                    
                }
                else if(strncmp(commands->cmds[0]->argument[0],"--file-type",strlen("--file-type")) == 0)
                {
                    if(commands->cmds[0]->argument[1][0] == '*' && commands->cmds[0]->argument[1][1] == '.' && strlen(commands->cmds[0]->argument[1])>2)
                    {
                        char extension[MAX_LENGTH] = {'\0'};
                        strncpy(extension,commands->cmds[0]->argument[1]+2,strlen(commands->cmds[0]->argument[1])-3);
                        ls_with_file_type(extension);  //execute ls --file-type extension
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




