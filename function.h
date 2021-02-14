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
#include "util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<pwd.h>     
#include<grp.h>    
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>



void pwd();
void ls_short();
void ls_with_r();

void ls_with_l();
void ls_with_l_filename(const char* filename);

void ls_with_s();
void ls_with_s_filename(const char* filename);
void ls_with_file_type(const char* extension);



#endif