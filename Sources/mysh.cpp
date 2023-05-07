#include "headers.h"

int main() {    

    // starting dir
    chdir("in-mysh-now");

    // total path
    list<string> path;

    // starting path
    string starting_path = "in-mysh-now";
    path.push_back(starting_path);
    
    // input line
    string line;

    list<string> history;

    // history output
    string out = "";

    map<string,vector<string>> aliases;
    
    // sc cntr-c signal sz cntr-z signal
    struct sigaction sc,sz;
    sc.sa_handler = SIG_IGN;    // shell process ignore signal
    sigfillset (&(sc.sa_mask));
    sc.sa_flags = 0; 
    sigaction(SIGINT, &sc, NULL);

    sz.sa_handler = SIG_IGN;    // shell process ignore signal
    sigfillset (&(sz.sa_mask));
    sz.sa_flags = 0;
    sigaction(SIGTSTP, &sz, NULL);

    // into shell
    while (true) {
        
        // get new path
        path = fix_path(path);
        if (out != "") {    // if execution is history execution

            print_path(path,out);
            
            // line get history execution + other input
            line = out;
            string next;
            getline(cin,next);
            line = line + next;
        }
        else {
            print_path(path,out);
            getline(cin,line);
        }
        out = "";
        
        // add line to history
        add_to_history(history,line);
        
        // split line to spaces and to special characters
        vector<string> tempt_split_line = string_line_to_vector(line);
        
        // concatenate >,> to >>
        vector<string> split_line = concatenate(tempt_split_line);

        // split input lines into ;
        vector<vector<string>> lines = find_processes(split_line);

        // for all split lines to ; make execution
        for(vector<vector<string>>::iterator it = lines.begin(); it != lines.end(); it++) {
            vector<string> temp_line = *it;

                Process main_process;
                Files files;
                vector<Process> pipes;
                vector<string> parsing_line = temp_line;

                // replace aliases if command isn't alias command
                if(temp_line[0] != "destroyalias" && temp_line[0] != "createalias")
                    parsing_line = replace_aliases(temp_line,aliases);
                
                // parse line
                parser(parsing_line,main_process,files,pipes);

                // replace arguments of process with rules of wildcards    
                wildcards(main_process,pipes);
                
                // if command is history command don't put it to history
                if(main_process.get_name() == "history") history.pop_front();

                // make process execution
                tuple<string,string> r_tuple = execute_processes(main_process,pipes,files,history,sc,sz,aliases);
                
                // tuple(0) = history output, tuple(1) = new path 
                
                out = get<0>(r_tuple);
                string t_path = get<1>(r_tuple);
                
                // if new path exists merge it to old
                if(t_path != "") { 
                    list<string> temp_path = path_string_to_list(t_path);
                    merge_path(path,temp_path);
                }
        }
    }
}