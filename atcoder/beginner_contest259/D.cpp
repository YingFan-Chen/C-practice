#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

class disjoint_set{
        std::vector<ll> v;
    public : 
        disjoint_set(ll n){
            v.assign(n, -1);
        }
        ll find(ll x){
            if(v[x] < 0) return x;
            else{
                ll root = find(v[x]);
                v[x] = root;
                return root;
            }
        }
        void merge(ll x, ll y){
            ll root1 = find(x), root2 = find(y);
            if(root1 != root2){
                if(v[root1] < v[root2]){
                    v[root1] += v[root2];
                    v[root2] = root1;
                }else{
                    v[root2] += v[root1];
                    v[root1] = root2;
                }
            }
            return ;
        }
        /* merge method will merge according to size of two sets, and deterministic_merge method will merge set y to set x. */
        void deterministic_merge(ll x, ll y){
            ll root1 = find(x), root2 = find(y);
            if(root1 != root2){
                v[root1] += v[root2];
                v[root2] = root1;
            }
            return ;
        }
        ll size(ll x){
            return - v[find(x)];
        }
};

int main(){
    int n;
    cin >> n;
    ll sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    vector<vector<ll>> circle;
    disjoint_set ds(n);
    
    int a = -1, b = -1;
    for(int i = 0; i < n; i ++){
        ll x, y, r;
        cin >> x >> y >> r;
        circle.push_back({x, y, r});
        ll tmp = (x - sx) * (x - sx) + (y - sy) * (y - sy);
        if(r * r == tmp) a = i;
        tmp = (x - tx) * (x - tx) + (y - ty) * (y - ty);
        if(r * r == tmp) b = i; 
    }

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(i != j){
                ll x1 = circle[i][0], y1 = circle[i][1], r1 = circle[i][2];
                ll x2 = circle[j][0], y2 = circle[j][1], r2 = circle[j][2];
                
                if(r1 < r2){
                    swap(x1, x2);
                    swap(y1, y2);
                    swap(r1, r2);
                }
                if(x2 + r2 < x1 + r1 and x2 - r2 > x1 - r1 and y2 + r2 < y1 + r1 and y2 - r2 > y1 - r1) continue;
                else{
                    ll tmp = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); 
                    if(tmp <= (r1 + r2) * (r1 + r2)) ds.merge(i, j);
                }

            }
        }
    }


    if(a >= 0 and b >= 0 and ds.find(a) == ds.find(b)) cout << "Yes" << endl;
    else cout << "No" << endl;

}