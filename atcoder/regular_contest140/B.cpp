#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n;
    string s;
    cin >> n;
    cin >> s;
    map<int, int> m;
    for(int i = 0; i < n; ++i){
        if(s[i] == 'R'){
            int l = i - 1, r = i + 1;
            int count = 0;
            while(l >= 0 && r < n){
                if(s[l] == 'A' && s[r] == 'C'){
                    ++ count;
                    -- l;
                    ++ r;
                }else break;
            }
            if(count > 0){
                if(m.find(count) == m.end()) m[count] = 1;
                else m[count]++;
            }           
        }
    }
    //for(auto &i : m) cout << i.first << " " << i.second << "\n";
    int k = 1;
    while(!m.empty()){
        if(k % 2){
            int tmp = m.rbegin()->first - 1;
            m.rbegin()->second --;
            if(m.rbegin()->second == 0) m.erase(m.rbegin()->first);
            if(tmp > 0){
                if(m.find(tmp) == m.end()){
                    m[tmp] = 1;
                }else m[tmp] ++;
            }
            
        }else{
            m.begin()->second --;
            if(m.begin()->second == 0) m.erase(m.begin()->first);
        }
        ++ k;
    }
    cout << k - 1;
}