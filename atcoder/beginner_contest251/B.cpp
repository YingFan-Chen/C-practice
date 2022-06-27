#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;
int main(){
    int n, w;
    cin >> n >> w;
    vector<int> A(n);
    for(int i = 0; i < n; ++i) cin >> A[i];
    sort(A.begin(), A.end());
    int count = 0;
    unordered_set<int> s;
    //1 weight
    for(int i = 0; i < n; ++i){
        if(A[i] <= w){
            if(s.find(A[i]) == s.end()){
                s.insert(A[i]);
                ++count;
            }
        }else{
            break;
        } 
    }
    //2 weight
    for(int i = 0; i < n - 1; ++i){
        if(A[i] + A[i + 1] > w) break;
        for(int j = i + 1; j < n; ++j){
            int tmp = A[i] + A[j];
            if(tmp <= w){
                if(s.find(tmp) == s.end()){
                    s.insert(tmp);
                    ++count;
                }
            }else{
                break;
            }
        }
    }
    //3 weight
    for(int i = 0; i < n - 2; ++i){
        if(A[i] + A[i + 1] + A[i + 2] > w) break;
        for(int j = i + 1; j < n - 1; ++j){
            if(A[i] + A[j] + A[j + 1] > w) break;
            for(int k = j + 1; k < n; ++k){
                int tmp = A[i] + A[j] +A[k];
                if(tmp <= w){
                    if(s.find(tmp) == s.end()){
                        s.insert(tmp);
                        ++count;
                    }
                }else{
                    break;
                }
            }
        }
    }
    cout << count;
}