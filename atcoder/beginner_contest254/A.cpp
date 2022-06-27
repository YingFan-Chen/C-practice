#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n ;
    cin >> n;
    n = n % 100;
    if(n < 10){
        cout << "0" << n << "\n";
    }else cout << n << "\n";
}