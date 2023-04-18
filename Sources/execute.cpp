#include "headers.h"
#define is_special(tokken) (tokken == ">" || tokken == "<" || tokken == ">>" || tokken == "|" || tokken == "&;" || tokken == "\0")
vector<int> execute(vector<string> line,process &main_process,string &input_file,string &output_file,
vector<process> background_processes,vector<int> pipes) {

	vector<int> details(5,0);
	
	vector<string>::iterator it = line.begin();

	if(it == line.end() || is_special(*it)) return details;
	
	main_process.change_name(*it);
	details.at(0) = 1;
	it++;
	
	if (it != line.end()) {		
		while(!is_special(*it) & it != line.end()) {			
			main_process.insert_argument(*(it++));
			if(it == line.end()) break;
		}
	}

	while(it != line.end()) {
		string tokken = *it;
		
		if(tokken == ">") {
			details.at(2) = 1;
			if (it == line.end()) {
				cerr << "Output file error" << endl;
				exit(1);
			}
			if (is_special(*it)) {
				cerr << "Output file error" << endl;
				exit(1);
			}
			output_file = *(++it);			
		}
		if(tokken == "<") {
			details.at(1) = 1;
			if (it == line.end()) {
				cerr << "Input file error" << endl;
				exit(1);
			}
			if (is_special(*it)) {
				cerr << "Input file error" << endl;
				exit(1);
			}
			input_file = *(++it);
		}

 		it++;
	}
	return details;
}