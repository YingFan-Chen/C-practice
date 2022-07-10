#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;

int main(){
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    int pi[n];
    memset(pi, 0, sizeof(pi));
    for(int i = 1; i < n; i ++){
        int j = pi[i - 1];
        while(j){
            if(s[i] == s[j]) break;
            else j = pi[j - 1];
        }
        if(s[i] == s[j])  pi[i] = j + 1;
    }


    int dp[m];
    memset(dp, 0, sizeof(dp));
    int base = 0, cur = 0;
    while(cur < m){
        if(cur - base == n or t[cur] != s[cur - base]){
            if(cur - base == 0){
                cout << -1 << endl;
                return 0;
            }
            base = cur - pi[cur - base - 1];
        }else{
            if(base == 0) dp[cur] = 1;
            else dp[cur] = dp[base - 1] + 1;
            cur ++;
        }
    }
    cout << dp[m - 1] << endl;
}