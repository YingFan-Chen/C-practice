#include <bits/stdc++.h>
using namespace std;
int main(){
    map<int, int> m;
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i){
        int a, b, c;
        cin >> a;
        if(a == 2){
            cin >> b >> c;
            m[b] -= c;
            if(m[b] <= 0) m.erase(b); 
        }else if(a == 1){
            cin >> b;
            m[b] ++;
        }else{
            cout << m.rbegin()->first - m.begin()->first << "\n";
        }

    }

}