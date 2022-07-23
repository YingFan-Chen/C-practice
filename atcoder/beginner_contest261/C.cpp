#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    map<string, int> m;
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++){
        string tmp;
        cin >> tmp;
        if(m.find(tmp) == m.end()){
            cout << tmp << endl;
            m[tmp] ++;
        }else{
            cout << tmp << "(" << m[tmp] << ")" << endl;
            m[tmp] ++;
        }
    }
}