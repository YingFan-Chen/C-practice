#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

void update(vector<pair<int, int>> &state, unordered_map<int, vector<int>> &edge, string &s, int n){
    for(int i = 1; i <= n; i ++){
        if(s[i] != 'X'){
            int w = 0, b = 0;
            for(auto &j : edge[i]){
                if(s[j - 1] == 'W') w ++;
                else if(s[j - 1] == 'B') b ++;
                state[i] = {w, b};
            }    
        }
    }
}

int main(){
    int n;
    cin >> n;
    unordered_map<int, vector<int>> edge;
    for(int i = 1; i < n; i ++){
        int a , b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    string s;
    cin >> s;

    vector<pair<int, int>> state(n + 1, {0, 0});
    vector<int> res;

    for(int i = 1; i <= n; i ++){
        int index, maxi = -1E5;
        update(state, edge, s, n);
        //debug(s);
        for(int j = n; j > 0; j --){
            //debug(state[j]);
            auto [w, b] = state[j]; 
            if(s[j - 1] == 'W' and b - w >= maxi) index = j, maxi = b - w;
        }
        if(maxi == -1E5){
            cout << -1 ;
            return 1;
        }
        res.push_back(index);
        s[index - 1] = 'X';
        for(auto &j : edge[index]){
            if(s[j - 1] == 'W') s[j - 1] = 'B';
            else if(s[j - 1] == 'B') s[j - 1] = 'W';
        }  
    }
    for(int i = 0; i < n; i ++) cout << res[i] << " ";
}