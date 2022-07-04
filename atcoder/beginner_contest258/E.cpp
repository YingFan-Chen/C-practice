#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;

ll f(vector<ll> &sum, ll i, ll x, ll n){
    ll l = i, r = i + n, res = 0;
    res = n * (x / sum[n - 1]);
    x %= sum[n - 1];
    if(x == 0) return res;
    while(l + 1 < r){
        ll mid = (l + r) >> 1;
        ll section;
        if(i == -1) section = sum[mid];
        else section = sum[mid] - sum[i];
        if(section >= x) r = mid;
        else l = mid;
    }
    res += r - i;
    return res; 
}

int main(){
    ll n, q, x;
    cin >> n >> q >> x;
    vector<ll> W(n, 0);
    for(int i = 0; i < n; i ++) cin >> W[i];
    vector<ll> sum(n << 1, 0);
    sum[0] = W[0];
    for(int i = 1; i < n << 1; i ++) sum[i] = sum[i - 1] + W[i % n];

    vector<ll> boxes;
    unordered_map<ll, ll> um;
    ll i = 0;
    while(um.find(i) == um.end()){
        um[i] = boxes.size();
        ll tmp = f(sum, i - 1, x, n);
        boxes.push_back(tmp);
        i += tmp;
        i %= n;
    }
    ll start = um[i], mod = boxes.size() - start;
    for(int j = 0; j < q; j ++){
        ll tmp;
        cin >> tmp;
        tmp --;
        if(tmp >= start) tmp = start + (tmp - start) % mod;
        cout << boxes[tmp] << endl;
    }
}