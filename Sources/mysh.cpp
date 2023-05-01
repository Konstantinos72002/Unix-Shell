#include "headers.h"

int main() {    
    pid_t parent_id = getpid();
    string line;
    list<string> history;
    string out;
    // make reading
    while (true) {
        
        cout << "in-mysh-now:> " << out;
        out = "";
        getline(cin,line);
        
        
        add_to_history(history,line);

        vector<string> tempt_split_line = tokenize(line);
        vector<string> split_line = concatenate_redirections(tempt_split_line);

        Process main_process;
        Files files;
        vector<Process> background_processes;
        vector<Process> pipes;
       
        vector<int> details = parser(split_line,main_process,files,background_processes,pipes);
        
        out = execute_processes(main_process,background_processes,pipes,files,history);
    }
}