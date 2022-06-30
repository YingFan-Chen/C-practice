#include <bits/stdc++.h>
using namespace std;
int main(){
    string prefix = "./test < ./case/testcase";
    system("make test");
    system("make createtestcase");
    system("./createtestcase");
    for(int i = 0; i <= 9; i ++){
        string command = prefix + (char) ('0' + i);
        system(command.c_str());
    }
}