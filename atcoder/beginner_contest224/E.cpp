#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;

map<pair<int, int>, pair<int, int>> points; // first -> a, second -> res
unordered_map<int, vector<pair<int, int>>> row, column; //first -> a, second -> r/c
unordered_map<int, unordered_map<int, int>> _row, _column;

int DFS(int x, int y){
    int a = points[{x, y}].first, res = points[{x,y}].second;
    if(res != -1) return res;
    auto iter = upper_bound(row[x].begin(), row[x].end(), pair<int, int> {a, INT_MAX});
    int maximum = -1, tmp_a = iter->first;
    if(_row[x].find(a) != _row[x].end()) maximum = max(maximum, _row[x][a]);
    else{ 
        while(iter != row[x].end() and iter->first == tmp_a){
            int tmp = DFS(x, iter->second);
            maximum = max(maximum, tmp);
            _row[x][a] = max(_row[x][a], tmp);
            iter ++;
        }
    }
    iter = upper_bound(column[y].begin(), column[y].end(), pair<int, int> {a, INT_MAX});
    tmp_a = iter->first;
    if(_column[y].find(a) != _column[y].end()) maximum = max(maximum, _column[y][a]);
    else{
        while(iter != column[y].end() and iter->first == tmp_a){
            int tmp = DFS(iter->second, y);
            maximum = max(maximum, tmp);
            _column[y][a] = max(_column[y][a], tmp);
            iter ++;
        }
    }
    points[{x, y}].second = maximum + 1;
    return maximum + 1;
}

int main(){
    int h, w, n;
    cin >> h >> w >> n;
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i ++){
        int r, c, a;
        cin >> r >> c >> a;
        points[{r, c}] = {a, -1};
        row[r].push_back({a, c});
        column[c].push_back({a, r});
        v.push_back({r, c});
    }

    for(auto &i : row) sort(i.second.begin(), i.second.end());
    for(auto &i : column) sort(i.second.begin(), i.second.end());

    for(auto &i : v){
        if(points[i].second != -1) cout << points[i].second << endl;
        else cout << DFS(i.first, i.second) << endl ;
    }
}