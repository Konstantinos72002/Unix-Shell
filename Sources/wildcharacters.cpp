#include "headers.h"

void wildcards(Process &process,vector<Process> &pipes) {
	
	// if we haven't pipes replace only main process arguments
	if(pipes.size() == 0) {
		fix_args(process);
	} else {	// if we have pipes for all pipe processes replace arguments
		fix_args(process);
		for(vector<Process>::iterator it = pipes.begin(); it!= pipes.end(); it++) {
			fix_args(*it);
		}
	}
}

static void fix_args(Process &process) {
	
	vector<string> args = process.get_arguments();
	vector<string> new_args;

	// for all arguments
	for (const auto& arg : args) {
        glob_t globResults;

		// if exist wildcard change
        if(glob(arg.c_str(), GLOB_TILDE, nullptr, &globResults) == 0) {
			
			// for every new chang
			for (size_t i = 0; i < globResults.gl_pathc; i++) {
			
				// insert it to new arguments array
				string str(globResults.gl_pathv[i]);
				new_args.push_back(str);
			}
			globfree(&globResults);
		} else {

			// if dosn't exist change, insert argument to array
			new_args.push_back(arg);
		}
	}

	// change all arguments with new one
    process.change_all_arguments(new_args);
}