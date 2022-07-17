#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> P(n + 1);
    for(int i = 1; i <= n; i ++) cin >> P[i];

    set<pair<int, int>> s;
    vector<vector<int>> v(n);
    vector<int> res(n + 1, -1);
    int index = 0;
    for(int i = 1; i <= n; i ++){
        int tmp = P[i];
        if(s.empty()){
            if(k == 1){
                res[tmp] = i;
                continue;
            }
            s.insert({tmp, index});
            v[index].push_back(tmp);
            index ++;
        }else{
            auto iter = s.lower_bound({tmp, 0});
            if(iter != s.end()){
                auto [a, b] = *iter;
                s.erase(iter);
                if(v[b].size() + 1 == k){
                    res[tmp] = i;
                    for(auto x : v[b]) res[x] = i;
                }else{
                    s.insert({tmp, b});
                    v[b].push_back(tmp);
                }
            }else{
                if(k == 1){
                    res[tmp] = i;
                    continue;
                }
                s.insert({tmp, index});
                v[index].push_back(tmp);
                index ++;
            } 
        }
    }

    for(int i = 1; i <= n; i ++) cout << res[i] << endl;
}