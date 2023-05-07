#include "headers.h"
#define is_special(tokken) (tokken == ">" || tokken == "<" || tokken == ">>" || tokken == "|" || tokken == "&" || tokken == ">>" || tokken == "\0")

void parser(vector<string> line,Process &main_process,Files & files,vector<Process> &pipes) {
	
	// it iterate line
	vector<string>::iterator it = line.begin();
	
	bool already = 0; // 0 if haven't insert main_process to pipes
	it = line.begin();
	while(it != line.end()) {

		if(!is_special(*it)) {	// you find main_process
			main_process.change_name(*it);
			main_process.insert_argument(*it);
			main_process.set_background(false);
			it++;

			// check if is background process
			if (it != line.end()) {
				while(!is_special(*it) || *it == "&") {
					if(it == line.end()) break;
					if(*it == "&") {
						main_process.set_background(true);
						it++;
						break;
					}
					main_process.insert_argument(*it);
					it++;
					if(it == line.end()) break;
				}
			}
		}

		if(it == line.end()) break;
		if(*it == "<") {	// find input file
			
			if (it+1 == line.end()) {
				cerr << "Input file error" << endl;
				exit(1);
			}
			if (is_special(*(it+1))) {
				cerr << "Input file error" << endl;
				exit(1);
			}
			if(files.input_is_empty()) {
				files.insert_input(*(++it));
			} else {
				cerr << "Only one redirection file" << endl;
				exit(1);
			}
		}

		if(it == line.end()) break;
		if(*it == ">" || *it == ">>") {	// find output file
			
			if (it+1 == line.end()) {
				cerr << "Output file error1" << endl;
				exit(1);
			}
			if (is_special(*(it+1))) {
				cerr << "Output file error2" << endl;
				exit(1);
			}
			if (*it == ">") files.insert_output(*(++it),true);
			if (*it == ">>") files.insert_output(*(++it),false);
		}

		if(it == line.end()) break;
		if(*it == "|") {	// find pipe
			if(!already) {	// if you haven't insert main_process to pipes
				already = 1;
				// Insert main process to pipes
				Process insert_process;
				insert_process.change_name(main_process.get_name());
				vector<string> temp = main_process.get_arguments();
				for(vector<string>::iterator temp_it = temp.begin(); temp_it != temp.end(); temp_it++) {
					insert_process.insert_argument(*temp_it);
				}
				pipes.push_back(insert_process);
			}
			Process new_insert_process;
			// Insert process to pipes
			new_insert_process.change_name(*(++it));
			new_insert_process.insert_argument(*it);
			while(++it != line.end()) {
				if(is_special(*it)) break;	
				new_insert_process.insert_argument(*it);
			}
			pipes.push_back(new_insert_process);
			it--;
		}
		
		if(it == line.end()) break;
 		it++;
	}
	
	return;
}