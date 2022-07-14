#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

const ll mod = 1e9 + 7;

int main(){
    int n;
    cin >> n;
    unordered_map<int, pair<ll, ll>> prime;
    vector<vector<pair<ll, ll>>> a(n);
    for(int i = 0; i < n; ++ i){
        int m;
        cin >> m;
        for(int j = 0; j < m; j ++){
            ll p, e;
            cin >> p >> e;
            a[i].push_back({p, e});
            if(prime.find(p) == prime.end()){
                prime[p] = {e, 1};
            }else{
                auto [a, b] = prime[p];
                if(e > a) prime[p] = {e, 1};
                else if(e == a) prime[p] = {e, b + 1};
            }
        }
    }

    int count = 1;
    for(int i = 0; i < n; ++ i){
        for(auto &j : a[i]){
            auto [p, e] = j;
            if(prime[p].first == e and prime[p].second == 1){
                count ++;
                break;
            }
        }
    }
    count = min(count, n);
    cout << count << endl;
}