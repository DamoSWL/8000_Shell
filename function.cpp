#include "function.h"

using namespace std;

int getinode(char *str)  
{  
    struct stat st;  
    if(stat(str,&st) == -1){  
        perror(str);  
        exit(-1);  
    }  
    return st.st_ino;  
}
 

char *inode_to_name(int inode)  
{  
    char *str;  
    DIR *dirp;  
    struct dirent *dirt;  
    if((dirp = opendir(".")) == NULL){  
        perror(".");  
        exit(-1);  
    }  
    while((dirt = readdir(dirp)) != NULL)  
    {  
        if(dirt->d_ino == inode){  
            str = (char *)malloc(strlen(dirt->d_name)*sizeof(char));  
            strcpy(str,dirt->d_name);  
            return str;  
        }  
    }  
    perror(".");  
    exit(-1);  
}

void pwd()  
{  
    int inode,up_inode;  
    char *str;  
    inode = getinode((char*)".");  
    up_inode = getinode((char*)"..");  
    chdir("..");  
    str = inode_to_name(inode);  
    if(inode == up_inode) {  
        return;  
    }  
    pwd();  
    printf("/%s",str);  
}  



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

    snprintf(buf,MAX_LENGTH,"%ld\t%s",st.st_blocks,filename+2);
    puts(buf);
}

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