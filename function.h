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
#include <vector>
#include <string>
#include <vector>
#include <algorithm>
#include "util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <pwd.h>     
#include <grp.h>    
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>




void pwd();
void ls_short();
void ls_with_r();
void changing_directory(char* path);

void ls_with_l();
void ls_with_l_filename(const char* filename);

void ls_with_s();
void ls_with_s_filename(const char* filename);
void ls_with_file_type(const char* extension);
void mul_ls(Commands* commands,int index);

int is_redirection(Commands* cmd);
int redirection(int fd,int type,Commands* cmd);
char* redirect_from_file(Commands* cmds,char* option);
char* redirect_cmd(char* old_cmd,char* option,Commands* cmd);

void history();

int is_service(Commands* cmd);

void find(char* path, char* filename);

#endif