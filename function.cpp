#include "function.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

extern vector<string> all_commands;

void pwd()  
{
    char* directory = get_current_dir_name();
    write(STDOUT_FILENO,directory,strlen(directory));
}  


/***********************************************************
 * Function: ls_short
 * 
 * Description: execute ls
 * 
 * 
 *
 * ***********************************************************/
void ls_short()
{
    DIR *dir = nullptr;
	dir = opendir(".");

    vector<string> ls_names;

    if(dir)
    {
       struct dirent* entry = readdir(dir);
       while(entry)
       {
            if(strncmp(entry->d_name,".",strlen(".")) != 0 && strncmp(entry->d_name,"..",strlen("..")) != 0)
           {
               ls_names.push_back(entry->d_name);
           }
           entry = readdir(dir);
       }
    }

    sort(ls_names.begin(),ls_names.end());

    for(auto iter = ls_names.begin(); iter != ls_names.end(); iter++)
    {
        puts(iter->c_str());
    }

    closedir(dir);
}


/***********************************************************
 * Function: ls_with_r
 * 
 * Description: execute ls -r
 * 
 * 
 *
 * ***********************************************************/

void ls_with_r()
{   
    DIR *dir = nullptr;
	dir = opendir(".");

    vector<string> ls_names;

    if(dir)
    {
       struct dirent* entry = readdir(dir);
       while(entry)
       {
           if(strncmp(entry->d_name,".",strlen(".")) != 0 && strncmp(entry->d_name,"..",strlen("..")) != 0)
           {
               ls_names.push_back(entry->d_name);
           }

           
           entry = readdir(dir);
       }
    }

    sort(ls_names.begin(),ls_names.end());

    for(auto iter = ls_names.rbegin(); iter != ls_names.rend(); iter++)
    {
        
        puts(iter->c_str());
    }

    closedir(dir);
}

/***********************************************************
 * Function: ls_with_l
 * 
 * Description: execute ls -l
 * 
 * 
 *
 * ***********************************************************/

void ls_with_l()
{
    DIR *dir = nullptr;
	dir = opendir(".");

    vector<string> ls_names;

    if(dir)
    {
       struct dirent* entry = readdir(dir);
       while(entry)
       {
           if(strncmp(entry->d_name,".",strlen(".")) != 0 && strncmp(entry->d_name,"..",strlen("..")) != 0)
           {
               ls_names.push_back(entry->d_name);
           }

           
           entry = readdir(dir);
       }
    }

    closedir(dir);

    sort(ls_names.begin(),ls_names.end());

    for(auto iter = ls_names.rbegin(); iter != ls_names.rend(); iter++)
    {
        
        string file_path = "./";
        file_path.append(*iter);
        ls_with_l_filename(file_path.c_str());

    }


}

/***********************************************************
 * Function: ls_with_l_filename
 * 
 * Description: execute ls -l filename
 * 
 * Input: @filename
 * 
 *
 * ***********************************************************/

void ls_with_l_filename(const char* filename)
{
    struct stat st;
    int ret = lstat(filename,&st);
    if(ret < 0)
    {
        perror("invalid input file:");
        return;
    }

    char perms[11] = {'\0'};

     
    switch( st.st_mode & S_IFMT )
    {
        case S_IFSOCK:  
            perms[0] = 's';
            break;
        case S_IFLNK:	 
            perms[0] = 'l';
            break;
        case S_IFREG:	 
            perms[0] = '-';
            break;
        case S_IFBLK:    
            perms[0] = 'b';
            break;
        case S_IFDIR:    
            perms[0] = 'd';
            break;
        case S_IFCHR:   
            perms[0] = 'c';
            break;
        case S_IFIFO:   
            perms[0] = 'p';
            break;
        default:
            break;

    }

    perms[1] = (st.st_mode & S_IRUSR) ? 'r':'-';
    perms[2] = (st.st_mode & S_IWUSR) ? 'w':'-';
    perms[3] = (st.st_mode & S_IXUSR) ? 'x':'-';

   
    perms[4] = (st.st_mode & S_IRGRP) ? 'r':'-';
    perms[5] = (st.st_mode & S_IWGRP) ? 'w':'-';
    perms[6] = (st.st_mode & S_IXGRP) ? 'x':'-';

    perms[7] = (st.st_mode & S_IROTH) ? 'r':'-';
    perms[8] = (st.st_mode & S_IWOTH) ? 'w':'-';
    perms[9] = (st.st_mode & S_IXOTH) ? 'x':'-';

    int nums = st.st_nlink;
    char *fileuser = getpwuid(st.st_uid)->pw_name;
    char *filegroup = getgrgid(st.st_gid)->gr_name;
    int size = (int)st.st_size;


    char *time = ctime(&st.st_mtime);
    char mtime[512] = {'\0'};
    strncpy(mtime,time,strlen(time)-1);

    char buf[1024]={0};

    sprintf(buf,"%s %d %s %s  %d\t%s\t%s",perms,nums,fileuser,filegroup,size,mtime,filename+2);

    puts(buf);
 

}

