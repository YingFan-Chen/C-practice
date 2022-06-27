#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    int n;
    ll l, res = 0;
    cin >> n >> l;
    ll total = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(int i = 0; i < n; i++){
        ll tmp;
        cin >> tmp;
        total += tmp;
        pq.push(tmp);
    }
    if(l > total) pq.push(l - total);
    while(pq.size() > 1){
        ll tmp1 = pq.top();
        pq.pop();
        ll tmp2 = pq.top();
        pq.pop();
        res += (tmp1 + tmp2);
        pq.push(tmp1 + tmp2);
    }
    cout << res;
}