#include <bits/stdc++.h>
#include <algorithm>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

void pull(int index, vector<int> &v){
    v[index] = __gcd(v[index << 1], v[index << 1 | 1]);
    return ;
}
void build(int index, int l, int r, vector<int> &v, vector<int> &val){
    if(l == r) v[index] = val[l];
    else{
        int mid = (l + r) >> 1;
        build(index << 1, l, mid, v, val);
        build(index << 1 | 1, mid + 1, r, v, val);
        pull(index, v);
    }
    return ;
}
int query(int index, int l, int r, int targetl, int targetr, vector<int> &v){
    if(l >= targetl and r <= targetr) return v[index];
    else{
        int mid = (l + r) >> 1, a = 0, b = 0;
        if(mid >= targetl) a = query(index << 1, l, mid, targetl, targetr, v);
        if(mid < targetr) b = query(index << 1 | 1, mid + 1, r, targetl, targetr, v);
        if(a and b) return __gcd(a, b);
        else if(a) return a;
        else return b; 
    }
}

int main(){
    int n, q ;
    cin >> n >> q;
    vector<int> A(n + 1), B(n + 1), subA(n), subB(n);
    for(int i = 1; i <= n; i ++) cin >> A[i];
    for(int i = 1; i <= n; i ++) cin >> B[i];
    for(int i = 1; i < n; i ++) subA[i] = abs(A[i + 1] - A[i]), subB[i] = abs(B[i + 1] - B[i]);
    vector<int> gcdA(n << 2), gcdB(n << 2);
    if(n > 1){
        build(1, 1, n - 1, gcdA, subA);
        build(1, 1, n - 1, gcdB, subB);
    }
    for(int i = 0; i < q; i ++){
        int h1, h2, w1, w2;
        cin >> h1 >> h2 >> w1 >> w2;
        int a = 0, b = 0, res;
        if(h1 != h2) a = query(1, 1, n - 1, h1, h2 - 1, gcdA);
        if(w1 != w2) b = query(1, 1, n - 1, w1, w2 - 1, gcdB);
        res = A[h1] + B[w1];
        if(a and b) res = __gcd(res, __gcd(a, b));
        else if(a) res = __gcd(res, a);
        else res = __gcd(res, b);
        cout << res << endl;
    }
}