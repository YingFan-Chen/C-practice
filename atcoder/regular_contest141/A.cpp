#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    int t;
    cin >> t;
    vector<ll> v(t);
    for(int i = 0; i < t; i++) cin >> v[i];
    for(int i = 0; i < t; i++){
        ll n = v[i], res = 0; 
        string str = to_string(n);
        int k = str.length();
        for(int i = 2; i <= k; i++){  
            //i : 份數, h : 長度
            if(k % i == 0){
                int h = k / i;
                string partial = str.substr(0, h);
                for(int j = 0; j < 2; j++){
                    string tmp = "";
                    ll p = stoll(partial) - j;
                    for(int b = 0; b < i; b++){
                        tmp += to_string(p);      
                    }
                    ll tmp1 = stoll(tmp);
                    if(tmp1 <= n){
                        res  = max(res, tmp1);
                    }
                }
            }
        }
        cout << res << "\n";
    }
}