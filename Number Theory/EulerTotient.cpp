#include <iostream>
#include <math.h>
using namespace std;

typedef unsigned long long ull;

bool* eratosthenesSieve(ull n) {
    bool *isPrime = new bool[n+1];
    for (ull i = 2; i <= n; i++) {
        isPrime[i] = true;
    }
    for (ull i = 2; i <= n; i++) {
        if (isPrime[i] == true) {
            for (ull j = 2 * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

int* countExponent(ull n, bool* primeArr) {
    int *exponent = new int[n + 1];
    for (int i = 2; i <= n; i++) {
        exponent[i] = 0;
    }
    ull i = 1;
    while (n > 1) {
        i++;
        if (!primeArr[i]) {
            continue;
        }
        while(n % i == 0) {
            n /= i;
            exponent[i]++;
        }
    }
    return exponent;
}

ull eulerTotient(ull n) {
    bool *prime = eratosthenesSieve(n); //sang nguyen to
    int *exponent = countExponent(n, prime); //luu so mu~ cua prime
    if(prime[n])
        return n - 1;
    ull res = 1;
    for (int i = 2; i <= n; i++) {
        if(exponent[i] != 0) {
            res *= pow(i, exponent[i] - 1) * (i - 1);
        }
    }
    return res;
}

int main() {
    ull n;
    cout << "input n = ";
    cin >> n;

    cout << "phi(" << n << ") = " << eulerTotient(n);
}