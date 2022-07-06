#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
//#include "..\..\lib\debug"
#endif
using namespace std;


int main(){
    int t;
    for(int i = 0; i < t; i++){
        ll b, k, sx, sy, gx, gy;
        cin >> b >> k >> sx >> sy >> gx >> gy;
        vector<pair<ll, ll>> s, g;

        double tmp = sx / (double) b;
        s.push_back({floor(tmp), sy});
        s.push_back({ceil(tmp), sy});
        tmp = gx / (double) b;
        g.push_back({floor(tmp), gy});
        g.push_back({ceil(tmp), gy});
        tmp = sy / (double) b;
        s.push_back({sx, floor(tmp)});
        s.push_back({sx, ceil(tmp)});
        tmp = gy / (double) b;
        g.push_back({gx, floor(tmp)});
        g.push_back({gx, ceil(tmp)});
        
        // 0 good point
        ll res = (abs(gx - sx) + abs(gy - sy)) * k;
        
        //2 good point
        vector<vector<ll>> dist(4, vector<ll> (4, ll_max));
        for(int i = 0; i < 4; i ++){
            for(int j = 0; j < 4; j ++){
                auto [x1, y1] = s[i];
                auto [x2, y2] = g[j];
                if(x1 % b == 0 and x2 % b == 0 and y1 / b == y2 / b){
                    ll mini;
                    mini = abs(y2 - y1) + abs(x2 - x1) * k;
                    tmp = y1 / (double) b;
                    mini = min(mini, abs((ll) floor(tmp) - y1) + abs((ll) floor(tmp) - y2) + abs(x2 - x1));
                    mini = min(mini, abs((ll) ceil(tmp) - y1) + abs((ll) ceil(tmp) - y2) + abs(x2 - x1));
                    mini += (abs(sx - x1) + abs(sy - y1) + abs(gx - x2) + abs(gy - y2)) * k;
                    dist[i][j] = mini;
                }
                else if(y1 % b == 0 and y2 % b == 0 and x1 / b == x2 / b){
                    ll mini;
                    mini = abs(y2 - y1) * k + abs(x2 - x1);
                    tmp = x1 / (double) b;
                    mini = min(mini, abs((ll) floor(tmp) - x1) + abs((ll) floor(tmp) - x2) + abs(y2 - y1));
                    mini = min(mini, abs((ll) ceil(tmp) - x1) + abs((ll) ceil(tmp) - x2) + abs(y2 - y1));
                    mini += (abs(sx - x1) + abs(sy - y1) + abs(gx - x2) + abs(gy - y2)) * k;
                    dist[i][j] = mini;
                }else{
                    dist[i][j] = abs(x2 - x1) + abs(y2 - y1) + (abs(sx - x1) + abs(sy - y1) + abs(gx - x1) + abs(gy - y1)) * k;
                }
            }
        }
        for(auto &i : dist){
            for(auto &j : i) res = min(res, j);
        }
        cout << res << endl;
    }
}