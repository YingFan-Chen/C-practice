#include <bits/stdc++.h>
#define ll long long
#define ll_max LONG_LONG_MAX
#ifndef ONLINE_JUDGE
#include "C:\Users\josep\code\c++\lib\debug"
#endif
using namespace std;

int main(){
    double a, b, c;
    cin >> a >> b >> c;
    double r2 = pow(a * a + b * b, 0.5);
    if(r2 == 0){
        cout << (double) 0 << " " << (double) 0 << endl;
        return 0;
    }

    double tmp = 0;
    if(a >= 0 and b >= 0) tmp = atan(b / a);
    else if(a >= 0 and b <= 0) tmp = - atan(-b / a);
    else if(a <= 0 and b <= 0) tmp = M_PI + atan(b / a);
    else if(a <= 0 and b >= 0) tmp = M_PI - atan(b / -a);

    double x = cos(tmp + c / 360 * 2 * M_PI) * r2;
    double y = sin(tmp + c / 360 * 2 * M_PI) * r2;
    printf("%.7f %.7f", x, y);
}   