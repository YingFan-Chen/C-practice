#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    ll n;
    cin >> n;
    vector<int> C(10, 0);
    for(int i = 1; i < 10; i++) cin >> C[i];
    vector<string> dp(n + 1, "");
    for(int i = 1; i <= n; i ++){
        set<int> biggest;
        int max_size = 0;
        for(int j = 1; j < 10; j ++){
            int tmp = i - C[j];
            if(tmp >= 0) max_size = max(max_size, (int) dp[tmp].size());
        }
        for(int j = 1; j < 10; j ++){
            int tmp = i - C[j];
            if(tmp >= 0 and (int) dp[tmp].size() == max_size) biggest.insert(j);
        }
        int j;
        for(j = 0; j < max_size; j ++){
            char max_char = 0;
            //set<int> dup = biggest;
            for(auto &k : biggest){
                max_char =  max(max_char, dp[i - C[k]][j]);
            }
            for(auto &k : biggest){
                if(dp[i - C[k]][j] != max_char) biggest.erase(k); //***************
            }
            dp[i] += (char) max_char;
            if(biggest.size() == 1) break;
        }
        debug(biggest);
        if(biggest.size() == 1){
            int k = *biggest.begin();
            for(j = j + 1; j < max_size; j ++) dp[i] += dp[i - C[k]][j];
        }
        dp[i] += (char) (*biggest.rbegin() + '0');
    }
    cout << dp[n] << endl;
}