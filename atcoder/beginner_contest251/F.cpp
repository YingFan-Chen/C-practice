#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>
using namespace std;
vector<pair<int, int>> res_tree1, res_tree2;
void DFS(int count, int current, unordered_map<int, vector<int>> &edges, vector<int> &nodes){
    nodes[current] = count;
    int min_node = 0, min = INT_MAX;
    for(auto &i : edges[current]){
        if(nodes[i] > 0 && nodes[i] < min){
            min = nodes[i];
            min_node = i;
        }
    }
    if(min_node != 0){ 
        res_tree2.pop_back();
        res_tree2.push_back({current, min_node});
    }
    for(auto &i : edges[current]){
        if(!nodes[i]){
            res_tree1.push_back({current, i});
            res_tree2.push_back({current, i});
            DFS(count + 1, i, edges, nodes);
        }
    }
}
int main(){
    int n, m;
    cin >> n >> m;
    unordered_map<int, vector<int>> edges;
    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        if(edges.find(u) == edges.end()) edges[u] = {v};
        else edges[u].push_back(v);
        if(edges.find(v) == edges.end()) edges[v] = {u};
        else edges[v].push_back(u);
    }
    vector<int> nodes(n + 1, 0);
    DFS(1, 1, edges, nodes);
    for(auto &i : res_tree1) cout << i.first << " " << i.second << "\n";
    for(auto &i : res_tree2) cout << i.first << " " << i.second << "\n";
}