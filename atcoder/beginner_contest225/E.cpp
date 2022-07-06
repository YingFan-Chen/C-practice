#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#endif
using namespace std;

struct frac{
    ll x, y;
    frac(ll a, ll b) : x(a), y(b) {}
    bool operator< (const frac &t) const{
        if(y * t.x < x * t.y) return true;
        else return false;
    }
    bool operator<= (const frac &t) const{
        if(y * t.x <= x * t.y) return true;
        else return false;
    }
};


int main(){
    int n;
    cin >> n;
    vector<pair<frac, frac>> v;
    for(int i = 0; i < n; i ++){
        int x, y;
        cin >> x >> y;
        v.push_back({frac{x - 1, y}, frac{x, y - 1}});
    }
    sort(v.begin(), v.end());
    int count = 0;
    frac cur(1, 0);
    for(auto &i : v){
        if(cur <= i.second){
            count ++;
            cur = i.first;
        }
    }
    cout << count << endl;
}