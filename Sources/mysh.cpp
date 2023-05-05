#include "headers.h"

int main() {    
    chdir("in-mysh-now");
    list<string> path;
    string starting_path = "in-mysh-now";
    path.push_back(starting_path);
    pid_t parent_id = getpid();
    string line;
    list<string> history;
    string out = "";
    vector<pid_t> background;
    map<string,vector<string>> aliases;
    struct sigaction sc,sz;
    sc.sa_handler = SIG_IGN;
    sigfillset (&(sc.sa_mask));
    sc.sa_flags = 0; 
    sigaction(SIGINT, &sc, NULL);

    sz.sa_handler = SIG_IGN;
    sigfillset (&(sz.sa_mask));
    sz.sa_flags = 0;
    sigaction(SIGTSTP, &sz, NULL);

    // make reading
    while (true) {
        
        path = fix_path(path);
        if (out != "") {
            cout << out << endl;
            print_path(path,out);
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
        
       
        add_to_history(history,line);

        vector<string> tempt_split_line = string_line_to_vector(line);
        vector<string> split_line = concatenate(tempt_split_line);
        vector<vector<string>> lines = find_processes(split_line);
        for(vector<vector<string>>::iterator it = lines.begin(); it != lines.end(); it++) {
            vector<string> temp_line = *it;

                Process main_process;
                Files files;
                vector<Process> pipes;
                vector<string> parsing_line = temp_line;

                if(temp_line[0] != "destroyalias" && temp_line[0] != "createalias")
                    parsing_line = replace_aliases(temp_line,aliases);

                parser(parsing_line,main_process,files,pipes);
                
                wildcards(main_process,pipes);
                
                if(main_process.get_name() == "history") history.pop_front();

                tuple<string,string> r_tuple = execute_processes(main_process,pipes,background,files,history,sc,sz,aliases);
                // if(main_process.get_name() != "history" && main_process.get_arguments().size() == 2) out = get<0>(r_tuple);
                out = get<0>(r_tuple);
                string t_path = get<1>(r_tuple);
                if(t_path != "") { 
                    list<string> temp_path = path_string_to_list(t_path);
                    
                    merge_path(path,temp_path);
                }
                
        }
    }
}