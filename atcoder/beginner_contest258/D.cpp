#include <bits/stdc++.h>
#include <limits.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    ll n , x;
    cin >> n >> x;
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i ++){
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }
    ll mini = ll_max;
    ll add = 0;
    for(int i = 0; i < n ; i ++){
        auto [a, b] = v[i];
        add += a + b;
        ll tmp = add;
        tmp += (x - i - 1) * b;
        if(tmp > 0) mini = min(mini, tmp);
    }
    cout << mini << endl;
}