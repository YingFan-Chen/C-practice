#pragma once
#include <bits/stdc++.h>
#include "../debug"
#include "../data_structure"
#include "../algorithm"
using namespace std;

#ifndef _OLD_DRIVER_TREE
#define _OLD_DRIVER_TREE
class old_driver_tree{
    public :
        class ODT_Node{
            public : 
                ll left, right;
                mutable ll val;
                ODT_Node(ll _left, ll _right, ll _val) : left(_left), right(_right), val(_val){}
                inline bool operator< (const ODT_Node &x) const{
                    return left < x.left;
                }
        };

        set<ODT_Node> s;
        old_driver_tree(ll minimum, ll maximum, ll initial_val){
            s.insert(ODT_Node{minimum, maximum, initial_val});
        }

        auto split(ll x){
            auto iter = -- s.upper_bound(ODT_Node{x, 0, 0});
            if(iter->left == x) return iter;
            ll left = iter->left, right = iter->right, val = iter->val;
            s.erase(iter);
            s.insert(ODT_Node{left, x - 1, val});
            return s.insert(ODT_Node{x, right, val}).first;
        }

        void assign(ll left, ll right, ll val){
            //Note : right first
            auto iterl = split(right + 1), iterr = split(left);
            s.erase(iterl, iterr);
            s.insert(ODT_Node{left, right, val});
        }

        /*Template
        void operation(ll left, ll right, ll val){
            auto iterl = split(right + 1), iterr = split(left);
            for(; iterl != iterr; iterl ++){

            }
        }*/
};
#endif

int main(){
    
}