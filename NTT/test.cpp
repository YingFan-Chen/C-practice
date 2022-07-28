#include <bits/stdc++.h>
#include "Schonhage1024.cpp"
using namespace std;
static constexpr int16_t mod = 2048;

template <typename T>
void debugarray(array<T, 1024> &v, int n){
    for(int i = 0; i < v.size(); i ++){
        if(i != 0 and i % n == 0){
            cout << endl;
        }
        printf("%5d ", v[i]);
    }
    cout << endl << "======================================================================================" << endl;
}


int main(){
    array<int16_t, 1024> a1, a2;
    a1.fill(0);
    a2.fill(0);
    srand(time(NULL));

    //Generate p1, p2;
    for(int i = 0; i < 509; ++ i){
        a1[i] = rand() % mod;
        a2[i] = rand() % mod;
    }

    Schonhage1024 S1024(a1, a2);
    S1024.multiple();
    //debugarray(S1024.res, 64);

    Normal N1024(a1, a2);
    N1024.multiple();
    //debugarray(N1024.res, 64);


    for(int i = 0; i < 1024; i ++){
        if((S1024.res[i] - N1024.res[i]) % 2048 != 0){
            cout << S1024.res[i] << " " << N1024.res[i] << endl;
            cout << "false" << endl;
            return 0;
        }
    }
    cout << "True" << endl;
}