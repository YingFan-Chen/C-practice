#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    ll a, b, c;
    cin >> a >> b >> c;
    if(a > b) swap(a, b);
    if(a > c) swap(a, c);
    if(b > c) swap(b, c);
    ll sub1 = b - a, sub2 = c - b;
    vector<ll> v;
    v = {sub2, sub1 + sub2, sub1 + 2 * sub2};
    if(v[0] > a or v[1] > b or v[2] > c) cout << -1 << endl;
    else{
        ll total = v[0] + v[1] + v[2];
        ll res = total / 2 + a - v[0];
        cout << res << endl;
    }
}