#include "headers.h"

void print_path(list<string> &path,string &out) {

	for(list<string>::iterator it = path.begin() ; it != path.end() ; it++) {
		cout << *it << "/";
	}
		cout <<":> ";
	if(out != "") cout << out; 
}

list<string> path_string_to_list(string &path) {

	// iterate string
	string::iterator it = path.begin();
	list<string> return_path;
	string insert_string;
	while(it != path.end()) {
		
		// if you find / push in list the until now world
		if(*it != '/') {
			insert_string.push_back(*it);
		}	
		// else merge one more char to world 
		else {
			return_path.push_back(insert_string);
			insert_string.clear();
		}
		it++;
		if(it == path.end()) {
			return_path.push_back(insert_string);
			break;
		}
	}

	return return_path;
}

list<string> fix_path(list<string> &path) {
	list<string> return_path;
	stack<string> st;

	// for all strings in path
	for(list<string>::iterator it = path.begin() ; it != path.end() ; it++) {
		// if you find .. pop from stack, if you find something diferent push it to stack
		
		if(*it == "..") {
			if(st.size() == 0) {
				cout << "You can't exit this folder" << endl;
				exit(-1);
			} 
			st.pop();
		} else {
			st.push(*it);
		}
	}
	
	// put stack to list and return it
	while(st.size() != 0) {
		return_path.push_front(st.top());
		st.pop();
	}
	return return_path;
}

void merge_path(list<string> &o_r_path, list<string> &new_path) {
	for(list<string>::iterator it = new_path.begin() ;it != new_path.end(); it++) {
		o_r_path.push_back(*it);
	}
}

vector<string> replace_aliases(vector<string> &line,map<string,vector<string>> &aliases)
{
		// for all worlds in line
		vector<string> return_vector;
		vector<string>::iterator it = line.begin(); 
		while(it != line.end()) {
			string argument = *it;
			// if world exist in alias map replace it and put it to return vector else insert the world
			auto a_it = aliases.find(argument);
			if (a_it == aliases.end()) {
				return_vector.push_back(argument);
				it++;
				continue;
			}
			vector<string> replace_argument = a_it->second;
			for(vector<string>::iterator a_it = replace_argument.begin() ; a_it != replace_argument.end() ; a_it++) {
				return_vector.push_back(*a_it);
			}
			it++;
		}

		return return_vector;;
}

void merge_vectors(list<string> &o_r_path, list<string> &new_path) {
	for(list<string>::iterator it = new_path.begin() ;it != new_path.end(); it++) {
		o_r_path.push_back(*it);
	}
}

void create_alias(vector<string> &arguments,map<string,vector<string>> &aliases) {
	vector<string>::iterator it = arguments.begin();

	// insert to map aliases the new alias

	//delete createalias
	arguments.erase(it);

	// delete and save name
	it = arguments.begin();
	string name = *it;
	arguments.erase(it);

	// delete " "
	it = arguments.begin();
	arguments.erase(it);
	arguments.pop_back();
	
	aliases.insert(make_pair(name,arguments));
}