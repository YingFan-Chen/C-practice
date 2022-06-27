#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

struct segment_tree{
public :
    vector<ll> v, flag;
    segment_tree(int n){
        v.assign(n << 2, 0);
        flag.assign(n << 2, 0);
    } 
    void pull(int index){
        v[index] = v[index << 1] + v[index << 1 | 1];
        return ;
    }
    void push(int index, int l, int r){
        if(flag[index]){
            int mid = (l + r) >> 1;
            v[index << 1] += flag[index] * (mid - l + 1);
            v[index << 1 | 1] += flag[index] * (r - mid);
            flag[index << 1] += flag[index];
            flag[index << 1 | 1] += flag[index];
            flag[index] = 0;
        }
        return ;
    }
    void add(int index, int l, int r, int targetl, int targetr, ll val){
        if(l >= targetl and r <= targetr){
            v[index] += val * (r - l + 1);
            flag[index] += val; 
        }else{
            int mid = (l + r) >> 1;
            push(index, l, r);
            if(mid >= targetl) add(index << 1, l , mid, targetl, targetr, val);
            if(mid < targetr) add(index << 1 | 1, mid + 1, r, targetl, targetr, val);
            pull(index);
        }
        return ;
    }
    ll query(int index, int l, int r, int target){
        if(l == r) return v[index];
        else{
            push(index, l, r);
            int mid = (l + r) >> 1;
            ll res;
            if(target <= mid) res = query(index << 1, l, mid, target);
            else res = query(index << 1 | 1, mid + 1, r, target);
            return res;
        }
    }
};

int main(){
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> query(q + 1, vector<int> (4, 0));
    vector<int> tmp(n + 1, 0);
    vector<pair<int, ll>> event;
    for(int i = 1; i <= q; i ++){
        cin >> query[i][0];
        if(query[i][0] == 1){
            cin >> query[i][1] >> query[i][2] >> query[i][3];
        }else if(query[i][0] == 2){
            cin >> query[i][1] >> query[i][2];
            tmp[query[i][1]] = i;
        }else{
            cin >> query[i][1] >> query[i][2];
            if(tmp[query[i][1]]) event.push_back({tmp[query[i][1]], query[i][2]});
        }
    }
    sort(event.begin(), event.end());
    map<pair<int, int>, pair<ll, ll>> mapping;
    segment_tree st(m);
    int j = 0;
    for(int i = 1; i <= q; i ++){
        if(query[i][0] == 2){
            while(j < event.size() and i == event[j].first){
                ll val = st.query(1, 1, m, event[j].second);
                mapping[{query[i][1], event[j].second}] = {query[i][2], val};
                j++ ;
            }
        }else{
            if(query[i][0] == 1){
                st.add(1, 1, m, query[i][1], query[i][2], query[i][3]);
            }else{
                ll res = st.query(1, 1, m, query[i][2]);
                if(mapping.find({query[i][1], query[i][2]}) == mapping.end()){
                    cout << res << endl;
                }else{
                    auto [a, b] = mapping[{query[i][1], query[i][2]}];
                    res += a - b;
                    cout << res << endl;
                }
            }
        }
    }
}