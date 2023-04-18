#include "headers.h"

bool splitOnSymbol(std::vector<std::string> &words, int i, char c)
{
    if (words[i].size() < 2)
    {
        return false;
    }
    int pos;
    if ((pos = words[i].find(c)) != std::string::npos)
    {
        if (pos == 0)
        {
            //starts with symbol
            words.insert(words.begin() + i + 1, words[i].substr(1, words[i].size() - 1));
            words[i] = words[i].substr(0, 1);
        }
        else
        {
            //symbol in middle or end
            words.insert(words.begin() + i + 1, std::string{c});
            std::string after = words[i].substr(pos + 1, words[i].size() - pos - 1);
            if (!after.empty())
            {
                words.insert(words.begin() + i + 2, after);
            }
            words[i] = words[i].substr(0, pos);
        }
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> tokenize(const std::string &s)
{

    std::vector<std::string> ret;
    int pos = 0;
    int space;
    //split on spaces
    while ((space = s.find(' ', pos)) != std::string::npos)
    {
        std::string word = s.substr(pos, space - pos);
        if (!word.empty())
        {
            ret.push_back(word);
        }
        pos = space + 1;
    }

    std::string lastWord = s.substr(pos, s.size() - pos);
    if (!lastWord.empty())
    {
        ret.push_back(lastWord);
    }

    for (int i = 0; i < ret.size(); ++i)
    {
        for (auto c : {'&', '<', '>', '|'})
        {
            if (splitOnSymbol(ret, i, c))
            {
                --i;
                break;
            }
        }
    }

    return ret;
}

char ** strlist(vector<string> &input) {
    char** result = new char*[input.size()];
    result[input.size()] = nullptr;
    for (int i=0; i<input.size(); i++) {
        char *temp = new char[input[i].size()];
        strcpy(temp, input[i].c_str());
        result[i] = temp;
    }
    return result;
}

char* str_to_chars(string &input) {
    char* result = new char[input.size() + 1];
    strcpy(result, input.c_str());
    return result;
}