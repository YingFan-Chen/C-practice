#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;
 
int main(){
    ll n, k;
    cin >> n >> k;
    ll a = k, b = 0, tmp = k;
    if(k % 10 == 0){
        cout << 0;
    }else{
        while(tmp) {
            b = b * 10 + tmp % 10;
            tmp /= 10;
        }

        ll res = 0;
        if(b < a){
            cout << 0;
        }else if(b == a){
            while(b <= n){
                res ++;
                b *= 10;
            }
            cout << res;
        }else{
            while(b <= n){
                res ++;
                b *= 10;
            }
            while(a <= n){
                res ++;
                a *= 10;
            }
            cout << res;
        }
    }  
}