#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> B(n + 1, vector<ll> (m + 1, 0));
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++) cin >> B[i][j];
    }
    int starti = (B[1][1] - 1) / 7 + 1, startj = B[1][1] % 7;
    if(startj == 0) startj = 7;
    bool res = true;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            ll x = starti + i, y = startj + j;
            if(x >= 1 and x <= INT_MAX and y >= 1 and y <= 7){
                ll tmp = (x - 1) * 7 + y;
                if(B[i + 1][j + 1] != tmp) res = false;
            }else res = false; 
        }
    }
    if(res) cout << "Yes" << endl;
    else cout << "No" << endl;
}