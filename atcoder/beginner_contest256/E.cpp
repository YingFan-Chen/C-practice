#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

class disjoint_set{
        vector<ll> v;
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
                v[root1] += v[root2];
                v[root2] = root1;
            }
            return ;
        }
};

int main(){
    int n;
    cin >> n;
    disjoint_set ds(n + 1);
    vector<int> x(n + 1), c(n + 1);
    for(int i = 1; i <= n; i ++){
        cin >> x[i];
        ds.merge(x[i], i);
    }
    for(int i = 1; i <= n; i ++) cin >> c[i];
    ll res = 0;
    for(int i = 1; i <= n; i++){
        if(ds.find(i) == i){
            int weight = c[i], cur = x[i];
            while(cur != i){
                weight = min(weight, c[cur]);
                cur = x[cur];
            }
            res += weight;
        }
    }
    cout << res;
}