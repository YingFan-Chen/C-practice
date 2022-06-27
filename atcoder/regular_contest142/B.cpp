#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<vector<int>> res (n, vector<int> (n, 0));
    int val = 1;
    for(int i = 0; i < n; i += 2){
        for(int j = 0; j < n; j ++){
            res[i][j] = val;
            val ++;
        }
    }
    for(int i = 1; i < n; i += 2){
        for(int j = 0; j < n; j ++){
            res[i][j] = val;
            val ++;
        }
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++) cout << res[i][j] << " ";
        cout << endl;    
    }
}