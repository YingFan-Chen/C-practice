#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, x;
    cin >> n >> x;
    int tmp = (x - 1) / n;
    cout << (char) ('A' + tmp) << endl;
}