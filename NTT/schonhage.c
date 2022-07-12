#include <stdint.h>

void makeC(int16_t m, int16_t* C){
    C[0] = m;
    int16_t base = 0, top = 1;
    while(!(C[base] & 1)){
        C[top] = C[base] >> 1;
        ++ top;
        C[top] = C[top - 1] + m;
        ++ top;
        ++ base;
    }
}

void Cooley_Tukey(int16_t l, int16_t r, int16_t n, int16_t *p, int16_t c){
    int16_t tmp[n];
    int16_t mid = (l + r) >> 1;

    for(int16_t i = l, j = mid + 1; i <= mid; i += n, j += n){
        for(int16_t k = 0; k < n; ++ k){
            tmp[(k + c) % n] = p[j + k];
        }
        for(int16_t k = 0; k < c; ++ k){
            tmp[k] = - tmp[k];
        }
        for(int16_t k = 0; k < n; ++ k){
            p[j + k] = p[i + k] - tmp[k];
            p[i + k] += tmp[k];
        }
    }    
}


void schonhage(int16_t m, int16_t n, int16_t* p1, int16_t* p2, int16_t* p3, int16_t* C){
    int16_t mn = m * n;
    int16_t p1_[mn << 1], p2_[mn << 1];

    int16_t i = 0, j = 0;
    while(i < mn >> 1){
        for(int16_t _ = 0; _ < m; ++ _){
            p1_[j] = p1_[j + mn] = p1[i];
            p2_[j] = p2_[j + mn] = p2[i];
            ++ i; ++ j;
        }
        j += m;
    }
    j = m;
    while(i < mn){
        for(int16_t _ = 0; _ < m; ++ _){
            p1_[j] = p1[i];
            p1_[j + mn] = - p1[i];
            p2_[j] = p2[i];
            p2_[j + mn] = - p2[i];
            ++ i; ++ j; 
        }
        j += m;
    }

    int16_t k = 1;
    for(i = mn; i > n; i >>= 1){
        for(j = 0; j < mn << 1; j += i, ++ k){
            Cooley_Tukey(j, j + i - 1, n, p1_, C[k]);
            Cooley_Tukey(j, j + i - 1, n, p2_, C[k]);
        }
    }

    
}