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
    vector<int> v;
    for(int i = 3; i <= n; i ++){
        cout << "? 1 " << i << endl;
        int d;
        cin >> d; 
        if(d == 1) v.push_back(i);
    }
    map<int, int> m;
    if(v.empty()) cout << "! 1" << endl;
    else{
        for(auto &i : v){
            cout << "? 2 " << i << endl;
            int d;
            cin >> d;
            m[d] ++;
        }
        int tmp = m.begin()->first;
        if(tmp == 2 and m[tmp] > 1)  cout << "! 1" << endl;
        else if(tmp == 2 and v.size() == 1){
            int x = 0;
            for(int j = 3; j <= n; j ++){
                if(j != v[0]){
                    cout << "? 2 " << j << endl;
                    int d;
                    cin >> d;
                    if(d == 1){
                        x = j; 
                        break;
                    }
                }
            }
            if(x == 0){
                cout << "! 1" << endl;
            }else{
                int a, b;
                cout << "? " << x << " " << v[0] << endl;
                cin >> a;
                cout << "? " << x << " 1" << endl;
                cin >> b;
                if(a > b) cout << "! 1" << endl;
                else cout << "! 3" << endl;
            }
        }else cout << "! " << tmp + 1 << endl;
    }
}