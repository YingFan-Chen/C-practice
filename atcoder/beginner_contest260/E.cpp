#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "..\..\lib\debug"
#endif
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(n);
    unordered_map<int, vector<int>> um;
    for(int i = 0; i < n; i ++){
        cin >> A[i] >> B[i];
        um[A[i]].push_back(i);
        um[B[i]].push_back(i);
    }

    unordered_set<int> s;
    vector<int> f(m + 1);
    int l = 1, r = 1;
    while(l <= m and r <= m){
        if(um.find(r) != um.end())
            for(auto i : um[r]) s.insert(i);
        if(s.size() == n){
            while(s.size() == n){
                for(int i = r; r <= m; r ++){
                    f[i - l + 1] ++;
                }
                l ++;
                for(auto i : um[l - 1]){
                    if((A[i] > r or A[i] < l) and (B[i] > r or B[i] < l)){
                        s.erase(i);
                    }
                }
            }
        }
        r ++;
    }

    for(int i = 1; i <= m; i ++) cout << f[i] << " ";
}