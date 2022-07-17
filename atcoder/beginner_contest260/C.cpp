#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, x, y;
    cin >> n >> x >> y;
    ll red = 1, blue = 0;
    for(int i = 1; i < n; i ++){
        blue += red * x;
        red += blue;
        blue *= y;
    }

    cout << blue << endl;
}