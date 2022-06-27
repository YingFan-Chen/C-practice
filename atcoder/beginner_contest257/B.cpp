#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> A(k + 1);
    vector<int> L(q + 1);
    vector<int> N(n + 1);
    for(int i = 1; i <= k; i ++) cin >> A[i];
    for(int i = 1; i <= q; i ++) cin >> L[i];


    for(int i = 1; i <= k; i ++){
        N[A[i]] = 1;
    }
    for(int i = 1; i <= q; i++){
        int count = 0, j;
        for(j = 1; j <= n; j++){
            if(N[j]) count ++;
            if(count == L[i]) break;
        }
        if(j != n and N[j + 1] == 0){
            N[j] = 0;
            N[j + 1] = 1;
        }
    }
    for(int i = 1; i <= n; i ++){
        if(N[i]) cout << i << " ";
    }
}