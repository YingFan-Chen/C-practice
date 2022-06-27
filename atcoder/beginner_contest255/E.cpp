#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    ll n , m ;
    cin >> n >> m;
    vector<ll> s(n - 1, 0);
    vector<ll> x;
    for(int i = 0; i < n - 1; i ++) cin >> s[i];
    for(int i = 0; i < m; i ++){
        ll tmp ;
        cin >> tmp;
        x.push_back(tmp);
    }
    ll res = 0;
    vector<ll> A(n, 0);
    unordered_map<ll, ll> um1, um2;
    um1[0] ++;
    for(int i = 1; i < n; i++){
        A[i] = s[i - 1] - A[i - 1];
        if(i % 2) um1[A[i]] ++;
        else um2[A[i]] ++;
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            ll count = 0, offset = x[j] - A[i];
            if(i % 2){
                for(int k = 0; k < m; k ++){
                    if(um1.find(x[k] - offset) != um1.end())  count += um1[x[k] - offset];
                    if(um2.find(x[k] + offset) != um2.end())  count += um2[x[k] + offset];
                }
            }else{
                for(int k = 0; k < m; k ++){
                    if(um1.find(x[k] + offset) != um1.end())  count += um1[x[k] + offset];
                    if(um2.find(x[k] - offset) != um2.end())  count += um2[x[k] - offset];
                }
            }
            res = max(res, count);
        }
    }
    cout << res ;
}