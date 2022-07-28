#include <bits/stdc++.h>
#include "Schonhage.cpp"
#include "Schonhage2048.cpp"
using namespace std;
static constexpr int mod = 2048, m = 32, n = 32;

template <typename T>
void debug(vector<T> &v, int n){
    for(int i = 0; i < v.size(); i ++ ){
        if(i != 0 and i % n == 0){
            cout << endl;
        }
        printf("%5d ", v[i]);
    }
    cout << endl << "================================" << endl;
}

template <typename T>
void debugarray(array<T, 1024> &v, int n){
    for(int i = 0; i < v.size(); i ++){
        if(i != 0 and i % n == 0){
            cout << endl;
        }
        printf("%5d ", v[i]);
    }
    cout << endl << "================================" << endl;
}


int main(){
    vector<int16_t> p1(m * n), p2(m * n);
    array<int16_t, 1024> a1, a2;
    a1.fill(0);
    a2.fill(0);
    srand(time(NULL));

    //Generate p1, p2;
    for(int i = 0; i < 509; ++ i){
        a1[i] = p1[i] = rand() % mod;
        a2[i] = p2[i] = rand() % mod;
    }

    /*Schonhage S(m, n, mod);
    S.p1 = p1;
    S.p2 = p2;
    S.Multiple();
    debug(S.p3, n);*/

    /*Normal N(m, n, mod);
    N.p1 = p1;
    N.p2 = p2;
    N.Multiple();
    debug(N.p3, n);*/

    Schonhage1024 S1024(a1, a2);
    S1024.multiple();
    //debugarray(S1024.res, n);

    Normal_multi N1024(p1, p2);
    N1024.multiple();
    //debug(N1024.res, n);


    for(int i = 0; i < 1024; i ++){
        if((S1024.res[i] - N1024.res[i]) % 2048 != 0){
            cout << S1024.res[i] << " " << N1024.res[i] << endl;
            cout << "false" << endl;
            return 0;
        }
    }
    cout << "True" << endl;
}