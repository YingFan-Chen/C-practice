#include <bits/stdc++.h>
using namespace std;

class Schonhage{
    

public:
    int32_t m, n, mn, mn2, mlog, nlog, mod;
    vector<int32_t> p1, p2, p3, p1_ext, p2_ext, p3_ext;
    
    //Constructor
    Schonhage(int32_t m_in, int32_t n_in, int32_t mod_in) : m(m_in), n(n_in), mod(mod_in){
        mn = m * n;
        mn2 = mn << 1;
        int32_t i = 0, x = 1;
        while(true){
            if(x == n){
                nlog = i;
                break;
            }else if(x == m){
                mlog = i;
            }
            ++ i;
            x <<= 1;
        }
        p1.resize(mn, 0);
        p2.resize(mn, 0);
        p3.resize(mn, 0);
        p1_ext.resize(mn2, 0);
        p2_ext.resize(mn2, 0);
        p3_ext.resize(mn2, 0);
    }

    int32_t Pow(int32_t x, int32_t n){
        if(x == 0) return 0;
        int64_t res = 1, base = x;
        while(n > 0){
            if(n & 1){
                res = (res * base) % mod;
            }
            n >>= 1;
            base = (base * base) % mod;
        }
        return (int32_t) res;
    }

    void Multiple(){
        int32_t i, j, k, l, revC;

        //Broaden
        i = 0, j = 0;
        while(i < mn >> 1){
            for(k = 0; k < m; ++ k){
                p1_ext[j] = p1_ext[j + mn] = p1[i];
                p2_ext[j] = p2_ext[j + mn] = p2[i];
                ++ i; ++ j;
            }
            j += m;
        }
        j = m;
        while(i < mn){
            for(int16_t k = 0; k < m; ++ k){
                p1_ext[j] = p1[i];
                p1_ext[j + mn] = mod - p1[i];
                p2_ext[j] = p2[i];
                p2_ext[j + mn] = mod - p2[i];
                ++ i; ++ j; 
            }
            j += m;
        }

        //Cooley_Tukey
        revC = 2;
        for(i = mn; i > n; i >>= 1){
            for(j = 0; j < mn2; j += i, ++ revC){
                int32_t tmp = revC, C = 0;
                for(k = 0; k < nlog; ++ k){
                    C = (tmp & 1) ? C << 1 | 1 : C << 1;
                    tmp >>= 1;
                }

                vector<int32_t> v1(n, 0), v2(n, 0);
                int32_t mid = ((j << 1) + i) >> 1;
                for(k = mid; k < j + i; k += n){
                    for(l = 0; l < n; ++ l){
                        if(l + C >= n){
                            v1[(l + C) % n] = (mod - p1_ext[k + l]) % mod;
                            v2[(l + C) % n] = (mod - p2_ext[k + l]) % mod;
                        }else{
                            v1[l + C] = p1_ext[k + l];
                            v2[l + C] = p2_ext[k + l];
                        }
                    }
                    
                    for(l = 0; l < n; ++ l){
                        p1_ext[k + l] = (p1_ext[k + l - (i >> 1)] - v1[l] + mod) % mod; 
                        p1_ext[k + l - (i >> 1)] = (p1_ext[k + l - (i >> 1)] + v1[l]) % mod;
                        p2_ext[k + l] = (p2_ext[k + l - (i >> 1)] - v2[l] + mod) % mod;
                        p2_ext[k + l - (i >> 1)] = (p2_ext[k + l - (i >> 1)] + v2[l]) % mod;
                    }
                }
            }
        }

        //Mult
        for(i = 0; i < mn2; i += n){
            for(j = 0; j < n; ++ j){
                for(k = 0; k < n; ++ k){
                    int32_t tmp = (p1_ext[i + j] * p2_ext[i + k]) % mod;
                    if(j + k >= n){
                        p3_ext[i + (j + k) % n] = (p3_ext[i + (j + k) % n] - tmp + mod) % mod;
                    }else{
                        p3_ext[i + j + k] = (p3_ext[i + j + k] + tmp) % mod;
                    }
                }
            }
        }

        //Gentleman_Sande
        -- revC;
        for(i = n << 1; i <= mn2; i <<= 1){
            for(j = mn2 - i; j >= 0; j -= i, -- revC){
                int32_t tmp = revC, C = 0;
                for(k = 0; k < nlog; ++ k){
                    C = (tmp & 1) ? C << 1 | 1 : C << 1;
                    tmp >>= 1;
                }

                vector<int32_t> v3(n, 0);
                int32_t mid = ((j << 1) + i) >> 1;
                for(k = mid; k < j + i; k += n){
                    for(l = 0; l < n; ++ l){
                        v3[l] = (p3_ext[k + l - (i >> 1)] - p3_ext[k + l] + mod) % mod;
                        p3_ext[k + l - (i >> 1)] = (p3_ext[k + l - (i >> 1)] + p3_ext[k + l]) % mod;
                    }

                    for(l = 0; l < n; ++ l){
                        if(l - C < 0){
                            p3_ext[k + l - C + n] = (mod - v3[l]) % mod;
                        }else{
                            p3_ext[k + l - C] = v3[l];
                        }
                    }
                }
            }
        } 

        //resize
        for(i = 0, j = 0; i < mn2; i += n, j += m){
            for(k = 0; k < n; ++ k){
                if(k + j >= mn){
                    p3[(k + j) % mn] = (p3[(k + j) % mn] - p3_ext[i + k] + mod) % mod;
                }else{
                    p3[k + j] = (p3[k + j] + p3_ext[i + k]) % mod;
                }
            }
        }

        //divide
        int32_t denom = Pow(n, mod - 2);
        for(int i = 0; i < mn; ++ i){
            p3[i] = (p3[i] * denom) % mod;
        }
    }
};