#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;
const ll mod = 998244353; 

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> dp(n + 1, vector<ll> (m + 1, 0));
    for(int i = 1; i <= m; i ++) dp[1][i] = dp[1][i - 1] + 1;
    for(int i = 2; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            dp[i][j] = dp[i][j - 1];
            if(k == 0) dp[i][j] += dp[i - 1][m];
            else{
                if(j - k > 0) dp[i][j] += dp[i - 1][j - k];
                if(j + k <= m) dp[i][j] += dp[i - 1][m] - dp[i - 1][j + k - 1];  
            }
            dp[i][j] %= mod;
        }
    }
    cout << (dp[n][m] + mod) % mod << endl; 
}