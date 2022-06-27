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
    vector<vector<int>> v;
    for(int i = 0; i < n; i ++){
        vector<int> tmp;
        for(int j = 0; j < i + 1; j ++){
            if(j == 0 || j == i) tmp.push_back(1);
            else tmp.push_back(v[i - 1][j - 1] + v[i - 1][j]); 
        }
    
        v.push_back(tmp);
    }
    for(int i = 0; i < v.size(); i++){
        for(int j : v[i]) cout << j << " ";
        cout << "\n";
    }
}