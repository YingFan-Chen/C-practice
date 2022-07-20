#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;

class binary_index_tree{
        ll size;
        std::vector<ll> v;
    public:
        binary_index_tree(ll n) : size(n) {
            v.assign(n + 1, 0);
        }
        void update(ll index, ll x){
            while(index <= size){
                v[index] += x;
                index += index & (-index);
            }
            return ;
        }
        ll query(ll index){
            ll res = 0;
            while(index){
                res += v[index];
                index -= index & (-index);
            }
            return res;
        }
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(n);
    unordered_map<int, vector<int>> um;
    for(int i = 0; i < n; i ++){
        cin >> A[i] >> B[i];
        um[A[i]].push_back(i);
        um[B[i]].push_back(i);
    }

    unordered_set<int> s;
    vector<int> f(m + 1);
    binary_index_tree BIT(m);
    int l = 1, r = 1;
    while(l <= m and r <= m){
        if(um.find(r) != um.end())
            for(auto i : um[r]) s.insert(i);
        while(s.size() == n){
            // minLength = r - l + 1, maxLength = m - l + 1
            BIT.update(r - l + 1, 1);
            BIT.update(m - l + 2, -1);

            l ++;
            for(auto i : um[l - 1]){
                if((A[i] > r or A[i] < l) and (B[i] > r or B[i] < l)){
                    s.erase(i);
                }
            }
        }
        r ++;
    }

    for(int i = 1; i <= m; i ++){
        cout << BIT.query(i) << " ";
    }
}