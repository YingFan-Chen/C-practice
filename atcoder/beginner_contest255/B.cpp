#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    unordered_set<int> noLight;
    for(int i = 1; i <= n; i++) noLight.insert(i);
    vector<ll> tmp(n - k + 1, 0);
    vector<vector<ll>> dist(k + 1, tmp);
    for(int i = 1; i <= k; i++){
        cin >> dist[i][0];
        noLight.erase(dist[i][0]);
    }
    vector<pair<int, int>> pos(n + 1, {0,0});
    for(int i = 1; i <= n; i++){
        int x, y;
        cin >> x >> y;
        pos[i] = {x, y};
    }
    int i = 1;
    for(auto &j : noLight){
        dist[0][i] = j;
        i ++;
    }
    for(i = 1; i <= k; i ++){
        auto [x1, y1] = pos[dist[i][0]];
        for(int j = 1; j <= n - k; j ++){
            auto [x2, y2] = pos[dist[0][j]];
            dist[i][j] = pow((x1 - x2), 2) + pow((y1 - y2), 2);
        }
    }
    
    ll l = 0, r = 1E11;
    unordered_set<int> s;
    while(l + 1 < r){
        s = noLight;
        ll mid = (l + r) >> 1;
        for(i = 1; i <= k; i ++){
            for(int j = 1; j <= n - k; j ++){
                if(mid >= dist[i][j]) s.erase(dist[0][j]);
            }
        }
        if(s.empty()) r = mid;
        else l = mid;
    }

    double res = pow((double) r, 0.5);
    printf("%.6f", res);
}