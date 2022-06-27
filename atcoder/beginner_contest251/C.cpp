#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
int main(){
    int n;
    cin >> n;
    unordered_set<string> set1;
    int max = 0, index = 0, t;
    string s;
    for(int i = 1; i <= n; ++i){
        cin >> s >> t;
        if(set1.find(s) == set1.end()){
            if(t > max){
                max = t;
                index = i;
            }
            set1.insert(s);
        }
    }
    cout << index;
}