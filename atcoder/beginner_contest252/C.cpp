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
#include <climits>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<string> reels(n);
    for(int i = 0; i < n; ++i) cin >> reels[i];
    int res = INT_MAX;
    for(int i = 0; i <= 9; ++i){
        vector<int> tmp(10, 0);
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 10; k++){
                if(reels[j][k] == 48 + i) tmp[k] ++;
            }
        }
        /*for(int i : tmp) cout << i << " ";
        cout << "\n";*/
        int max = 0, max_index = 0;
        for(int i = 0; i < 10; i++){
            if(max <= tmp[i]){
                max = tmp[i];
                max_index = i;
            }
        }
        //cout << max << "\n";
        int t = 10 * (max - 1) + max_index;
        res = min(res, t);
    }
    cout << res;
}