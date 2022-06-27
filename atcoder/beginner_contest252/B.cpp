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
    int n, k;
    cin >> n >> k;
    vector<int> A(n + 1);
    for(int i = 1; i <= n; ++i) cin >> A[i];
    vector<int> B(k + 1);
    for(int i = 1; i <= k; ++i) cin >> B[i];
    vector<int> max;
    int maxi = 0;
    for(int i = 1; i <= n; ++i){
        if(A[i] > maxi){
            max.clear();
            maxi = A[i];
            max.push_back(i);
        }else if(A[i] == maxi) max.push_back(i);
    }
    int flag = 0;
    for(int i = 1; i<= k; ++i){
        for(int j = 0; j <= max.size(); ++j){
            if(max[j] == B[i]){
                flag = 1;
                break;
            }
        }
    }
    if(flag) cout << "Yes";
    else cout << "No";
}