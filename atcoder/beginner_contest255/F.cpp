#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;
int func(vector<pair<int, int>> &v, vector<int> &pre, unordered_map<int, int> &um, int l, int r, int &x){
    if(l > r) return 0;
    else{
        int tmp = pre[x];
        x ++;
        if(um[tmp] > r or um[tmp] < l) return -1;
        int a = func(v, pre, um, l, um[tmp] - 1, x);
        int b = func(v, pre, um, um[tmp] + 1, r, x);
        v[tmp] = {a, b};
        if(a == -1 or b == -1) return -1;
        return tmp;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> pre(n);
    unordered_map<int, int> um;
    for(int i = 0; i < n; i++){
        cin >> pre[i];
    }
    for(int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        um[tmp] = i; 
    }
    if(pre[0] != 1) cout << -1;
    else{
        vector<pair<int, int>> v(n + 1);
        int x = 0;
        func(v, pre, um, 0, n - 1, x);
        if(v[1].first == -1 or v[1].second == -1) cout << -1 << "\n";
        else{ 
            for(int i = 1; i <= n; i++) cout << v[i].first << " " << v[i].second << "\n"; 
        }
    }

    /*debug(pre);
    debug(um);*/
}