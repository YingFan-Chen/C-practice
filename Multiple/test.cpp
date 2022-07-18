#include <bits/stdc++.h>
#include "multiple.cpp"
using namespace std;
using ll = long long;

int multiple(int x, int y, int mod){
    ll res = ((ll) x * (ll) y) % mod;
    return res; 
}
int main(){
    int32_t x, y, mod;
    srand(time(NULL));
    x = rand();
    y = rand();
    mod = rand();
    cout << multiple(x, y, mod) << endl;
    cout << binary_mult(x, y, mod) << endl;
}