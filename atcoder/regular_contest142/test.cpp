#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, vector<pair<int, int>>> um;
        int res = 1;
        for(auto i : nums){
            if(um.find(i) == um.end()){
                um[i + 1].assign(2, {INT_MAX, INT_MAX});
                um[i - 1].assign(2, {INT_MAX, INT_MAX});
                um[i - 1][1] = um[i + 1][0] = {i, i};
                cout << 1 << endl; 
            }else{
                auto [a, b] = um[i][0];
                auto [c, d] = um[i][1];
                if(a == -INT_MAX and c == -INT_MAX) continue;
                if(a != INT_MAX and c != INT_MAX){
                    um[a - 1][1].second = d;
                    um[d + 1][0].first = a;
                    um[i][0] = um[i][1] = {-INT_MAX, -INT_MAX};
                    cout << d- a + 1 << endl;
                    res = max(res, d - a + 1);
                }else if(a != INT_MAX){
                    um[a - 1][1].second = i;
                    if(um.find(i + 1) == um.end())
                        um[i + 1].assign(2, {INT_MAX, INT_MAX});
                    um[i + 1][0] = {a, i};
                    um[i][0] = um[i][1] = {-INT_MAX, -INT_MAX};
                    res = max(res, i - a + 1);
                    cout << i - a + 1 << endl;
                }else{
                    um[d + 1][0].first = i;
                    if(um.find(i - 1) == um.end())
                        um[i - 1].assign(2, {INT_MAX, INT_MAX});
                    um[i - 1][1] = {i, d};
                    um[i][0] = um[i][1] = {-INT_MAX, -INT_MAX};
                    res = max(res, d - i + 1);
                    cout << d - i + 1 << endl;
                }
            }
        }
        return res;
    }
};
int main(){
    Solution s;
    vector<int> v = {0,3,7,2,5,8,4,6,0,1};
    s.longestConsecutive(v);

}