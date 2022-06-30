#include <bits/stdc++.h>
using namespace std;

void casecreate(FILE* fp){
    int x;
    string s;
    for(int i = 0; i < 4; i ++){
        x = rand();
        s += (char) (x % 26 + 'a');
    }
    s += "\n";
    for(int i = 0; i < 100000; i ++){
        x = rand();
        s += (char) (x % 26 + 'a');
    }
    fwrite(s.c_str(), 1, s.size(), fp);
}

int main(){
    string prefix = "./case/testcase";
    srand(time(NULL));
    for(int i = 0; i < 10; i ++){
        string pathname = prefix + (char) ('0' + i);
        FILE* fp = fopen(pathname.c_str(), "w");
        casecreate(fp);
        fclose(fp);
    }
}