#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, m, x, t, d;
    cin >> n >> m >> x >> t >> d;
    int start = t - x * d;
    if(m >= x) cout << t << endl;
    else cout << start + m * d << endl;
}