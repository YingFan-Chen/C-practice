#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#endif
using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> front(n + 1, 0), reer(n + 1, 0);
    for(int i = 0; i < q; i ++){
        int a, x, y;
        cin >> a;
        if(a == 1){
            cin >> x >> y;
            reer[x] = y;
            front[y] = x;
        }else if(a == 2){
            cin >> x >> y;
            reer[x] = 0;
            front[y] = 0;
        }else{
            cin >> x;
            vector<int> tmp;
            int index = x;
            while(index != 0){
                tmp.push_back(index);
                index = front[index];
            }
            reverse(tmp.begin(), tmp.end());
            index = reer[x];
            while(index != 0){
                tmp.push_back(index);
                index = reer[index];
            }
            cout << tmp.size() << " ";
            for(auto i : tmp){
                cout << i << " ";
            }
            cout << endl;
        }
    }
}