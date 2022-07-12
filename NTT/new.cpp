#include <bits/stdc++.h>
#include "schonhage.c"
using namespace std;

int main(){
    int16_t p1[8] = {1,2,3,4,-1,-2,-3,-4};
    int16_t p2[8] = {1,2,3,4,-1,-2,-3,-4};
    int16_t p3[8] = {1,2,3,4,-1,-2,-3,-4};
    int16_t C[8];
    memset(C, 0, sizeof(C));
    makeC(2, C);

    schonhage(2, 4, p1, p2, p3, C);
}