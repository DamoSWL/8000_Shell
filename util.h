#ifndef  __UTIL_H__
#define  __UTIL_H__


#define MAX_COUNT 10
#define MAX_LENGTH 1024

// data structure for single command
typedef struct Command 
{		   
	int argc;         //the number of the options         
	char *cmd_name;   // the name of the command
	char *argument[MAX_COUNT];  //the string of the options for the command
}Command;

// data structure for all the commands in a single command line, separated by the pipeline(|)
typedef struct Commands 
{                  
	int cmd_count;            //the number of the commands 
	Command *cmds[MAX_COUNT];   //the command structure
}Commands;

Commands* create_commands();
void reset_commands(Commands* cmds);

void parse_cmd_line(const char* cmdLine, Commands* commands,int index);
int pipeline_flag(const char* cmdLine);

void execute_cmd(Commands* commands);


#endif