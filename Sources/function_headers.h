#include "headers.h"

using namespace std;

class Process {
	string name;
	vector<string> arguments;
	pid_t pid;
	bool is_background;
	
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
		void set_background(bool);
		bool get_background();
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

vector<vector<string>> find_processes(vector<string> &);

vector<int> parser(vector<string>,Process &,Files &,vector<Process> &);

vector<string> concatenate(vector<string> &);

void execute_files(Files &);

string execute_processes(Process &,vector<Process> &,vector<pid_t> &,Files &,list<string> &);

void recursive_pipes(vector<Process> &);

string execute_main_process(Process &,list<string> &,Files &);

// void execute_with_files(Process &, Files &);

void execute_inputs(string);

void execute_outputs(vector<tuple<string,bool>>);

char ** strlist(vector<string> &);

char* str_to_chars(string &);

void add_to_history(list<string> &,string &);

string special_cases(Process &,list<string> &);

void background_start(Process &,vector<pid_t> &);

void background_end(Process &,vector<pid_t> &);