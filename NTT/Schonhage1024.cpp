/*
    Z2048[x] / <x1024 + 1>
*/

#include <bits/stdc++.h>
using namespace std;

class Schonhage1024{
    static constexpr int16_t m = 64, n = 32, log_of_m = 6, log_of_n = 5, mn = 2048, nn = 1024;

public:
    array<int16_t, 1024> p1, p2, res;
    array<int16_t, 2048> p1_ext, p2_ext, res_ext;
    array<int16_t, 64> tmp_array1, tmp_array2;

    Schonhage1024(array<int16_t, 1024> &p1_in, array<int16_t, 1024> &p2_in) : p1(p1_in), p2(p2_in){
        res.fill(0);
        p1_ext.fill(0);
        p2_ext.fill(0);
        res_ext.fill(0);
    }

    void multiple(){
        int16_t i, j, k, l, revBit;

        /*
            y^n + 1
        */
        for(i = 0, j = 0; i < nn and j < mn; i += n, j += m)
        {
            for(k = 0; k < n; k ++)
            {
                p1_ext[j + k] = p1[i + k];
                p2_ext[j + k] = p2[i + k];
            }
        }

        /*
            Cooley Tukey
        */
        revBit = 1;
        for(i = mn; i > m; i >>= 1)
        {
            for(j = 0; j < mn; j += i, revBit ++)
            {
                /*
                    Reverse bit
                */
                int16_t tmp = revBit, C = 0; 
                for(k = 0; k < log_of_m; k ++)
                {
                    C = (tmp & 1) ? C << 1 | 1 : C << 1;
                    tmp >>= 1; 
                }

                int16_t mid = ((j << 1) + i) >> 1;
                for(k = mid; k < j + i; k += m)
                {
                    for(l = 0; l < m; l ++)
                    {
                        if(l + C >= m)
                        {   
                            tmp_array1[l + C - m] = - p1_ext[k + l];
                            tmp_array2[l + C - m] = - p2_ext[k + l];
                        }
                        else
                        {
                            tmp_array1[l + C] = p1_ext[k + l];
                            tmp_array2[l + C] = p2_ext[k + l];
                        }
                    }

                    for(l = 0; l < m; l ++)
                    {
                        p1_ext[k + l] = p1_ext[k + l - (i >> 1)] - tmp_array1[l];
                        p1_ext[k + l - (i >> 1)] += tmp_array1[l];
                        p2_ext[k + l] = p2_ext[k + l - (i >> 1)] - tmp_array2[l];
                        p2_ext[k + l - (i >> 1)] += tmp_array2[l];
                    }
                }              
            }
        } 

        /*
            Multiple(Karatusba? Better?)
        */
        for(i = 0; i < mn; i += m)
        {
            for(j = 0; j < m; j ++)
            {
                for(k = 0; k < m; k ++)
                {
                    if(j + k >= m)
                    {
                        res_ext[i + j + k - m] -= p1_ext[i + j] * p2_ext[i + k];
                    }
                    else
                    {
                        res_ext[i + j + k] += p1_ext[i + j] * p2_ext[i + k];
                    }
                }
            }
        }

        /*
            Gentleman_Sande
        */
        revBit --;
        for(i = m << 1; i <= mn; i <<= 1)
        {
            for(j = mn - i; j >= 0; j -= i, revBit --)
            {
                int16_t tmp = revBit, C = 0;
                for(k = 0; k < log_of_m; k ++)
                {
                    C = (tmp & 1) ? C << 1 | 1 : C << 1;
                    tmp >>= 1;
                }

                int16_t mid = ((j << 1) + i) >> 1;
                for(k = mid; k < j + i; k += m)
                {
                    for(l = 0; l < m; l ++)
                    {
                        tmp_array1[l] = res_ext[k + l - (i >> 1)] - res_ext[k + l];
                        res_ext[k + l - (i >> 1)] += res_ext[k + l];
                    }

                    for(l = 0; l < m; l ++)
                    {
                        if(l - C < 0)
                        {
                            res_ext[k + l - C + m] = - tmp_array1[l];
                        }
                        else
                        {
                            res_ext[k + l - C] = tmp_array1[l];
                        }
                    }
                }
            }
        }

        /*
            resize
        */
        for(i = 0, j = 0; i < mn; i += m, j += n)
        {
            for(k = 0; k < m; k ++)
            {   
                if(k + j >= nn)
                {
                    res[k + j - nn] -= res_ext[i + k]; 
                }
                else
                {
                    res[k + j] += res_ext[i + k];
                }
            }
        }

        for(i = 0; i < nn; i ++)
        {
            res[i] = (res[i] >> log_of_n) % 2048;
        }
    }
};


class Normal{
public:
    array<int16_t, 1024> p1, p2, res;
    Normal(array<int16_t, 1024> &p1, array<int16_t, 1024> &p2): p1(p1), p2(p2){
        res.fill(0);
    }

    void multiple(){
        for(int i = 0; i < p1.size(); i ++){
            for(int j = 0; j < p2.size(); j ++){
                if(i + j >= p1.size()){
                    res[(i + j) % p1.size()] -= p1[i] * p2[j];
                    res[(i + j) % p1.size()] %= 2048;
                }else{
                    res[i + j] += p1[i] * p2[j];
                    res[i + j] %= 2048;
                }
            }
        }
    }
};