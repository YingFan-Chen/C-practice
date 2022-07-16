#include <bits/stdc++.h>
#include "Schonhage.cpp"
using namespace std;
static constexpr int mod = 5227, m = 16, n = 32; // Cause we use int32_t, the mod must less than square of INT32_MAX or it will overflow.

void debug(vector<int> &v, int n){
    for(int i = 0; i < v.size(); i ++ ){
        if(i != 0 and i % n == 0){
            cout << endl;
        }
        printf("%5d ", v[i]);
    }
    cout << endl << "================================" << endl;
}


class Normal{
public:
    int m, n, mn, mod;
    vector<int> p1, p2, p3;
    Normal(int m_in, int n_in, int mod_in) : m(m_in), n(n_in), mod(mod_in){
        mn = m * n;
        p1.resize(mn, 0);
        p2.resize(mn, 0);
        p3.resize(mn, 0);
    }

    void Multiple(){
        for(int i = 0; i < mn; ++ i){
            for(int j = 0; j < mn; ++ j){
                int tmp = (p1[i] * p2[j]) % mod;
                if(i + j >= mn){
                    p3[(i + j) % mn] = (p3[(i + j) % mn] - tmp + mod) % mod;
                }else{
                    p3[i + j] = (p3[i + j] + tmp) % mod;
                }
            }
        }
    }
};


int main(){
    vector<int> p1(m * n), p2(m * n);
    srand(time(NULL));

    //Generate p1, p2;
    for(int i = 0; i < m * n; ++ i){
        p1[i] = rand() % mod;
        p2[i] = rand() % mod;
    }

    Schonhage S(m, n, mod);
    S.p1 = p1;
    S.p2 = p2;
    S.Multiple();
    debug(S.p3, n);

    Normal N(m, n, mod);
    N.p1 = p1;
    N.p2 = p2;
    N.Multiple();
    debug(N.p3, n);

    bool flag = true;
    for(int i = 0; i < m * n; i ++){
        if(S.p3[i] != N.p3[i]){
            flag = false;
            break;
        }
    }
    if(flag) cout << "True" << endl;
    else cout << "False" << endl;
}