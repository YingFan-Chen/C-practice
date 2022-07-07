#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;

const ll mod = 1E9 + 7, base = 7777;


int main(){
    string s, t;
    cin >> s >> t;

    vector<ll> poly(500000, 0);
    poly[0] = 1;
    for(int i = 1; i < 500000; i ++) poly[i] = (poly[i - 1] * base) % mod;
    
    ll sum = 0;
    unordered_set<ll> prefix;
    for(int i = 0; i < s.size(); i ++){
        sum = (sum + s[i] * poly[i]) % mod;
        prefix.insert(sum);
    }

    sum = 0;
    int index = t.size() - 1, pre = - 1;
    ll count = 0;
    
    while(){
        sum = (sum * base + t[index]) % mod;
        if(prefix.find(sum) == )
    }

}