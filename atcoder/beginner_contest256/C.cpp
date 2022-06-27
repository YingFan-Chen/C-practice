#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

void DFS(vector<int> &v, vector<int> &h, vector<int> &w, int &count){
    int n = v.size();
    //debug(v);
    if(n == 9){
        if(v[6] + v[7]+ v[8] != h[2]) return;
        if(v[2] + v[5]+ v[8] != w[2]) return;
        count ++;
        return;
    }else if(n == 8){
        if(v[1] + v[4]+ v[7] != w[1]) return;
    }else if(n == 7){
        if(v[0] + v[3]+ v[6] != w[0]) return;
    }else if(n == 6){
        if(v[3] + v[4]+ v[5] != h[1]) return;
    }else if(n == 3){
        if(v[0] + v[1]+ v[2] != h[0]) return;
    }
    for(int i = 1; i < 29; i ++){
            v.push_back(i);
            DFS(v, h, w, count);
            v.pop_back();
    }
    return ;
}

int main(){
    vector<int> h(3), w(3);
    for(int i = 0; i < 3; i ++){
        cin >> h[i];
    }
    for(int i = 0; i < 3; i ++){
        cin >> w[i];
    }
    vector<int> v;
    int count = 0;
    DFS(v, h, w, count);
    cout << count;
}