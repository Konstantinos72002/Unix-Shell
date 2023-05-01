#include "headers.h"

string Files::get_input() {
	return this->input;
}
vector<tuple<string,bool>> Files::get_outputs() {
	return this->outputs;
}
bool Files::input_is_empty() {
	return this->input.empty(); 
}
bool Files::outputs_is_empty() {
	return !this->outputs.size();
}
void Files::insert_input(string file) {
	this->input = file;
}
void Files::insert_output(string file,bool flag) {
	this->outputs.push_back({file,flag});
}