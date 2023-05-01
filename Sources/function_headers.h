#include "headers.h"

using namespace std;

class Process {
	string name;
	vector<string> arguments;
	pid_t pid;
	
	public:
		string get_name();
		vector<string> get_arguments();
		pid_t get_pid();
		void change_name(string);
		void insert_argument(string);
		void change_pid(pid_t);
		void print_informations();
		const void print_arguments(vector<string>); 
		int num_of_arguments();
};

class Files {
	string input;
	vector<tuple<string,bool>> outputs;

	public:
		string get_input();
		vector<tuple<string,bool>> get_outputs();
		vector<bool> get_flags();
		bool input_is_empty();
		bool outputs_is_empty();
		void insert_input(string);
		void insert_output(string,bool);
};

vector<string> tokenize(const string &);

vector<int> parser(vector<string>,Process &,Files &,vector<Process>,vector<Process> &);

vector<string> concatenate_redirections(vector<string> &);

void execute_files(Files &);

string execute_processes(Process &,vector<Process> &,vector<Process> &,Files &,list<string> &);

void recursive_pipes(vector<Process> &);

string execute_main_process(Process &,list<string> &,Files &);

// void execute_with_files(Process &, Files &);

void execute_inputs(string);

void execute_outputs(vector<tuple<string,bool>>);

char ** strlist(vector<string> &);

char* str_to_chars(string &);

void add_to_history(list<string> &,string &);