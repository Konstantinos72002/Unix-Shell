#include "headers.h"

void wildcards(Process &process,vector<Process> &pipes) {
	if(pipes.size() == 0) {
		fix_args(process);
	} else {
		fix_args(process);
		for(vector<Process>::iterator it = pipes.begin(); it!= pipes.end(); it++) {
			fix_args(*it);
		}
	}
}

void fix_args(Process &process) {
	
	vector<string> args = process.get_arguments();
	vector<string> new_args;

	 for (const auto& arg : args) {
        glob_t globResults;
        if(glob(arg.c_str(), GLOB_TILDE, nullptr, &globResults) == 0) {
			for (size_t i = 0; i < globResults.gl_pathc; i++) {
				string str(globResults.gl_pathv[i]);
				new_args.push_back(str);
			}
			globfree(&globResults);
		} else {
			new_args.push_back(arg);
		}
	}
    process.change_all_arguments(new_args);
}


// vector<vector<string>> wildcards(vector<string> &line) {
// 	vector<vector<string>> results;
// 	glob_t glob_result;

//     for (auto pattern : line) {
// 		vector<string> matches;
//         if (glob(pattern.c_str(), GLOB_NOSORT, NULL, &glob_result) == 0) {
//             for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
//                 matches.push_back(string(glob_result.gl_pathv[i]));
//             }
            
//         } else {
// 			matches.push_back(pattern);
// 		}
// 		results.push_back(matches);
//     }

//     globfree(&glob_result);
//     return results;
// }