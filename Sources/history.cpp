#include"headers.h"

void add_to_history(list<string> &previous,string &line) {
	
	if(previous.size() == 20) {
		previous.pop_back();
	}
	previous.push_front(line);
	return;
}