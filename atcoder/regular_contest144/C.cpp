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
    if(n - k < k){
        cout << - 1 << endl;
    }else{
        vector<int> v(n + 1, 0);

        for(int i = 1; i <= n - k; i ++){
            v[i] = k + i;
        }

        int j = 1;
        for(int i = n - k + 1; i <= n; i ++){
            v[i] = j;
            j ++;
        }

        for(int i = 1; i <= n; i ++) cout << v[i] << " ";
    }
}