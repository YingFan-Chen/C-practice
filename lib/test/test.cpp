#pragma once
#include <bits/stdc++.h>
#include "../debug"
#include "../data_structure"
#include "../algorithm"
using namespace std;

int main(){
    string pattern;
    string text;
    getline(cin, pattern);
    pattern = pattern.substr(0, pattern.size() - 1);
    getline(cin, text);
    KMP kmp(pattern, text);
    vector<pair<int, int>> pos1 = kmp.query();
    vector<string> patterns = {pattern};
    AC_automaton ac(text, patterns);
    vector<pair<int, int>> pos2 = ac.query();
    if(pos2 == pos1) cout << "true" << endl;
    else cout << "fasle" << endl;
}