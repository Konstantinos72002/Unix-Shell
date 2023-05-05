#include "headers.h"

void print_path(list<string> &path,string &out) {

	for(list<string>::iterator it = path.begin() ; it != path.end() ; it++) {
		cout << *it << "/";
	}
		cout <<":> ";
	if(out != "") cout << out; 
}

list<string> path_string_to_list(string &path) {
	string::iterator it = path.begin();
	list<string> return_path;
	string insert_string;
	while(it != path.end()) {
		
		if(*it != '/') {
			insert_string.push_back(*it);
		}
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

	for(list<string>::iterator it = path.begin() ; it != path.end() ; it++) {
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
		vector<string> return_vector;
		vector<string>::iterator it = line.begin(); 
		while(it != line.end()) {
			string argument = *it;
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

// void replace_aliases_process(Process &process,map<string,string> &aliases) {
// 	vector<string> arguments = process.get_arguments();
// 	vector<string>::iterator it = arguments.begin();
// 	it++;
// 	while(it != arguments.end()) {
		// string argument = *it;
		// auto a_it = aliases.find(argument);
		// if (a_it == aliases.end()) continue;
		// string replace_argument = a_it->second;
		// *it = replace_argument;	
// 	}
// }

void create_alias(vector<string> &arguments,map<string,vector<string>> &aliases) {
	vector<string>::iterator it = arguments.begin();
	
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