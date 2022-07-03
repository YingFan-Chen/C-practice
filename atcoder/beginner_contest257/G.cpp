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
    int n = s.size(), m = t.size();
    //build pi function
    int pi[n];
    pi[0] = 0;
    for(int i = 1; i < n; i ++){
        int j = pi[i - 1];
        while(j > 0){
            if(s[i] == s[j]){
                pi[i] = j + 1;
                break;
            }else j = pi[j - 1];
        }
    }
    //f
    ll count = 0;


    cout << count << endl;
}