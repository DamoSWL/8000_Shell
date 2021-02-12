#include <iostream>
#include <string>
#include <sstream>

using namespace std;
static string command_list[100];

void shell_loop(void);
std::string read_line(void);
void understand_line(string line);
int execute(string command_list[100]);




int main() {

    //load config files
    //Run the while loop
    shell_loop();
    //Cleanup
    return 0;
}

void shell_loop(void){
    string line;
    int status ;
    while(status !=0)
    {
        line = read_line();
        understand_line(line);
        status = execute(command_list);
    }
}
string read_line(void){
        string str;
        cout << ">> ";
        getline(cin, str);
        return str;
}
void understand_line(string line){

    string temp;
    //static string command_list[100];
    int i=0;

    stringstream ss(line);
    while(getline(ss, temp, ' ')){
        command_list[i] = temp;
        cout<<command_list[i]<<endl;
        i++;
    }

}

int execute(string command_list[100]) {
    int i;

    //exit function
    if (command_list[0].compare("0") == 0) {
        return 0;
    }
    return 1;
}