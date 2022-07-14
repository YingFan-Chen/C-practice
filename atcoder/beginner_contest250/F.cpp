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
    vector<pair<int, int>> vertex(n);
    for(int i = 0; i < n; i ++){
        int x, y;
        cin >> x >> y;
        vertex[i] = {x, y};
    }
    
}