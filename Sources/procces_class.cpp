#include "headers.h"

string Process:: get_name() { 
	return name;
}

vector<string> Process::get_arguments() {
	return arguments;
}

void Process::change_name(string name) {
	this->name = name;
}
		

void Process::insert_argument(string argument) {
	this->arguments.push_back(argument);
}

void Process::print_informations() {
	cout << "procces name: " << this->get_name() << endl;
	cout << "process arguements: "; this->print_arguments(this->get_arguments());
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

void Process::set_background(bool flag) {
	this->is_background = flag;
}
bool Process::get_background() {
	return this->is_background;
}

void Process::change_all_arguments(vector<string> &new_args) {
	this->arguments = new_args;
}