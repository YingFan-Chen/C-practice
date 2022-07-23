#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
    if(x1 > y1){
        swap(x1, y1);
        swap(x2, y2);
    }
    if(x2 < y1) cout << 0 << endl;
    else{
        if(x2 <= y2) cout << x2 - y1 << endl;
        else  cout << y2 - y1 << endl;
    }
}