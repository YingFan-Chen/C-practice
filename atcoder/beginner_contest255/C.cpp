#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    ll x, a, d, n;
    cin >> x >> a >> d >> n;
    ll tmp = a + (n - 1) * d;
    ll base = min(tmp, a), top = max(tmp, a);
    if(d == 0) cout << abs(x - base);
    else{
        if(x > top) cout << x - top;
        else if(x < base) cout << base - x;
        else{
            d = abs(d);
            ll tmp = (x - base) % d;
            cout << min(tmp, d - tmp);
        }
    }
}