#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, c;
    cin >> n >> c;
    vector<vector<pair<int, int>>> dp(n + 1, vector<pair<int, int>> (32, pair<int, int> (0, 1)));
    for(int i = 1; i <= n; i ++){
        int t, a;
        cin >> t >> a;
        if(t == 1){
            for(int j = 0; j < 32; j ++){
                if(a & 1){
                    dp[i][j].first = dp[i - 1][j].first & 1;
                    dp[i][j].second = dp[i - 1][j].second & 1;
                }else{
                    dp[i][j].first = dp[i - 1][j].first & 0;
                    dp[i][j].second = dp[i - 1][j].second & 0;
                }
                a >>= 1;
            }
        }else if(t == 2){
            for(int j = 0; j < 32; j ++){
                if(a & 1){
                    dp[i][j].first = dp[i - 1][j].first | 1;
                    dp[i][j].second = dp[i - 1][j].second | 1;
                }else{
                    dp[i][j].first = dp[i - 1][j].first | 0;
                    dp[i][j].second = dp[i - 1][j].second | 0;
                }
                a >>= 1;
            }
        }else{
            for(int j = 0; j < 32; j ++){
                if(a & 1){
                    dp[i][j].first = dp[i - 1][j].first ^ 1;
                    dp[i][j].second = dp[i - 1][j].second ^ 1;
                }else{
                    dp[i][j].first = dp[i - 1][j].first ^ 0;
                    dp[i][j].second = dp[i - 1][j].second ^ 0;
                }
                a >>= 1;
            }
        }
    }

    for(int i = 1; i <= n; i ++){
        int tmp = 0;
        for(int j = 0; j < 32; j ++){
            if(c & 1){
                tmp += dp[i][j].second << j;
            }else{
                tmp += dp[i][j].first << j;
            }
            c >>= 1;
        }
        c = tmp;
        cout << c << endl;
    }

}