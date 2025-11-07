#include "myUtility.h"

namespace myUtility {

string input(string s) {cout << s; string in; cin >> in; return in;}

bool is_integer(string s)
{
    auto it = s.begin();
    while(it != s.end() && isdigit(*it)) it++;
    return !s.empty() && it==s.end();
}

vector<string> split_space(string s)
{
    stringstream ss(s);
    vector<string> v;
    while (getline(ss, s, ' ')){
        v.push_back(s);
    }
    return v;
}
}