/***********************************************************
 * Function: ls_with_s
 * 
 * Description: execute ls -s
 * 
 * 
 * 
 *
 * ***********************************************************/

void ls_with_s()
{
    DIR *dir = nullptr;
	dir = opendir(".");

    vector<string> ls_names;

    if(dir)
    {
       struct dirent* entry = readdir(dir);
       while(entry)
       {
           if(strncmp(entry->d_name,".",strlen(".")) != 0 && strncmp(entry->d_name,"..",strlen("..")) != 0)
           {
               ls_names.push_back(entry->d_name);
           }

           
           entry = readdir(dir);
       }
    }

    closedir(dir);

    sort(ls_names.begin(),ls_names.end());

    for(auto iter = ls_names.rbegin(); iter != ls_names.rend(); iter++)
    {
        
        string file_path = "./";
        file_path.append(*iter);
        ls_with_s_filename(file_path.c_str());

    }
}


/***********************************************************
 * Function: ls_with_s_filename
 * 
 * Description: execute ls -s filename
 * 
 * Input: @filename
 *
 *
 * ***********************************************************/


void ls_with_s_filename(const char* filename)
{
    struct stat st;
    int ret = lstat(filename,&st);
    if(ret < 0)
    {
        perror("invalid input file:");
        return;
    }

    char buf[MAX_LENGTH] = {'\0'};

    snprintf(buf,MAX_LENGTH,"%ld\t%s",st.st_blocks,filename+2);// change from sprintf
    puts(buf);
}


/***********************************************************
 * Function: ls_with_file_type
 * 
 * Description: execute ls --file_type extension
 * 
 * Input: @extension, the extension of the file
 * 
 *
 * ***********************************************************/

void ls_with_file_type(const char* extension)
{
    DIR *dir = nullptr;
	dir = opendir(".");

    int len_ext = strlen(extension);

    vector<string> ls_names;

    if(dir)
    {
       struct dirent* entry = readdir(dir);
       while(entry)
       {      
           if(strncmp(entry->d_name,".",strlen(".")) != 0 && strncmp(entry->d_name,"..",strlen("..")) != 0)
           {
                int len_name = strlen(entry->d_name);
                if(strncmp(entry->d_name+len_name-len_ext,extension,len_ext) == 0)
                {
                    ls_names.push_back(entry->d_name);
                }
                
           }

           
           entry = readdir(dir);
       }
    }

    closedir(dir);

    sort(ls_names.begin(),ls_names.end());

    for(auto iter = ls_names.rbegin(); iter != ls_names.rend(); iter++)
    {
        puts(iter->c_str());
    }
}

/***********************************************************
 * Function: mul_ls
 * 
 * Description: execute ls command with multiple arguments
 * 
 * 
 * 
 *
 * ***********************************************************/

