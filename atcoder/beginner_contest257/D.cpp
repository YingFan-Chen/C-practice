#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<pair<ll, ll>> point;
    vector<ll> power;
    for(int i = 0; i < n; i ++){
        ll a, b, c;
        cin >> a >> b >> c;
        point.push_back({a, b});
        power.push_back(c);
    }
    vector<vector<ll>> dist(n, vector<ll> (n, 0));
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(i != j){
                dist[i][j] = abs(point[i].first - point[j].first) + abs(point[i].second - point[j].second);
            }
        }
    }
    unordered_set<int> s;
    ll l = -1, r = 1E10;
    while(l + 1 < r){
        ll mid = (l + r) >> 1;
        for(int i = 0; i < n; i ++){
            s.clear();
            s.insert(i);
            int pre;
            while(s.size() < n){
                pre = s.size();
                for(auto & j : s){
                    for(int k = 0; k < n; k ++){
                        if(mid * power[j] >= dist[j][k]) s.insert(k);
                    }
                }
                if(s.size() == pre) break;
            }
            if(s.size() == n) break;
        }
        if(s.size() == n) r = mid;
        else l = mid;
    }
    cout << r << endl;
}