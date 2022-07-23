#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    string s, t;
    cin >> s >> t;
    int k;
    cin >> k;
    unordered_map<char, vector<string>> um;
    for(int i = 0; i < k; i ++){
        char c;
        string tmp;
        cin >> c >> tmp;
        um[c].push_back(tmp);
    } 

    vector<int, int> dp
}