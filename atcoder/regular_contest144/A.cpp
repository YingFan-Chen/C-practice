#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){ 
    int n;
    cin >> n;
    int maximum = n << 1;
    int a = n % 4, b = n / 4;
    cout << maximum << endl;
    if(a != 0) cout << a;
    for(int i = 0; i < b; i ++) cout << 4;
}