#include <vector>
#include <stack>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
int main(){
    int n;
    cin >> n;
    map<int, int> m;
    for(int i = 0; i < n; ++i){
        int tmp;
        cin >> tmp;
        if(m.find(tmp) == m.end()){
            m[tmp] = 1;
        }else{
            m[tmp] ++ ;
        }
    }
    vector<long long> v;
    for(auto &i : m) v.push_back(i.second);
    int size = v.size();

    long long res = 0;
    for(int i = 1; i < size - 1; ++i){
        res = res + v[i - 1] * (n - v[i - 1] - v[i]) * v[i];
        v[i] += v[i - 1];
    }
    cout << res;
}