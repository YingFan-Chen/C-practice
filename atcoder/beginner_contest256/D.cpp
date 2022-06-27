#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    for(int i = 0; i < n; i ++){
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }
    sort(v.begin(), v.end());
    int left = v[0].first, right = v[0].second;
    for(int i = 1; i < n; i ++){
        if(v[i].first <= right){
            if(v[i].second > right) right = v[i].second;
        }else{
            cout << left << " " << right << endl;
            left = v[i].first;
            right = v[i].second;
        }
    }
    cout << left << " " << right << endl;
}