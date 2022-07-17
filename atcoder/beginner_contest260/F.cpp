#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

bool DFS(int root, vector<int> &depth, int count, unordered_map<int, vector<int>> &edge, vector<int> &from){
    depth[root] = count;
    for(auto i : edge[root]){
        if(depth[i] == -1){
            from[i] = root;
            if(DFS(i, depth, count + 1, edge, from)) return true;
        }else if(count - depth[i] == 3){
            int tmp = root;
            for(int j = 0; j < 4; j ++){
                cout << tmp << " ";
                tmp = from[tmp];
            }
            return true;
        }
    }
    return false;
}

int main(){
    int s, t, m;
    cin >> s >> t >> m;
    unordered_map<int, vector<int>> edge;
    for(int i = 1; i <= m; i ++){
        int v, u;
        cin >> v >> u;
        edge[v].push_back(u);
        edge[u].push_back(v);
    }
    vector<int> depth, from;
    depth.resize(s + t + 1, -1);
    from.resize(s + t + 1, -1);
    if(DFS(1, depth, 0, edge, from)){
        return 0;
    }

    depth.resize(s + t + 1, -1);
    if(DFS(s + 1, depth, 0, edge, from)){
        return 0;
    }

    cout << -1;

}