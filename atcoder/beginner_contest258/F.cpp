#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;

ll up(ll x, ll b){
    if(x % b == 0) return x;
    if(x > 0) return x / b * b + b;
    else return x / b * b;
}

ll down(ll x, ll b){
    if(x % b == 0) return x;
    if(x > 0) return x / b * b;
    else return x / b * b - b;
}

int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        ll b, k, sx, sy, gx, gy;
        cin >> b >> k >> sx >> sy >> gx >> gy;
        vector<pair<ll, ll>> s, g;

        s.push_back({down(sx, b), sy});
        s.push_back({up(sx, b), sy});
        g.push_back({down(gx, b), gy});
        g.push_back({up(gx, b), gy});
        s.push_back({sx, down(sy, b)});
        s.push_back({sx, up(sy, b)});
        g.push_back({gx, down(gy, b)});
        g.push_back({gx, up(gy, b)});
        
        // 0 good point
        ll res = (abs(gx - sx) + abs(gy - sy)) * k;
        ll dist;
        
        //2 good point
        for(int i = 0; i < 4; i ++){
            for(int j = 0; j < 4; j ++){
                auto [x1, y1] = s[i];
                auto [x2, y2] = g[j];
                if(x1 % b == 0 and x2 % b == 0 and down(y2, b) == down(y1, b)){
                    dist = abs(y2 - y1) + abs(x2 - x1) * k;
                    dist = min(dist, abs(down(y1, b) - y1) + abs(down(y1, b) - y2) + abs(x2 - x1));
                    dist = min(dist, abs(up(y1, b) - y1) + abs(up(y1, b) - y2) + abs(x2 - x1));
                    dist += (abs(sx - x1) + abs(sy - y1) + abs(gx - x2) + abs(gy - y2)) * k;
                    res = min(res, dist);
                }
                else if(y1 % b == 0 and y2 % b == 0 and  down(x2, b) == down(x1, b)){
                    dist = abs(y2 - y1) * k + abs(x2 - x1);
                    dist = min(dist, abs(down(x1, b) - x1) + abs(down(x1, b) - x2) + abs(y2 - y1));
                    dist = min(dist, abs(up(x1, b) - x1) + abs(up(x1, b) - x2) + abs(y2 - y1));
                    dist += (abs(sx - x1) + abs(sy - y1) + abs(gx - x2) + abs(gy - y2)) * k;
                    res = min(res, dist);
                }else{
                    dist = abs(x2 - x1) + abs(y2 - y1) + (abs(sx - x1) + abs(sy - y1) + abs(gx - x2) + abs(gy - y2)) * k;
                    res = min(res, dist);
                }
            }
        }
        cout << res << endl;
    }
}