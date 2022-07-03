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
    vector<vector<char>> A(n, vector<char> (n , 0));
    for(int i = 0; i < n; i ++){
        string tmp;
        cin >> tmp;
        for(int j = 0; j < n; j ++){
            A[i][j] = tmp[j];
        }
    }
    string maxi ;
    for(int x = 0; x < n; x ++){
        for(int y = 0; y < n; y ++){
            for(int i = -1; i <= 1; i ++){
                for(int j = -1; j <= 1; j ++){
                    if(i != 0 or j != 0){
                        string tmp;
                        int tmpx = x, tmpy = y;
                        for(int z = 0; z < n; z ++){
                            tmp += A[tmpx][tmpy];
                            tmpx = (tmpx + i + n) % n;
                            tmpy = (tmpy + j + n) % n;
                        }
                        maxi = max(maxi, tmp);
                    }
                }
            }
        }
    }
    cout << maxi << endl;
}
