#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
    int n, k;
    string s;
    cin >> n >> k;
    cin >> s;
    
    //find the factors of n
    vector<int> factor;
    for(int i = 1; i <= sqrt((float) n); ++i){
        if(n % i == 0){ 
            factor.push_back(i);
            factor.push_back(n / i);
        }
    }
    sort(factor.begin(), factor.end());
    
    for(int i = 0; i < factor.size(); ++ i){
        int count = 0, h = n / factor.at(i);
        for(int j = 0; j < factor.at(i); ++ j){
            int max_freq = 0;
            vector<int> v(26);
            for(int k = j; k < n; k += factor.at(i)){
                v.at((int) s[k] - 97) ++;
                max_freq = max(max_freq, v.at((int) s[k] - 97));
            }
            count += (h - max_freq);
        }
        if(count <= k){
            cout << factor.at(i) ;
            break;
        }
    }
}