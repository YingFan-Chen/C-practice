#include <bits/stdc++.h>
#include <climits>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

// first -> all , second -> not all
pair<ll, ll> DFS(int root, vector<vector<pair<int, int>>> &edge, vector<int> &d, int from){
    priority_queue<ll, vector<ll>, less<ll>> pq;
    ll weight = 0;
    for(auto &i : edge[root]){
        auto [v, w] = i;
        if(v != from){
            auto [a, b] = DFS(v, edge, d, root);
            weight += a;
            ll tmp = b - a + w;
            if(tmp > 0) pq.push(tmp);
        }
    }
    int cost = d[root];
    if(cost == 0) return {weight, INT_MIN};

    for(int i = 1; i < cost and pq.size(); i ++){
        weight += (ll) pq.top();
        pq.pop();
    }

    if(pq.size()){
        return {weight + (ll) pq.top(), weight};
    }else{
        return {weight, weight};
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i ++) cin >> d[i];

    vector<vector<pair<int, int>>> edge(n + 1);
    for(int i = 1; i < n; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    }

    ll res = DFS(1, edge, d, 0).first;
    cout << res << endl;
}