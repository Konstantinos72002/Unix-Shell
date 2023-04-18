#include "headers.h"

string process:: get_name() { 
	return name;
}

vector<string> process::get_arguments() {
	return arguments;
}

pid_t process::get_pid() {
	return pid;
}

void process::change_name(string name) {
	this->name = name;
}
		

void process::insert_argument(string argument) {
	this->arguments.push_back(argument);
}

void process::change_pid(pid_t pid) {
	this->pid = pid;
}

void process::print_informations() {
	cout << "procces name: " << this->get_name() << endl;
	cout << "process arguements: "; this->print_arguments(this->get_arguments());
	cout << "process id: " << this->get_pid() << endl;
}

const void process::print_arguments(vector<string> arguments) {
	for(vector<string>::iterator it = arguments.begin(); it != arguments.end(); it++) {
		cout << *it;
	}
	cout << endl;
}

int process::num_of_arguments() {
	return arguments.size();
}