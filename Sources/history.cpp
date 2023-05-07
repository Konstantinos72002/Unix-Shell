#include"headers.h"

void add_to_history(list<string> &previous,string &line) {
	// if history is full pop one element and then add the new one
	// else add the new one

	if(previous.size() == 20) {
		previous.pop_back();
	}
	previous.push_front(line);
	return;
}