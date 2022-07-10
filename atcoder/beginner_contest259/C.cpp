#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    bool res = true;
    string s, t;
    cin >> s >> t;
    if(s.size() > t.size()){
        cout << "No" << endl;
    }else{
        vector<pair<char, int>> v;
        char pre = t[0];
        int count = 1;
        for(int i = 1; i < t.size(); i ++){
            if(t[i] == pre) count ++;
            else{
                v.push_back({pre, count});
                count = 1;
                pre = t[i];
            } 
        }
        v.push_back({pre, count});
        
        pre = s[0];
        count = 1;
        int j = 0;
        for(int i = 1; i < s.size(); i ++){
            if(s[i] == pre) count ++;
            else{
                if(pre == v[j].first){
                    if(count > v[j].second){
                        res = false;
                        break;
                    }else if(count == v[j].second){
                        
                    }else{
                        if(count < 2){
                            res = false;
                            break;
                        }
                    }
                    j ++;
                    count = 1;
                    pre = s[i];
                }else{
                   res = false;
                   break; 
                }
            }
        }
        if(pre == v[j].first){
            if(count > v[j].second){
                res = false;
            }else if(count == v[j].second){
                
            }else{
                if(count < 2){
                    res = false;
                }
            }
            j ++;
        }else res = false;
        if(res and j == v.size()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}