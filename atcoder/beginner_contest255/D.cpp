#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> A(n + 1);
    for(int i = 1; i <= n; i++) cin >> A[i];
    sort(A.begin(), A.end());
    vector<ll> sum(n + 1);
    for(int i = 1; i <= n; i++){
        if(i == 1) sum[i] = A[i];
        else sum[i] = sum[i - 1] + A[i];
    }
    for(int i = 0; i < q; i++){
        ll x ; 
        cin >> x;
        int l = 0, r = n + 1;
        while(l + 1 < r){
            int mid = (l + r) >> 1;
            if(A[mid] <= x) l = mid;
            else r = mid;
            //debug(mid);
        }
        ll res = 0;
        res += l * x - sum[l];
        res += sum[n] - sum[l] - (n - l) * x;
        cout << res << "\n";
    }
}