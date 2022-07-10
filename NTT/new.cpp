#include <bits/stdc++.h>
using namespace std;

const int16_t _nm = 512, _mod = 17, _m = 16, _n = 32;   
// x^n = -1, y^n = -1 

void schonhage(int16_t* p1, int16_t* p2, int16_t* res, int16_t nm, int16_t m, int16_t n){
    int16_t _p1[nm << 1], _p2[nm << 1];
    int16_t i = 0, j = 0, k;

    for(; i < nm >> 1; ++ i){
        for(k = 0; k < m; ++ k){
            _p1[j] = p1[i];
            _p1[j + m] = - p1[i];
            ++ j;
        }
        j += m;
    }
    for(; i < nm; ++ i){
        for(k = 0; k < m; ++ k){
            _p1[j + m] = _p1[j] = p1[i];
            ++ j;
        }
        j += m;
    }
    
}



int main(){

}