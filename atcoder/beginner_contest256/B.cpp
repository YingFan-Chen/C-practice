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
    vector<int> s(n);
    for(int i = 0; i < n; i++) cin >> s[i];
    int count = 0;
    vector<int> square(4, 0);
    for(int i = 0; i < n; i++){
        square[0] = 1;
        for(int j = 3; j >= 0; j--){
            if(square[j] == 1){
                if(j + s[i] > 3){
                    count ++;
                    square[j] = 0;
                }else{
                    square[j + s[i]] = 1;
                    square[j] = 0;
                }
            }
        }
    }
    cout << count;
}