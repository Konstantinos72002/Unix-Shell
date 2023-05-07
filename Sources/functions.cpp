#include "headers.h"


// split words at symbol c 
bool splitOnSymbol(vector<string> &words, int i, char c) {
    if (words[i].size() < 2) return false;

    int pos;
    if ((pos = words[i].find(c)) != string::npos) {
        if (pos == 0) {
            
            words.insert(words.begin() + i + 1, words[i].substr(1, words[i].size() - 1));
            words[i] = words[i].substr(0, 1);
        } else {
            words.insert(words.begin() + i + 1, string{c});
            string after = words[i].substr(pos + 1, words[i].size() - pos - 1);
            if (!after.empty()) {
                words.insert(words.begin() + i + 2, after);
            }
            words[i] = words[i].substr(0, pos);
        }
        return true;
    } else return false;
}

vector<string> string_line_to_vector(string &line) {

    vector<string> ret;
    int pos = 0;
    int space;
    
    // split at spaces
    while ((space = line.find(' ', pos)) != string::npos) {
        string word = line.substr(pos, space - pos);
        if (!word.empty()) {
            ret.push_back(word);
        }
        pos = space + 1;
    }
    string lastWord = line.substr(pos, line.size() - pos);
    if (!lastWord.empty()) {
        ret.push_back(lastWord);
    }

    // split at special characters
    for (int i = 0; i < ret.size(); ++i) {
        for (auto c : {'&', '<', '>', '|', ';','"'}) {
            if (splitOnSymbol(ret, i, c)) {
                --i;
                break;
            }
        }
    }
    return ret;
}

char** strlist(vector<string>& strings) {
    
    char** charArray = new char*[strings.size() + 1];

    for (size_t i = 0; i < strings.size(); i++) {
        charArray[i] = new char[strings[i].size() + 1];
        std::strcpy(charArray[i], strings[i].c_str());
    }

    charArray[strings.size()] = NULL;

    return charArray;
}

char* str_to_chars(string &input) {
    
    char* result = new char[input.size() + 1];
    strcpy(result, input.c_str());
    return result;
}

vector<string> concatenate(vector<string> &line) {
    
    vector<string> return_vector;
    
    for(vector<string>::iterator it = line.begin(); it != line.end(); ++it) {
        
        string current = *it;
        if(it == line.end()-1) {
            return_vector.push_back(current);
            break;
        }
        
        string next = *(it+1);

        if(current == next && current == ">") {
            return_vector.push_back(">>");
            it++;
        } else {
            return_vector.push_back(current);
        }

    } 
    return return_vector;
}

vector<vector<string>> find_processes(vector<string> &lines) {
    vector<vector<string>> return_vector;
    
    for(vector<string>::iterator it = lines.begin(); it != lines.end() ; it++) {
    vector<string> line;
    
        while(*it != ";") {
            line.push_back(*it);
            it++;
            if(it == lines.end()) break;
        }
        
        return_vector.push_back(line);
        int size = line.size();
        for(int i = 0 ; i < size ; i++) line.pop_back();
        if (it == lines.end()) break;
    }
    
    return return_vector;
}