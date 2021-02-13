#include "function.h"

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