#include "headers.h"

using namespace std;

class process {
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

vector<string> tokenize(const string &);

vector<int> execute(vector<string>,process &,string &,string &,vector<process>,vector<int>);

void execute_main_process(process &);

char ** strlist(vector<string> &);

char* str_to_chars(string &input);