#include "headers.h"

void execute_main_process(process &process) {
	int num_of_args = process.num_of_arguments();
	vector<string> vector_arguments = process.get_arguments();
	string process_name_string = process.get_name();

	char** arguments = strlist(vector_arguments);
	char * process_name = str_to_chars(process_name_string);

	char** name_args = (char**)malloc(num_of_args + 1);
	for (int i = 0; i < num_of_args+1; i++) {
		if(i == 0) {
			name_args[i] = (char*)malloc(sizeof(process_name));
		}
		else {
			name_args[i] = (char*)malloc(sizeof(arguments[i-1]));
		}
	}

	for(int i = 0; i < sizeof(name_args);i++) {
		cout << name_args[i] << endl;
	}

	if (num_of_args == 0) {
		cout << "edo mpainei" << endl;
		char *argv[] = {process_name, NULL };
		execvp(process_name,argv);
	}
	else {
		execvp(process_name, arguments);
	}

	delete [] arguments;
	delete process_name;
	
	return ;
}