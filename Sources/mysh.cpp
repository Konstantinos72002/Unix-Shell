#include "headers.h"

int main() {    
    pid_t parent_id = getpid();
    string line;
    list<string> history;
    string out;
    vector<pid_t> background;
    // make reading
    while (true) {
        
        
        if (out != "") {
            cout << "in-mysh-now:> " << out;
            line = out;
            string next;
            getline(cin,next);
            line = line + next;
        }
        else {
            cout << "in-mysh-now:> ";
            getline(cin,line);
        }
        out = "";
        
       
        add_to_history(history,line);

        vector<string> tempt_split_line = tokenize(line);
        vector<string> split_line = concatenate(tempt_split_line);
        vector<vector<string>> lines = find_processes(split_line);
        for(vector<vector<string>>::iterator it = lines.begin(); it != lines.end(); it++) {
            vector<string> line = *it;

            Process main_process;
            Files files;
            vector<Process> pipes;
        
            vector<int> details = parser(line,main_process,files,pipes);
            
            out = execute_processes(main_process,pipes,background,files,history);
        }
    }
}