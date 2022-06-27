#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n , k;
    cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    for(int i = 0; i < k; i++){
        vector<int> tmp;
        for(int j = i; j < n; j += k){
            tmp.push_back(v[j]);
        }
        sort(tmp.begin(), tmp.end());
        int l = 0;
        for(int j = i; j < n; j += k){
            v[j] = tmp[l];
            l ++;
        }
    }
    for(int i = 1; i < n; i ++ ){
        if(v[i] <  v[i - 1]){
            cout << "No" ;
            return 0;
        }
    }
    cout << "Yes";
}