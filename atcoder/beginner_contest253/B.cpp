#include <bits/stdc++.h>
using namespace std;
int main(){
    int h, w;
    cin >> h >> w;
    vector<string> v(h);
    for(int i = 0; i < h; ++i){
        cin >> v[i];
    }
    pair<int, int> p1, p2;
    int flag = 0;
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            if(v[i][j] == 'o'){
                if(flag == 0){
                    p1 = {i, j};
                    flag = 1;
                }else{
                    p2 = {i, j};
                    break;
                }
            }
        }
    }
    int res = abs(p1.first - p2.first) + abs(p1.second - p2.second);
    cout << res;
}