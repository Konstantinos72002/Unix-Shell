#include "headers.h"

void execute_files(Files &files) {
	if (!files.input_is_empty()) {
		execute_inputs(files.get_input());
	}
	if(!files.outputs_is_empty()) {
		execute_outputs(files.get_outputs());
	}
}

string execute_processes(Process &main_process,vector<Process> &background_processes,vector<Process> &pipes,
Files &files , list<string> &history) {
	
	if(pipes.size() == 0) {
		
		pid_t pid = fork();
		if(pid == 0) {
			return execute_main_process(main_process,history,files);
		}
		else {
			int status;
			wait(&status);
		}
		return "";
	} else {

		int num_of_pipes = pipes.size()-1;
		vector<int[2]> fd(num_of_pipes);
		
		for(int i=0; i < num_of_pipes ; i++) {
			pipe(fd[i]);
		}
		int num_of_processes = num_of_pipes + 1;
		vector<pid_t> pids(num_of_processes);
		for (int i = 0; i<num_of_processes ; i++) {
			
			pids[i] = fork();
			if (pids[i] == 0) {
				if (i == 0) { 
					close(fd[i][0]);  // not read
					dup2(fd[i][1], STDOUT_FILENO); // write
					execute_main_process(pipes[i],history,files); 
					close(fd[i][1]); // close write
				} else if (i == num_of_processes-1) {
					close(fd[i-1][1]); // not write
					dup2(fd[i-1][0], STDIN_FILENO); // read from previuous 
					execute_main_process(pipes[i],history,files);
					close(fd[i-1][0]);  //close read
				} else {
					close(fd[i-1][1]); 
					dup2(fd[i-1][0], STDIN_FILENO); // read from previuous
					close(fd[i][0]);
					dup2(fd[i][1], STDOUT_FILENO); // write
					
					execute_main_process(pipes[i],history,files);

					close(fd[i-1][0]);  //close read
					close(fd[i][1]); // close write
				}
				
			}
		}
		for(int i=0;i<num_of_pipes;i++) {
			close(fd[i][0]);
			close(fd[i][1]);
		}

		for (int i = 0; i < num_of_processes; i++) {
			
        	waitpid(pids[i], NULL, 0);
   	 	}
		

	}

return "";
}

string execute_main_process(Process &process, list<string> &history, Files &files) {
	execute_files(files);
	int num_of_args = process.num_of_arguments();
	vector<string> vector_arguments = process.get_arguments();
	// for (vector<string>::iterator it = vector_arguments.begin(); it!= vector_arguments.end() ; it++) cout << *it << endl;
	string process_name_string = process.get_name();

	char** arguments = strlist(vector_arguments);
	
	char * process_name = str_to_chars(process_name_string);
	
	if(!strcmp(process_name,"history") && process.get_arguments().size() == 1) {
		cout << "Last " << history.size() << " executes:" << endl;
		for(list<string>::iterator it = history.begin(); it != history.end() ; it++) {
			cout << *it << endl;
		}
		return "";
	}

	if(!strcmp(process_name,"history")) {
		list<string>::iterator it = history.begin();
		for(int i = 0; i < stoi(process.get_arguments()[1]); i++) it++;
		return *it;
	}

	execvp(process_name, arguments);
	perror("execvp"); // execvp returns only if an error occurred
    exit(1);
	
	delete [] arguments;
	delete process_name;
	
	return "";
}

// void execute_with_files(Process &process, Files &files) {
// 	if (!files.input_is_empty()) {
// 		execute_inputs(files.get_input());
// 	}
// 	if(!files.outputs_is_empty()) {
// 		execute_outputs(files.get_outputs());
// 	}
// 	execute_main_process(process);
// }

void execute_inputs(string inputs) {

	char* input_c = str_to_chars(inputs);
	int inputfile = open(input_c, O_RDONLY);
	dup2(inputfile, 0);
	close(inputfile);
}

void execute_outputs(vector<tuple<string,bool>> outputs) {
	
	for(vector<tuple<string,bool>>::iterator it = outputs.begin(); it != outputs.end(); ++it){ 
		char* output_c = str_to_chars(get<0>(*it));
		bool flag = get<1>(*it);
		int outfile;
		if(flag) {
			outfile = open(output_c, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		} else {
			outfile = open(output_c, O_WRONLY | O_APPEND , S_IRUSR | S_IWUSR);
		}
			if (*it == *(outputs.end() - 1)) {
				dup2(outfile, STDOUT_FILENO);
				close(outfile);
			}
	}
}