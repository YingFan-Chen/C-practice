#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int main(){
    int n;
    long long res = LONG_LONG_MAX;
    cin >> n;
    vector<int> A(n + 1);
    for(int i = 1; i <= n; ++i) cin >> A[i];

    //Without An
    vector<long long> v1(n + 1);
    v1[n] = LONG_LONG_MAX;
    v1[n - 1] = A[n - 1];
    for(int i = n - 2; i > 0 ; i --){
        v1[i] = min(A[i] + v1[i + 2], A[i] + v1[i + 1]);
    }

    //With An
    vector<long long> v2(n + 1);
    v2[n] = A[n];
    v2[n - 1] = A[n] + A[n - 1];
    for(int i = n - 2; i > 1; i --){
        v2[i] = min(A[i] + v2[i + 2], A[i] + v2[i + 1]);
    }
    v2[2] = min(v2[2], v2[3] + A[1]);
    res = min(v1[1], v2[2]);
    cout << res;
}