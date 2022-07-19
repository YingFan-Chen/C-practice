#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;
constexpr int kN = 1000000;

int main(){
    int s, t, m;
    cin >> s >> t >> m;
    vector<vector<int>> edge(s + 1, vector<int> ());
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
    }
    
    vector<vector<int>> dp(t + 1, vector<int> (t + 1));
    for(int i = 1; i <= s; i ++){
        for(auto j : edge[i]){
            for(auto k : edge[i]){
                if(j != k){
                    if(dp[j - s][k - s] == 0) dp[j - s][k - s] = i;
                    else{
                        cout << j << " " << k << " " << i << " " << dp[j -s][k - s];
                        return 0;
                    }
                }
            }
        }
    }

    cout << -1;
}