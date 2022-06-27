#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n;
    vector<int> tmp(4);
    vector<vector<int>> v(n, tmp);
    for(int i = 0; i < n; i ++){
        cin >> v[i][0] >> v[i][1] >> v[i][2] >> v[i][3];
    }
    
}