#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n, q;
    string s;
    cin >> n >> q >> s;
    int head = 0;
    for(int i = 0; i < q; i ++){
        int t, x;
        cin >> t >> x;
        if(t == 1){
            head = (head + n - x) % n;
        } else{
            int index = (head + x - 1) % n;
            cout << s[index] << endl;
        }
    }
}