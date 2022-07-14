#include <stdint.h>
#include <string.h>
#include <stdio.h>

static constexpr int32_t mod = 337;

void Cooley_Tukey(int16_t l, int16_t r, int16_t n, int16_t *p, int16_t c){
    int16_t tmp[n];
    int16_t mid = (l + r) >> 1;

    for(int i = l, j = mid + 1; i <= mid; i += n, j += n){
        /*Shifting*/
        for(int k = 0; k < n; ++ k){
            tmp[(k + c) % n] = p[j + k];
        }
        for(int k = 0; k < c; ++ k){
            tmp[k] = - tmp[k];
        }

        /*A + BC & A - BC*/
        for(int k = 0; k < n; ++ k){
            p[j + k] = p[i + k] - tmp[k];
            p[i + k] += tmp[k];
        }
    }    
}

void  Gentleman_Sande(int16_t l, int16_t r, int16_t n, int16_t *p, int16_t c){
    int16_t tmp[n];
    int16_t mid = (l + r) >> 1;
    for(int i = l, j = mid + 1; i <= mid; i += n, j += n){
        for(int k = 0; k < n; ++ k){
            tmp[k] = p[i + k] - p[j + k];
            p[i + k] += p[j + k];
        }

        for(int k = 0; k < n; ++ k){
            p[j + (k - c + n) % n] = tmp[k];
        }
        for(int k = n - c; k < n; ++ k){
            p[j + k] = - p[j + k]; 
        }
    }
}

void Polynomial_Multiple(int16_t *p1, int16_t *p2, int16_t *p3, int16_t l, int16_t n){
    for(int i = 0; i < n; ++ i){
        for(int j = 0; j < n ; ++ j){
            int32_t tmp = p1[l + i] * p2[l + j];
            if(i + j >= n){
                p3[l + (i + j) % n] -= tmp;
            }else{
                p3[l + (i + j)] += tmp;
            }
        }
    }
}


void Schonhage_Multiple(int16_t m, int16_t n, int16_t* p1, int16_t* p2, int16_t* p3){
    int16_t mn = m * n, mn2 = mn << 1;
    int16_t n_pow;
    for(int i = 1, pow = 0; i <= mn; i <<= 1, ++ pow){
        if(i == n){
            n_pow = pow;
            break;
        } 
    }
    int16_t p1_[mn2], p2_[mn2], p3_[mn2];
    memset(p3_, 0, sizeof(p3_));

    /* Broaden input array*/
    int i = 0, j = 0;
    while(i < mn >> 1){
        for(int _ = 0; _ < m; ++ _){
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

    /*Cooley Tukey Bufferfly*/
    int16_t revC = 2;
    for(i = mn; i > n; i >>= 1){
        for(j = 0; j < mn2; j += i, ++ revC){
            int16_t tmp = revC, C = 0;
            for(int _ = 0; _ < n_pow; ++ _){
                C = (tmp & 1) ? C << 1 | 1 : C << 1;
                tmp >>= 1;
            }

            Cooley_Tukey(j, j + i - 1, n, p1_, C);
            Cooley_Tukey(j, j + i - 1, n, p2_, C);
        }
    }

    /*Multiple*/
    for(i = 0; i < mn2; i += n){
        Polynomial_Multiple(p1_, p2_, p3_, i, n);
    }

    //for(i = 0; i < mn2; i ++) printf("%d ", p3_[i] % 7);
    
    /*Gentleman Sande Butterfly*/
    -- revC; 
    for(i = n << 1; i <= mn2; i <<= 1){
        for(j = mn2 - i; j >= 0; j -= i, -- revC){
            int16_t tmp = revC, C = 0;
            for(int _ = 0; _ < n_pow; ++ _){
                C = (tmp & 1) ? C << 1 | 1 : C << 1;
                tmp >>= 1;
            }

            Gentleman_Sande(j, j + i - 1, n, p3_, C);
        }
    }

    //for(i = 0; i < mn2; i ++) printf("%d ", p3_[i] % 7);

    memset(p3, 0, sizeof(p3));
    for(i = 0, j = 0; i < mn2; i += n, ++ j){
        int16_t tmp = j << 1;
        for(int k = 0; k < n; ++ k){
            if(k + tmp >= mn){
                p3[(k + tmp) % mn] -= p3_[i + k];
            }else{
                p3[k + tmp] += p3_[i + k];
            }
        }
    }

}