void mul_ls(Commands* commands,int index)
{
    if(strncmp(commands->cmds[index]->cmd_name,"ls",strlen("ls")) == 0)
    {
        if(strncmp(commands->cmds[index]->argument[0],"-r",strlen("-r")) == 0)  //execute ls -r
        {
            ls_with_r();
        }
        else if(strncmp(commands->cmds[index]->argument[0],"-l",strlen("-l")) == 0)  
        {
            if(commands->cmds[index]->argc == 1)
            {
                ls_with_l();  //execute ls -l
            }
            else if(commands->cmds[index]->argc == 2)
            {
                char filename[MAX_LENGTH] = {'\0'};
                strncpy(filename,commands->cmds[index]->argument[1],strlen(commands->cmds[index]->argument[1]));
                ls_with_l_filename(filename);  //execute ls -l filename
            }
            else{}
            
        }
        else if(strncmp(commands->cmds[index]->argument[0],"-s",strlen("-s")) == 0)
        {
            if(commands->cmds[0]->argc == 1)
            {
                ls_with_s();  //execute ls -s 
            }
            else if(commands->cmds[index]->argc == 2)
            {
                char filename[MAX_LENGTH] = {'\0'};
                strncpy(filename,commands->cmds[index]->argument[1],strlen(commands->cmds[index]->argument[1]));
                ls_with_s_filename(filename);  //execute ls -s  filename
            }
            else{}
            
        }
        else if(strncmp(commands->cmds[index]->argument[0],"--file-type",strlen("--file-type")) == 0)
        {
            if(commands->cmds[index]->argument[1][0] == '*' && commands->cmds[index]->argument[1][1] == '.' && strlen(commands->cmds[index]->argument[1])>2)
            {
                char extension[MAX_LENGTH] = {'\0'};
                strncpy(extension,commands->cmds[index]->argument[1]+2,strlen(commands->cmds[index]->argument[1])-2);
               
                if(strlen(extension) > 2)  //add the verification for the length of extension
                {
                    ls_with_file_type(extension);  //execute ls --file-type extension
                }
                else
                {
                    puts("invalid format of file extension");
                    return;
                }
                
                
            }
            else
            {
                puts("invalid format of file extension");
                return;
            }
            
        }
        else
        {
            ls_short();
            
        }

    }
}



/***********************************************************
 * Function: Implement the CD(changing directory) command
 *
 * Description: execute cd[directory]
 * I use default function in C++ library(chdir), for implementing the CD command
 *
 * ***********************************************************/
void changing_directory(char* path)
{
    if(chdir(path) < 0)
    {
        perror("cd: ");
    }
 
}

/***********************************************************
 * Function: is_redirection
 *
 * Description: verify if there is redirection operator in the command
 * 
 *
 * ***********************************************************/

int is_redirection(Commands* cmds)
{
    int num_arg = cmds->cmds[0]->argc;
    if(cmds->cmds[0]->argc >= 2)
    {
        if(strncmp(cmds->cmds[0]->argument[num_arg - 2],">>",2) == 0)
        {
            return APPEND_REDIRECT;
        }
        else if(strncmp(cmds->cmds[0]->argument[num_arg - 2],">",1) == 0)
        {
            return TRUNC_REDIRECT;
        }
        else if(strncmp(cmds->cmds[0]->argument[num_arg - 2],"<",1) == 0) 
        {
            return INPUT_REDIRECT;
        }
        else{}
    }

    return -1;
}

/***********************************************************
 * Function: redirection
 *
 * Description: redirect the stdout to the designated file
 * 
 *
 * ***********************************************************/

int redirection(int fd,int type,Commands* cmds)
{
    char file[MAX_LENGTH] = {'\0'};
    int num_argc = cmds->cmds[0]->argc;
    strncpy(file,cmds->cmds[0]->argument[num_argc-1],strlen(cmds->cmds[0]->argument[num_argc-1]));

    if(type == APPEND_REDIRECT)
    {
        fd = open(file,O_WRONLY|O_CREAT|O_APPEND,0664);
        if(fd < 0)
        {
            perror("open: ");
            return -1;
        }
    }
    else if(type == TRUNC_REDIRECT)
    {
        fd = open(file,O_WRONLY|O_CREAT|O_TRUNC,0664);
        if(fd < 0)
        {
            perror("open: ");
            return -1;
        }
    }
    else if(type == INPUT_REDIRECT)
    {
        fd = open(file,O_RDONLY);
        if(fd < 0)
        {
            perror("open: ");
            return -1;
        }
    }
    else{}
    
    if(type == INPUT_REDIRECT)
    {
        dup2(fd,STDIN_FILENO);
    }
    else
    {
        dup2(fd,STDOUT_FILENO);
    }
    
    
    return 0;

}

