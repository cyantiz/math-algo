#include <iostream>
using namespace std;

typedef unsigned long long ull;

ull gcd(ull a, ull b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}
ull lcm(ull a, ull b) {
    return (a * b) / (gcd(a, b));
}

int main() {
    cout << gcd(20, 16) << endl;
    cout << lcm(20, 16) << endl;
}