#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, a, b;
    cin >> n >> a >> b;
    vector<ll> A(n);
    for(int i = 0; i < n; i ++) cin >> A[i];
    map<ll, ll> m;
    ll sum = 0;
    for(auto i : A){
        m[i] ++;
        sum += i;
    }

    ll maximum = 0;
    while(true){
        
    }
}