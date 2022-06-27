#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

const ll m = 998244353; 

void pull(int index, vector<ll> &v){
    v[index] = (v[index << 1] + v[index << 1 | 1]) % m;   
    return ;
}

void push(int index, int l, int r, vector<ll> &v, vector<pair<ll, ll>> &flag){
    if(flag[index] != pair<ll, ll> {0, 0}){
        int mid = (l + r) >> 1;
        auto [a, b] = flag[index];
        v[index << 1] = (v[index << 1] + (2 * a + (mid - l) * b) * (mid - l + 1) / 2) % m;
        v[index << 1 | 1] = (v[index << 1 | 1] + (a + (mid - l + 1) * b + a + (r - l) * b) * (r - mid) / 2) % m;
        flag[index << 1].first = (flag[index << 1].first + a) % m;
        flag[index << 1].second = (flag[index << 1].second + b) % m;
        flag[index << 1 | 1].first = (flag[index << 1 | 1].first + a + (mid - l + 1) * b) % m;
        flag[index << 1 | 1].second = (flag[index << 1 | 1].second + b) % m;
        flag[index] = {0, 0};
    }
    return ;
}

void initialize(int index, int l, int r, vector<ll> &v, vector<ll> &tmp){
    if(l == r) v[index] = tmp[l];
    else{
        int mid = (l + r) >> 1; 
        initialize(index << 1, l, mid, v, tmp);
        initialize(index << 1 | 1, mid + 1, r, v, tmp);
        pull(index, v);
    }
    return ;
}

void adjust(int index, int l, int r, int targetl, int targetr, int start, ll plus, vector<ll> &v, vector<pair<ll, ll>> &flag){
    if(r < targetl or l > targetr) return ;
    else if(r <= targetr and l >= targetl){
        v[index] = (v[index] + (plus + (l - start) * plus + plus + (r - start) * plus) * (r - l + 1) / 2) % m;
        flag[index].first = (flag[index].first + plus + (l - start) * plus) % m;
        flag[index].second = (flag[index].second + plus) % m;
        return ;
    }else{
        push(index, l, r, v, flag);
        int mid = (l + r) >> 1;
        adjust(index << 1, l, mid, targetl, targetr, start, plus, v, flag);
        adjust(index << 1 | 1, mid + 1, r, targetl, targetr, start, plus, v, flag);
        pull(index, v);
        return ;
    } 
}

ll query(int index, int l, int r, int targetl, int targetr, vector<ll> &v, vector<pair<ll, ll>> &flag){
    if(r < targetl or l > targetr) return 0;
    else if(r <= targetr and l >= targetl) return v[index];
    else{
        push(index, l, r, v, flag);
        int mid = (l + r) >> 1;
        ll a = query(index << 1, l, mid, targetl, targetr, v, flag);
        ll b = query(index << 1 | 1, mid + 1, r, targetl, targetr, v, flag);
        return (a + b) % m;
    }
}

int main(){
    int n, q;
    cin >> n >> q;
    vector<ll> A(n + 1);
    for(int i = 1; i <= n; i++) cin >> A[i];

    vector<ll> tmp = A;
    for(int i = 2; i <= n; i++) tmp[i] = (tmp[i - 1] + tmp[i]) % m;
    for(int i = 2; i <= n; i++) tmp[i] = (tmp[i - 1] + tmp[i]) % m;

    vector<ll> C(n << 2);
    vector<pair<ll, ll>> flag(n << 2);
    initialize(1, 1, n, C, tmp);
    for(int i = 0; i < q; i ++){
        int a, b, c;
        cin >> a;
        if(a == 1){
            cin >> b >> c;
            adjust(1, 1, n, b, n, b, (c - A[b]), C, flag);
            A[b] = c;
        }else if(a == 2){
            cin >> b;
            ll res = query(1, 1, n, 1, b, C, flag);
            if(res < 0) res += m;
            cout << res << endl;
        }
    }
}