#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n , m;
    cin >> n >> m;
    unordered_map<int, vector<int>> edges;
    for(int i = 0; i < m; i++){
        int a, b ;
        cin >> a >> b ;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int x, k;
        cin >> x >> k;
        queue<pair<int, int>> q; //<node, dist>
        q.push({x, 0});
        unordered_set<int> vertex = {x};
        ll res = 0;
        while(!q.empty()){
            auto i = q.front();
            q.pop();
            if(i.second > k) break;
            res += i.first;
            for(auto j : edges[i.first]){
                if(vertex.find(j) == vertex.end()){
                    vertex.insert(j);
                    q.push({j, i.second + 1});
                }
            }
        }
        cout << res << "\n";
    }
}