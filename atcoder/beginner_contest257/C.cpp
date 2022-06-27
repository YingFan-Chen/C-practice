#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n;
    string s;
    cin >> n >> s;
    vector<ll> W(n + 1);
    for(int i = 1; i <= n; i ++) cin >> W[i];
    map<ll, pair<int, int>> m;
    for(int i = 1; i <= n; i ++){
        if(s[i - 1] == '1') m[W[i]].second ++;
        else m[W[i]].first ++; 
    }
    vector<pair<int, int>> v;
    int child = 0, adult = 0;
    for(auto &i : m){
        child += i.second.first;
        adult += i.second.second;
        v.push_back({child, adult});
    }
    int res = max(child, adult);

    /*auto j = m.begin();
    j ++;
    while(j != m.end()){
        auto tmp = j;
        tmp --;
        j->second.first += tmp->second.first;
        j->second.second += tmp->second.second;
    }
    int child = m.rbegin()->second.first, adult = m.rbegin()->second.second;
    int res = max(child, adult);*/
    for(auto &i : v){
        int count = 0;
        count = i.first;
        count += adult - i.second;
        res = max(res, count);
    }


    cout << res << endl;
}