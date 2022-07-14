#include <bits/stdc++.h>
#include "schonhage.c"
using namespace std;

int main(){
    int16_t p1[512];
    int16_t p2[512];
    int16_t p3[512];
    memset(p3, 0, sizeof(p3));

    



    Schonhage_Multiple(16, 32, p1, p2, p3);
    for(int i = 0; i < 8; ++ i) cout << p3[i] << " ";
}