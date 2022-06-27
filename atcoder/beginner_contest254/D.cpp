#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;
/*key point : c^2 = a ^ 2 * k * b ^ 2 * k;*/
int maxSquare(int x){
    int i = pow(x, 0.5);
    while(i > 1){
        if(x % (i * i) == 0) break;
        else i --;
    }
    return i * i;
}
int main(){
    int n;
    cin >> n;
    unordered_map<int, int> um;
    um[1] ++;
    ll res = 1;
    for(int i = 2; i <= n; i++){
        int sq = maxSquare(i);
        res += 2 * um[i / sq] + 1;
        um[i / sq] ++;
    }
    cout << res ;
}