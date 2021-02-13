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
           ls_names.push_back(entry->d_name);
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
           ls_names.push_back(entry->d_name);
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