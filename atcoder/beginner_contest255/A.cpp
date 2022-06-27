#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int r, c;
    cin >> r >> c;
    int v[2][2];
    cin >> v[0][0] >> v[0][1] >> v[1][0] >> v[1][1];
    cout << v[r - 1][c - 1];
}