#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <climits>
using namespace std;
/*int findMin(unordered_map<int, int> m){
    int min = INT_MAX;
    for(auto &i : m){
        if(min > i.second) min = i.second;
    }
    return min;
}*/


int main(){
    int n, q;
    cin >> n;
    vector<int> a(n), b(n);
    unordered_map<int, int> m2;
    unordered_set<int> s1;
    set<int> s2;
    vector<pair<int, int>> range(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) cin >> b[i];
    
    for(int i = n - 1; i >= 0; --i) m2[b[i]] = i;
    s2.insert(INT_MAX);
    for(auto i : m2) s2.insert(i.second);
    
    s1.insert(a[0]);
    int l, r;
    if(m2.find(a[0]) == m2.end()) l = n;
    else{
        l = m2[a[0]];
        /*m2.erase(a[0]);*/
        s2.erase(m2[a[0]]);
    }
    r = *s2.begin() - 1;
    range[0] = {l, r};

    for(int i = 1; i < n; ++ i){
        if(s1.find(a[i]) != s1.end()) range[i] = range[i - 1];
        else{
            s1.insert(a[i]);
            if(m2.find(a[i]) == m2.end()){
                l = n;
                r = range[i - 1].second;
            }else{
                if(m2[a[i]] - 1 == range[i - 1].second){
                    l = max(m2[a[i]], range[i - 1].first);
                    /*m2.erase(a[i]);*/
                    s2.erase(m2[a[i]]);
                    r = *s2.begin() - 1;
                }else{
                    l = max(m2[a[i]], range[i - 1].first);
                    /*m2.erase(a[i]);*/
                    s2.erase(m2[a[i]]);
                    r = range[i - 1].second;
                }
            }
            range[i] = {l, r};
        }
    }

    cin >> q;
    for(int i = 0; i < q; ++i){
        int x, y;
        cin >> x >> y;
        if(range[x - 1].first <= y - 1 && range[x -1].second >= y - 1) cout << "Yes\n";
        else cout << "No\n";
    } 
}