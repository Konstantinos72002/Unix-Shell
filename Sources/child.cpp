#include "headers.h"

void execute_main_process(process &process) {
	int num_of_args = process.num_of_arguments();
	vector<string> vector_arguments = process.get_arguments();
	string process_name_string = process.get_name();
	
	char** arguments = strlist(vector_arguments);
	char * process_name = str_to_chars(process_name_string);
	if (num_of_args == 0) {
		cout << "edo mpainei" << endl;
		char *argv[] = { NULL };
		execvp(process_name,argv);
	}
	else {
		execvp(process_name, arguments);
	}

	delete [] arguments;
	delete process_name;
	
	return ;
}