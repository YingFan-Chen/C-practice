#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ll_max LLONG_MAX
struct edge{
    int to, index, cost; 
    edge(int _to, int _index, int _cost) : to(_to), index(_index), cost(_cost){};
}; 
struct node{
    int val, edgefrom;
    ll dist;
    node(int _val, int _edgefrom, ll _dist) : val(_val), edgefrom(_edgefrom), dist(_dist){};
};
struct cmp{
    bool operator()(node a, node b){
        return a.dist > b.dist;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> res;
    //存圖
    vector<vector<edge>> edges(n + 1);  
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        edges[a].push_back(edge(b, i, c));
        edges[b].push_back(edge(a, i, c)); 
    }

    //存點的狀態, pq取min_dist, nodes維持點的dist 
    priority_queue<node, vector<node>, cmp> pq;
    pq.push(node(1, 0, 0));
    vector<ll> nodes(n + 1, ll_max);
    nodes[1] = 0;
    while(!pq.empty()){
        auto tmp = pq.top();
        pq.pop();
        if(tmp.dist == nodes[tmp.val]){
            if(tmp.edgefrom != 0) res.push_back(tmp.edgefrom); 
            for(auto &i : edges[tmp.val]){
                if(tmp.dist + i.cost < nodes[i.to]){
                    nodes[i.to] = tmp.dist + i.cost;
                    pq.push(node(i.to, i.index, nodes[i.to]));
                }
            }
        }
    }
    for(int &i : res) cout << i << " ";
}