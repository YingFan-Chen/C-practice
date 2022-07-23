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
    vector<ll> X(n + 1);
    for(int i = 1; i <= n; i ++) cin >> X[i];
    unordered_map<ll, ll> um;
    for(int i = 0; i < m; i ++){
        ll c, y;
        cin >> c >> y;
        um[c] = y;
    }

    vector<vector<ll>> dp(n + 1, vector<ll> (n + 1));
    // dp[x][y] -> x : x times, y : count = y
    for(int i = 1; i <= n; i ++){
        for(int j = 0; j <= i; j ++){
            if(j == 0){
                ll tmp = 0;
                for(int k = 0; k < i; k ++){
                    tmp = max(tmp, dp[i - 1][k]);
                }
                dp[i][j] = tmp;
            }else{
                if(um.find(j) == um.end()){
                    dp[i][j] = dp[i - 1][j - 1] + X[i];
                }else{
                    dp[i][j] = dp[i - 1][j - 1] + X[i] + um[j];
                }
            }
        }
    }
    ll res = 0;
    for(int i = 0; i <= n; i ++){
        res = max(res, dp[n][i]);
    }

    cout << res << endl;
}