char* redirect_from_file(Commands* cmds,char* option)
{
    pid_t pid = fork();
    if(pid == 0)
    {
        int fd = -1;
        redirection(fd,INPUT_REDIRECT,cmds);
        fgets(option,MAX_LENGTH,stdin);

        
    }

    waitpid(pid,nullptr,0);
    return option;         
}

char* redirect_cmd(char* old_cmd,char* option,Commands* cmds)
{
    char file[MAX_LENGTH] = {'\0'};
    int num_argc = cmds->cmds[0]->argc;
    strncpy(file,cmds->cmds[0]->argument[num_argc-1],strlen(cmds->cmds[0]->argument[num_argc-1]));

    int fd = open(file,O_RDONLY);
    if(fd > 0)
    {
        read(fd,option,MAX_LENGTH);
    }
    close(fd);

    int i = 0;
    char tmpCmd[MAX_LENGTH] = {'\0'};
    for(; i < strlen(old_cmd); i++)
    {
        if(old_cmd[i] == '<')
        {
            break;
        }

    }

    strncpy(tmpCmd,old_cmd,i);
    strncat(tmpCmd,option,strlen(option));

    reset_commands(cmds);
    parse_cmd_line(tmpCmd,cmds,0);


}

void history()
{
    for(auto iter = all_commands.rbegin(); iter != all_commands.rend();iter++)
    {
        puts(iter->c_str());
    }
}

int is_service(Commands* cmd)
{
    int num_options = cmd->cmds[0]->argc;
    if(strncmp(cmd->cmds[0]->argument[num_options-1],"&",1) == 0)
    {
        cmd->cmds[0]->argc -= 1;
        return 1;
    }

    return 0;
}

void find(char* path, char* filename)
{

    if(strlen(filename) == 0)
    {
        return;
    }
    if(!pattern_validation(filename))
    {
        puts("invalid format of filename, only [a-zA-Z0-9.] allowed");
        return;
    }
    DIR *dir = nullptr;
	dir = opendir(path);

    if(dir)
    {
      
       struct dirent* entry = readdir(dir);
       while(entry)
       {
           if(strncmp(entry->d_name,".",strlen(".")) != 0 && strncmp(entry->d_name,"..",strlen("..")) != 0)
           {
               char full_path[MAX_LENGTH] = {'\0'};
               strncpy(full_path,path,strlen(path));
               strncat(full_path,"/",1);
               strncat(full_path,entry->d_name,strlen(entry->d_name));

               struct stat st;
               lstat(full_path,&st);

       
                if((st.st_mode & S_IFMT) == S_IFDIR)
                {
                   find(full_path,filename);
                }
                else
                {
                    if(strncmp(entry->d_name,filename,strlen(filename)) == 0)
                    {
                        puts(full_path);
                    }
                    else
                    {
                        regex re(get_pattern(filename));
                        if(regex_match(entry->d_name,re))
                        {
                            puts(full_path);
                        }
                    }
                    
                }
 
           }

           
           entry = readdir(dir);
       }
    }

    closedir(dir);
}

bool pattern_validation(char* filename)
{
    for(auto i = 0; i < strlen(filename); i++)
    {
        if(isalnum(filename[i]) || (filename[i] == '.') || (filename[i] == '*'))
        {
            continue;
        }
        else
        {
            return false;
        }
        
    }
    return true;
}



string get_pattern(char* filename)
{
    string pattern;
    for(auto i = 0; i < strlen(filename); i++)
    {
        if(isalnum(filename[i]) || (filename[i] == '.'))
        {
            char tmp[MAX_LENGTH] = {'\0'};
            strncpy(tmp,filename+i,1);
            pattern.append(tmp);
        }
        else if((filename[i] == '*'))
        {
            pattern.append(PATTERN);
        }
        else{}
    }
    
    return pattern;
}