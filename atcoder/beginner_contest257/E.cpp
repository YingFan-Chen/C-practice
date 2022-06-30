#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    ll n;
    cin >> n;
    vector<int> c(10);
    vector<pair<int, int>> C(10);
    for(int i = 1; i < 10; i++){
        cin >> c[i];
        C[i] = {c[i], i};
    }
    sort(C.begin(), C.end());
    int minCost = C[1].first, maxDigit = n / minCost;
    for(int i = maxDigit; i > 0; i --){
        int d;
        for(int j = 1; j <= 9; j ++){
            if(n - c[j] >= (i - 1) * minCost) d = j;
        }
        cout << d;
        n -= c[d];
    }
    cout << endl;
}