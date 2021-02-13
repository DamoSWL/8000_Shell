#ifndef __FUNCTION_H__
#define __FUNCTION_H__



#include <stdio.h>  
#include <sys/stat.h>  
#include <dirent.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/types.h> 
#include <unistd.h>
#include <dirent.h>

#include <string>
#include <vector>
#include <algorithm>



int getinode(char *str);
char *inode_to_name(int inode);

void pwd();
void ls_short();
void ls_with_r();



#endif