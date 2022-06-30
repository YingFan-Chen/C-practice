#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> tel;
    for(int i = 0; i < m; i ++){
        int u, v;
        cin >> u >> v;
        tel.push_back({u, v});
    }
    unordered_map<int, vector<int>> edges;
    vector<int> undet;
    for(int i = 0; i < m; i ++){
        auto [u, v] = tel[i];
        if(u != 0 and v != 0) edges[u].push_back(v), edges[v].push_back(u);
        else if(u) undet.push_back(u);
        else undet.push_back(v);
    }
    //BFS
    vector<int> begindist(n + 1, -1), enddist(n + 1, -1);
    begindist[1] = 0;
    enddist[n] = 0;
    queue<pair<int, int>> q;
    q.push({1, 0});
    while(q.size()){
        auto[v, d] = q.front();
        q.pop();
        for(auto i : edges[v]){
            if(begindist[i] == - 1){
                begindist[i] = d + 1;
                q.push({i, d + 1});
            }
        }
    }
    q.push({n, 0});
    while(q.size()){
        auto[v, d] = q.front();
        q.pop();
        for(auto i : edges[v]){
            if(enddist[i] == -1){
                enddist[i] = d + 1;
                q.push({i, d + 1});
            }
        }
    }
    //solution
    vector<int> sol(n + 1, 1E5 + 1);
    int minbegindist = 1E5 + 1, minenddist = 1E5 + 1;
    for(auto i : undet){
        if(begindist[i] != -1) minbegindist = min(minbegindist, begindist[i]);
        if(enddist[i] != - 1) minenddist = min(minenddist, enddist[i]);
    }
    for(int i = 1; i <= n; i ++){
        int a = begindist[n], b = - 1, c = - 1, d = - 1;
        if(minbegindist != 1E5 + 1 and enddist[i] != - 1) b = minbegindist + 1 + enddist[i];
        if(minenddist != 1E5 + 1 and begindist[i] != - 1) c = minenddist + 1 + begindist[i];
        if(minbegindist != 1E5 + 1 and minenddist != 1E5 + 1) d = minbegindist + 2 + minenddist;
        if(a != -1) sol[i] = min(sol[i], a);
        if(b != -1) sol[i] = min(sol[i], b);
        if(c != -1) sol[i] = min(sol[i], c);
        if(d != -1) sol[i] = min(sol[i], d);
        if(sol[i] == 1E5 + 1) sol[i] = -1;
    }
    for(int i = 1; i <= n; i ++) cout << sol[i] << " ";
    cout << endl;
}