#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
int main(){
    long long n;
    int p_range, count = 0;
    vector<bool> p;
    vector<int> prime = {}; 
    cin >> n;
    p_range = ceil(pow((double) n / 2, 1.0 / 3));
    p.assign(p_range + 1, true);
    for(int i = 2; i <= p_range; ++ i){
        if(p[i]){
            prime.push_back(i);
            for(int j = i; j <= p_range; j += i) p[j] = false;
        }
    }
    for(int i = 0; i <= prime.size(); ++ i){
        for(int j = i + 1; j < prime.size(); ++ j){
            if(prime[i] * pow(prime[j], 3) <= n) ++ count;
            else break;
        }
    }
    cout << count;
}