#include <iostream>
#include <string>
using namespace std;
int main(){
    string s, ans = "";
    cin >> s;
    int n = s.length();
    for(int i = 0; i < 6; ++i){
        ans = ans + s[i % n];
    }
    cout << ans;
}