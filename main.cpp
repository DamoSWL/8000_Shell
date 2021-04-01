#include <iostream>
#include <string>
#include <sstream>
#include "util.h"
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <regex>
#include "function.h"
#include <signal.h>

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


    char* user = secure_getenv("USER");  //change from getnev


    char* directory = get_current_dir_name();

    char prefix[MAX_LENGTH] = {'\0'};
    snprintf(prefix,MAX_LENGTH,"%s@%s:%s$ ",user,"localhost",directory);  //change from sprintf
    write(STDOUT_FILENO,prefix,strlen(prefix));
    

    
}

vector<string> all_commands;
vector<int> all_pids;


void signal_handler(int signal)
{
    if(signal == SIGINT)
    {
        for (auto iter = all_pids.cbegin(); iter != all_pids.cend();iter++)
        kill(*iter,SIGTERM);
        all_pids.clear();
    }
}

int main(int argc, char* argv[]) 
{

    char* newCmd = new char[MAX_LENGTH];
    Commands* cmds = create_commands();

    if(init_shell_path() < 0)
    {
        delete [] newCmd;
        delete[] cmds;  //release the memory according to bug report
        return -1;
    }

    signal(SIGINT,signal_handler);
    
    while(1)
    {
       
        memset(newCmd,'\0',MAX_COUNT);
        print_prefix();
        fgets(newCmd,MAX_LENGTH,stdin);   
        newCmd[strlen(newCmd)-1] = '\0'; 
        if(strlen(newCmd) > 0)
        {
            parse_cmd_line(newCmd,cmds,0);
    
            if(execute_cmd(cmds,0) > 0)
            {
                all_commands.push_back(newCmd);
            }
        }    

        all_pids.clear();
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
int execute_cmd(Commands* commands,int index)
{    
    int exe_flag = -1;
    

    if(commands->cmd_count == 1)  //if there is only one command in the line, meaning no pipeline
    {

        pid_t pid = -1; 

        int redirect_type = 0;
        int fd = -1;      
        
        int backen = 0;

        backen = is_service(commands);
        redirect_type = is_redirection(commands);

        if(commands->cmds[index]->argc == 0)  //if there is no argument for this command
        {
            if(strncmp(commands->cmds[index]->cmd_name,"exit",strlen("exit")) == 0)
            {
                exe_flag = 1;
                exit(0);
            }
            else if(strncmp(commands->cmds[index]->cmd_name,"pwd",strlen("pwd")) == 0)
            {
                pwd();
                putchar('\n');
                exe_flag = 1;
            }
            else if(strncmp(commands->cmds[index]->cmd_name,"ls",strlen("ls")) == 0)  // execute ls
            {

                ls_short();
                exe_flag = 1;
                
            }
            else if(strncmp(commands->cmds[index]->cmd_name,"history",strlen("history")) == 0)
            {
                history();
                exe_flag = 1;
            }
            
        }
        else  // if there is a argument for the command
        {
            if(strncmp(commands->cmds[index]->cmd_name,"ls",strlen("ls")) == 0)
            {

                exe_flag = 1;
                if(redirect_type > 0)  //check if there is redirection
                {              
                    pid = fork(); //create new process for the ls command
                    if(pid == 0)
                    {
                                                
                        redirection(fd,redirect_type,commands);  //redirect the stdout to the file
                        commands->cmds[index]->argc -= 2;    
                        mul_ls(commands,index);
                        
                    }
                    else
                    {
                        all_pids.push_back(pid);
                    }
                    
                }
                else
                {
                    if(backen > 0)
                    {
                        pid = fork();
                        if(pid == 0)
                        {
                             mul_ls(commands,index);
                            
                        }
                        else
                        {
                            printf("[1] %d\n",pid);
                        }
                        
                    }
                    else
                    {
                        mul_ls(commands,index);
                    }
                    
                   
                }
                
                
            }
            else if(strncmp(commands->cmds[index]->cmd_name,"cd",strlen("cd")) == 0)  //execute cd, changing directory
            {
                char path[MAX_LENGTH]={'\0'};
                strncpy(path,commands->cmds[index]->argument[0],strlen(commands->cmds[index]->argument[0]));
                puts(path);
                changing_directory(path);
                exe_flag = 1;
            }
            else if(strncmp(commands->cmds[index]->cmd_name,"history",strlen("history")) == 0)
            {
                exe_flag = 1;
                if(redirect_type > 0)
                {               
                    pid = fork();
                    if(pid == 0)
                    {                                            
                        redirection(fd,redirect_type,commands);                        
                        history();
                        
                    }
                    else
                    {
                        all_pids.push_back(pid);
                    }
                }
                else
                {
                    history();
                }
                
            }
            else if(strncmp(commands->cmds[index]->cmd_name,"find",strlen("find")) == 0)
            {
                
                exe_flag = 1;
                if(redirect_type > 0)
                {
                    pid = fork();
                    if(pid == 0)
                    {
                                           
                        redirection(fd,redirect_type,commands);  
                        
                        char filename[MAX_LENGTH] = {'\0'};
                        strncpy(filename,commands->cmds[index]->argument[2],strlen(commands->cmds[index]->argument[2]));
                        find(commands->cmds[index]->argument[0],filename);
                        
                    }
                    else
                    {
                        all_pids.push_back(pid);
                    }
                }
                else
                {
                    char filename[MAX_LENGTH] = {'\0'};
                    strncpy(filename,commands->cmds[index]->argument[2],strlen(commands->cmds[index]->argument[2]));
                    if(backen > 0)
                    {
                        pid = fork();
                        if(pid == 0)
                        {
                            find(commands->cmds[index]->argument[0],filename);
                        
                        }
                        else
                        {

                            printf("[1] %d\n",pid);                       
                        }
                        
                    }
                    else
                    {
                        pid = fork();
                        if(pid == 0)
                        {
                            find(commands->cmds[index]->argument[0],filename);
                        }
                        else
                        {
                            all_pids.push_back(pid);
                        }
                       
                       
                    }
                    
                    
                }

            }

        }


        if((pid > 0) && (backen != 1))
        {

            waitpid(pid,nullptr,0);

        }
        
        
    }
    else
    {

        exe_flag = 1;
        int fds[2]; // file descriptors
        pipe(fds);

        pid_t pid_1 = -1;
        pid_t pid_2 = -1;


        pid_1=fork();
        if(pid_1 == 0)  //command 1
        {
             dup2(fds[1], STDOUT_FILENO);
             close(fds[0]);
             commands->cmd_count = 1;
             execute_cmd(commands,0);
             close(fds[1]);
             
             
        }

        pid_2 = fork();

        if(pid_2 == 0)  //command 2
        {
             dup2(fds[0], STDIN_FILENO);
             close(fds[1]);
             commands->cmd_count = 1;
             execute_cmd(commands,1);
             close(fds[0]);
             
        }

        close(fds[0]);
        close(fds[1]);

        all_pids.push_back(pid_1);
        all_pids.push_back(pid_2);

        waitpid(pid_1,nullptr,0);
        waitpid(pid_2,nullptr,0);
        

    }
    
    
    

    return exe_flag;

}




