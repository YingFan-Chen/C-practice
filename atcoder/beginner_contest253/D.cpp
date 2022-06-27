#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b){
    if(b > a) swap(a, b);
    while(a % b != 0){
        a = a % b;
        swap(a, b);
    }
    return b; 
}
int main(){
    long long n, a, b;
    long long sum1, sum2, sum3, sum4;
    cin >> n >> a >> b;
    sum1 = (1 + n) * n / 2;
    long long tmp;
    tmp = n / a;
    sum2 = (a + a * tmp) * tmp / 2;
    tmp = n / b; 
    sum3 = (b + b * tmp) * tmp / 2;
    long long k = a * b / gcd(a, b);
    tmp = n / k;
    sum4 = (k + k * tmp) * tmp / 2;
    sum1 = sum1 - sum2 - sum3 + sum4;
    cout << sum1;
}