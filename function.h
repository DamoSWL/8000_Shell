#ifndef __FUNCTION_H__
#define __FUNCTION_H__



#include <stdio.h>  
#include <sys/stat.h>  
#include <dirent.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/types.h> 
#include  <unistd.h>



int getinode(char *str);
char *inode_to_name(int inode);
void pwd();



#endif