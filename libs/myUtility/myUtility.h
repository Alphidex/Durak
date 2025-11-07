#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

namespace myUtility {
template <typename T>  
void print(T s) {cout << s << endl;}
string input(string s);
bool is_integer(string s);
vector<string> split_space(string s);
}