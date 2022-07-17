#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.first > b.first) return true;
    else if(a.first == b.first){
        return a.second < b.second;
    }else return false;
}

int main(){
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    vector<int> A(n + 1, 0), B(n + 1, 0);
    vector<pair<int, int>> v1, v2, v3;
    for(int i = 1; i <= n; i ++){
        cin >> A[i];
        v1.push_back({A[i], i});
    }
    for(int i = 1; i <= n; i ++){
        cin >> B[i];
        v2.push_back({B[i], i});
    }
    for(int i = 1; i <= n; i ++){
        v3.push_back({A[i] + B[i], i});
    }

    vector<int> res;
    sort(v1.begin(), v1.end(), cmp);
    sort(v2.begin(), v2.end(), cmp);
    sort(v3.begin(), v3.end(), cmp);
    unordered_set<int> s;
    for(int i = 1; i <= n; i ++) s.insert(i);

    for(int i = 0; i < x; i ++){
        res.push_back(v1[i].second);
        s.erase(v1[i].second);
    }
    int count = 0;
    for(int i = 0; i < n; i ++){
        if(count == y) break;
        if(s.find(v2[i].second) != s.end()){
            res.push_back(v2[i].second);
            s.erase(v2[i].second);
            count ++;
        }
    }
    count = 0;
    for(int i = 0; i < n; i ++){
        if(count == z) break;
        if(s.find(v3[i].second) != s.end()){
            res.push_back(v3[i].second);
            count ++;
        }
    }
    sort(res.begin(), res.end());
    for(auto i : res){
        cout << i << endl;
    }
}