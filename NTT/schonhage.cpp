#include <bits/stdc++.h>
#include "../lib/debug"

using namespace std;
using ll = long long;

void schonhage(vector<ll> &, vector<ll> &, int, int);

void NTT(vector<ll> &, int); 

void NTT_partition(vector<ll> &, int, int, int, int);

void vshift(vector<ll> &, int, int);

int main(){
    vector<ll> f = {1, 2, 3, 4, -1, -2, -3, -4};
    vector<ll> F(f.size() << 1, 0);
    schonhage(F, f, 2, 4);
    debug(F);
} 

void schonhage(vector<ll> &F, vector<ll> &f, int n, int m){     //N = m * n, y = x ^ n
    int N = n * m;
    for(int i = 0; i < N; i ++){
        int index = i % n + i / n * (n << 1);
        F[index] = f[i];
    }
    NTT(F, n << 1);
}  

void NTT(vector<ll> &F, int n){
    queue<pair<bool, int>> q;
    q.push({true, 0});
    for(int size = F.size(); size > n; size >>= 1){
        for(int index = 0; index < F.size(); index += size){
            auto [sign, exponent] = q.front();
            q.pop();
            int c = exponent;
            if(sign) c += n;
            c >>= 1;
            q.push({false, c});
            q.push({true, c});
            NTT_partition(F, index, index + size - 1, c, n);
        }
    }
}

void NTT_partition(vector<ll> &F, int l, int r, int c, int n){
    int mid = (l + r) >> 1;
    vector<ll> b(F.begin() + mid + 1, F.begin() + r + 1);
    vshift(b, c, n);
    int i = l, j = mid + 1, k = 0;
    while(i <= mid){
        F[j] = F[i] - b[k];
        F[i] += b[k];
        i ++;
        j ++;
        k ++;
    }
}

void vshift(vector<ll> &v, int x, int n){
    vector<ll> tmp = v;
    for(int index = 0; index < tmp.size(); index += n){
        for(int i = 0; i < n; i ++){
            if(i + x >= n)
                v[(i + x) % n + index] = -tmp[i + index];
            else 
                v[i + x + index] = tmp[i + index];
        }
    }   
}