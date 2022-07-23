#include <iostream>
using namespace std;

typedef unsigned long long ull;

bool isPrime(ull n) {
    if(n < 2) return false;
    for (ull x = 2; x*x <= n; x++) {
        if(n % x == 0) return false;
    }
    return true;
}

int main() {
    cout << boolalpha << isPrime(29);
}