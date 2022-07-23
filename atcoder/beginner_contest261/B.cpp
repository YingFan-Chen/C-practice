#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> A(n);
    for(int i = 0; i < n; i ++) cin >> A[i];
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(A[i][j] == 'D' and A[j][i] != 'D'){
                cout << "incorrect" << endl;
                return 0;
            }
            if(A[i][j] == 'W' and A[j][i] != 'L'){
                cout << "incorrect" << endl;
                return 0;
            }
            if(A[i][j] == 'L' and A[j][i] != 'W'){
                cout << "incorrect" << endl;
                return 0;
            }
        }
    }
    cout << "correct" << endl;
}