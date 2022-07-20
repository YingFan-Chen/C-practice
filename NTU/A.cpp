#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll Pow(ll x, ll n, ll mod){
    ll res = 1;
    while(n > 0){
        if(n & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        n >>= 1;
    }
    return res;
}

int main(){
    int m, n;
    cin >> m >> n;
    unordered_set<int> s;
    ll sum = 0;
    for(int i = 0; i < n; i ++){
        int tmp;
        cin >> tmp;
        sum = (sum + tmp) % m;
        s.insert(tmp);
    }

    // a * n + (0 + n - 1) * n / 2 * d

    for(auto i : s){
        ll d = sum;
        d = (d - i * n) % m;
        ll tmp = Pow(n * (n - 1) / 2, m - 2, m);
        d = (d * tmp) % m;
        if(d < 0) d += m;

        int count = 0;
        ll val = i;
        while(s.find(val) != s.end()){
            val = (val + d) % m;
            count ++;
        }
        if(count == n){
            cout << i << " " << d << endl;
            return 0;
        }
    }

    cout << -1 << endl; 
}