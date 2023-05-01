#include "headers.h"

string Process:: get_name() { 
	return name;
}

vector<string> Process::get_arguments() {
	return arguments;
}

pid_t Process::get_pid() {
	return pid;
}

void Process::change_name(string name) {
	this->name = name;
}
		

void Process::insert_argument(string argument) {
	this->arguments.push_back(argument);
}

void Process::change_pid(pid_t pid) {
	this->pid = pid;
}

void Process::print_informations() {
	cout << "procces name: " << this->get_name() << endl;
	cout << "process arguements: "; this->print_arguments(this->get_arguments());
	cout << "process id: " << this->get_pid() << endl;
}

const void Process::print_arguments(vector<string> arguments) {
	for(vector<string>::iterator it = arguments.begin(); it != arguments.end(); it++) {
		cout << *it;
	}
	cout << endl;
}

int Process::num_of_arguments() {
	return arguments.size();
}