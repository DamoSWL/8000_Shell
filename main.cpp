#include <iostream>
#include <string>
#include <sstream>
#include "util.h"
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

int init_shell_path()
{

    char* home_path = getenv("HOME");
    char shell_path[MAX_LENGTH] = {'\0'};

    int ret = 0;

    //strncpy(shell_path,home_path,strlen(home_path));
    strncat(shell_path,"/csci-shell",strlen("/csci-shell"));
    
    DIR* dir = nullptr;
    dir = opendir(shell_path);
    umask(0);
    if(!dir)
    {
      ret = mkdir(shell_path,0755);   
      if(ret < 0)
      {
          perror("/csci-shell initialization fail:");
          return ret;
      } 
    }

    strncat(shell_path,"/home",strlen("/home"));
    dir = opendir(shell_path);
    if(!dir)
    {
        ret = mkdir(shell_path,0755);  
        if(ret < 0)
        {
          perror("/csci-shell/home initialization fail:");
          return ret;
        }   
    }

    chdir(shell_path);
    if(dir)
    {
        closedir(dir);
    }

    return ret;

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

    if(init_shell_path() < 0)
    {
        return -1;
    }


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
    pid_t pid = -1; 

    int redirect_type = 0;
    int fd = -1;
    redirect_type = is_redirection(commands);
    

    if(commands->cmd_count == 1)  //if there is only one command in the line, meaning no pipeline
    {
        if(commands->cmds[0]->argc == 0)  //if there is no argument for this command
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
            
        }
        else  // if there is a argument for the command
        {
            if(strncmp(commands->cmds[0]->cmd_name,"ls",strlen("ls")) == 0)
            {
                pid = fork(); //create new process for the ls command
                if(pid == 0)
                {
                    if(redirect_type > 0)  //check if there is redirection
                    {
                        redirection(fd,redirect_type,commands);  //redirect the stdout to the file
                        commands->cmds[0]->argc -= 2;
                    }
 
                    mul_ls(commands);
                    exit(0);
                }
                
            }
            else if(strncmp(commands->cmds[0]->cmd_name,"cd",strlen("cd")) == 0)  //execute cd, changing directory
            {
                char path[MAX_LENGTH]={'\0'};
                strncpy(path,commands->cmds[0]->argument[0],strlen(commands->cmds[0]->argument[0])-1);
                changing_directory(path);
            }


           
        }
        
    }
    wait(NULL);



   
}




