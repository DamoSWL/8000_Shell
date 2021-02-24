#include "function.h"

using namespace std;



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
    DIR *dir;
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
    DIR *dir;
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
    DIR *dir;
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
 * Description: execute ls -r filename
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
    DIR *dir;
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

    snprintf(buf,MAX_LENGTH,"%lld\t%s",st.st_blocks,filename+2);//here
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
    DIR *dir;
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
 * Function: Implement the CD(changing directory) command
 *
 * Description: execute cd[directory]
 * I use default function in C++ library(chdir), for implementing the CD command
 *
 * ***********************************************************/
void changing_directory(char* path){
    if(chdir(path)>=0){
        char buf[80];
       // char* directory = get_current_dir_name();
        getcwd(buf,sizeof(buf));
        printf("Current directory is:%s\n",buf);
    }
    else{
        printf("[ERROR]: cd '%s' : No such path\n",path);
    }
}