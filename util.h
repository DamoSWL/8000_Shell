#ifndef  __UTIL_H__
#define  __UTIL_H__


#define MAX_COUNT 10
#define MAX_LENGTH 1024


typedef struct Command 
{		   
	int argc;                  
	char *cmd_name;                
	char *argument[MAX_COUNT]; 
}Command;


typedef struct Commands 
{                  
	int cmd_count;             
	Command *cmds[MAX_COUNT];   
}Commands;

Commands* create_commands();
void reset_commands(Commands* cmds);

void parse_cmd_line(const char* cmdLine, Commands* commands,int index);
int pipeline_flag(const char* cmdLine);

void execute_cmd(Commands* commands);


#endif