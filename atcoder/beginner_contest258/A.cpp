#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int k;
    cin >> k;
    if(k >= 60){
        k %= 60;
        if(k < 10){
            cout << "22:0" << k << endl;
        }else{
            cout << "22:" << k << endl;
        }
    } else{
        if(k < 10){
            cout << "21:0" << k << endl;
        }else{
            cout << "21:" << k << endl;
        }
    }
}