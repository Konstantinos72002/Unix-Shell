#include "headers.h"

int main()
{    
    pid_t parent_id = getpid();
    string line;
    
    // make reading
    while (true) {
        cout << "in-mysh-now:> ";
        getline(cin,line);
        
        vector<string> split_line;
        
        split_line = tokenize(line);

        
        process main_process;
        string input_file,output_file;
        vector<process> background_processes;
        vector<int> pipes;
       
        vector<int> details = execute(split_line,main_process,input_file,output_file,background_processes,pipes);

        
        if(details[0] == 1) {
            pid_t pid = fork() ;
            //     cerr << "Fork error" << endl;
            //     exit(1);
            // }    
            if (pid == 0) {
                execute_main_process(main_process);
            }
            else {
                int status;
                wait(&status);
            }
        }
    }
}