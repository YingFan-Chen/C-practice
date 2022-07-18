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
    vector<bitset<kN>> edge(t + 1, bitset<kN> ());
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        edge[v - s][u] = 1;
    }
    for(int i = 1; i < t; i ++){
        for(int j = i + 1; j <= t; j ++){
            bitset<kN> tmp = edge[i] & edge[j];
            if(tmp.count() >= 2){
                cout << s + i << " " << s + j << " ";
                int count = 2;
                for(int k = 1; k <= kN, count < 4; k ++){
                    if(tmp[k] == 1){
                        cout << k << " ";
                        count ++;
                    }
                }
                return 0;
            }
        }
    }
    cout << -1;
}