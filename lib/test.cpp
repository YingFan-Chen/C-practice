#include <bits/stdc++.h>
#include "debug"
#include "data_structure"
using namespace std;
int main(){
    vector<ll> v = {1, 1, 1, 1, 1};
    binary_index_tree bit(5);
    for(int i = 0; i < 5; i ++) bit.update(i + 1, v[i]);
    bit.update(3, 3);
    for(int i = 0; i < 5; i ++) cout << bit.query(i + 1) << " ";
}