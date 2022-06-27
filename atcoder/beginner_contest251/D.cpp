#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
int main(){
    int w;
    cin >> w;
    vector<int> v1;
    unordered_set<int> v2,v3;
    /*vector<bool> table;
    table.assign(w + 1, false);
    for(int i = 1; i <= w; ++i){
        if(table[i] == false){
            table[i] = true;
            unordered_set<int> tmp2 = v2;
            for(int j : v1){
                int tmp = i + j;
                if(tmp <= w){
                    v2.insert(tmp);
                    table[tmp] = true;
                }else break;
            }
            for(int j : tmp2){
                int tmp = i + j;
                if(tmp <= w){
                    v3.insert(tmp);
                    table[tmp] = true;
                }else break;
            }
            v1.push_back(i);
        }
    }*/
    /*this is a fantasy solution, ans is independent on input*/
    for(int i = 1; i < 100; ++i){
        v1.push_back(i);
        v1.push_back(i * 100);
        v1.push_back(i * 10000);
    }

    cout << v1.size() << "\n";
    for(int i : v1) cout << i << " "; 
}