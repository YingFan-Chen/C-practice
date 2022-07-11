#include <bits/stdc++.h>
using namespace std;

const int16_t _mn = 512, _mod = 17, _m = 16, _n = 32;

const int16_t C512[60] = {  8, -8, 24, -24,
                            4, -4, 20, -20, 12, -12, 28, -28,
                            2, -2, 18, -18, 10, -10, 6, -6, 22, -22, 14, -14, 30, -30,
                            1, -1, 17, -17, 9, -9, 25, -25, 5, -5, 21, -21, 3, -3, 19, -19, 11, -11, 27, -27, 7, -7, 23, -23, 15, -15, 31, -31  }; 
                

void schonhage(int16_t* p1, int16_t* p2, int16_t* res, int16_t mn, int16_t m, int16_t n){
    int16_t _p1[mn << 1], _p2[mn << 1];
    
    int16_t i = 0, j = 0;
    while(i < mn >> 1){
        for(int16_t _ = 0; _ < m; ++ _){
            _p1[j] = _p1[j + mn] = p1[i];
            _p2[j] = _p2[j + mn] = p2[i];
            ++ i; ++ j;
        }
        j += m;
    }
    j = m;
    while(i < mn){
        for(int16_t _ = 0; _ < m; ++ _){
            _p1[j] = p1[i];
            _p1[j + mn] = - p1[i];
            _p2[j] = p2[i];
            _p2[j + mn] = - p2[i];
            ++ i; ++ j; 
        }
        j += m;
    }

    int16_t C[n << 2];
    C[0] = m >> 1;
    C[1] = - C[0];
    C[2] = C[0] + m;
    C[3] = - C[2];
    int16_t base = 0, top = 4;

    for(int16_t k = m; k > 1; k >>= 1){
        
    }  
}



int main(){

}