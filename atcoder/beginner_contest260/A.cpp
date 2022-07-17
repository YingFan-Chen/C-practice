#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    string s;
    cin >> s;
    map<char, int> m;
    for(int i = 0; i < 3; i ++){
        m[s[i]] ++;
    }

    bool flag = false;
    for(auto i : m){
        if(i.second == 1){
            cout << i.first << endl;
            flag = true;
            break;
        } 
    }
    if(flag == false) cout << -1 << endl;
}