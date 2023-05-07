#include "headers.h"

using namespace std;

// process characteristics
class Process {
	string name;	// process name
	vector<string> arguments; // process arguments. argument[0] is process name
	bool is_background; // true is process is background process
	
	public:
		// getters
		string get_name();
		vector<string> get_arguments();
		bool get_background();

		// setters
		void change_name(string);
		void insert_argument(string);
		void set_background(bool);

		void print_informations();	// print all characteristics of process
		const void print_arguments(vector<string>);  // print arguments of function
		
		int num_of_arguments();	// return number of arguments
		
		void change_all_arguments(vector<string>&);	// change all arguments of process with new
};

// class with files
class Files {
	string input;	// input file name
	vector<tuple<string,bool>> outputs; // output files names, true if > false if >>

	public:
		
		//getters
		string get_input();
		vector<tuple<string,bool>> get_outputs();
		
		// insert files
		void insert_input(string);
		void insert_output(string,bool);
		
		bool input_is_empty();
		bool outputs_is_empty();
		
};

// split a string line to vector of strings into spaces and into special characters
vector<string> string_line_to_vector(string &);

// split deferent line executes into ;
vector<vector<string>> find_processes(vector<string> &);

// getting a line, find main_process of line, files of line, and pipe processes of line if exists
void parser(vector<string>,Process &,Files &,vector<Process> &);

// concatenate >,> to >>
vector<string> concatenate(vector<string> &);

// open input and outputs redirections
void execute_files(Files &);

// execute command and return <history output, new path> if something don't exist return "" at this place
tuple<string,string> execute_processes(Process &,vector<Process> &,Files &,list<string> &,
struct sigaction &,struct sigaction &,map<string,vector<string>> &);

// execvp process
void execute_main_process(Process &,list<string> &,Files &,bool);

// rederict stdin to input file
void execute_input(string);

// rederict stdout to latst output file, open all between files and if last is > delete includes and write
// else if is >> append to file
void execute_outputs(vector<tuple<string,bool>>);

// Vector of strings to char** and null at the end
char ** strlist(vector<string> &);

// string to character
char* str_to_chars(string &);

// add line to history
void add_to_history(list<string> &,string &);

// if process is alias or cd or exit or history execute in this function
tuple<string,string> special_cases(Process &,list<string> &,map<string,vector<string>> &);

// replace process arguments with new one following bash wildcards rules
void wildcards(Process &,vector<Process> &);

// used by wildcards
static void fix_args(Process &);

// print path and history output if exist
void print_path(list<string> &,string &);

// in path if exist .. delete it and delete the previous folder of that and return new path
list<string> fix_path(list<string> &);

// throw / and keep worlds and put it in a list of strings
list<string> path_string_to_list(string &);

// merge previus path with new in previus
void merge_path(list<string> &, list<string> &);

// replace aliases
vector<string> replace_aliases(vector<string> &,map<string,vector<string>> &);

// insert to alias map the new alias
void create_alias(vector<string> &,map<string,vector<string>> &);