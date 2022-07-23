#include <iostream>
#include <math.h>
using namespace std;

typedef unsigned long long ull; 

bool *eratosthenesSieve(ull n)
{
    bool *isPrime = new bool[n + 1];
    for (ull i = 2; i <= n; i++) {
        isPrime[i] = true;
    }
    for (ull i = 2; i <= n; i++) {
        if (isPrime[i] == true) {
            for (ull j = 2 * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

int *calcExponent(ull n, bool *primeArr) {
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
        while (n % i == 0) {
            n /= i;
            exponent[i]++;
        }
    }
    return exponent;
}

ull phi(ull n)
{
    bool *prime = eratosthenesSieve(n);      // sang nguyen to
    int *exponent = calcExponent(n, prime); // luu so mu~ cua prime
    if (prime[n])
        return n - 1;
    ull res = 1;
    for (int i = 2; i <= n; i++) {
        if (exponent[i] != 0) {
            res *= pow(i, exponent[i] - 1) * (i - 1);
        }
    }
    return res;
}

ull ModPow(ull a, ull b, ull m) {
    if(b == 0)
        return 1 % m;
    ull u = ModPow(a, b / 2, m);
    u = (u * u) % m;
    if(b % 2 == 1) {
        u = (u * a) % m;
    }
    return u;
}

ull ModInverse(ull x, ull m) {
    return ModPow(x, phi(m) - 1, m);
}

void ChineseRemainder(ull n, ull* a, ull* m) {
    ull res = 0, _X = 1;
    for (ull k = 0; k < n; k++) {
        _X *= m[k];
    }
    for (ull k = 0; k < n; k++) {
        // Calc Xk
        ull Xk = _X / m[k];
        // Calc Result
        res += a[k] * Xk * ModInverse(Xk, m[k]);
    } 
    res = res % _X;
    cout << "Ket qua: x === " << res << " (mod " << _X << ")" << endl;
}
int main() {
    ull n;
    cout << "n = ";
    cin >> n;
    ull a[n], m[n];
    for (ull i = 0; i < n; i++) {
        printf("a[%lld] = ", i);
        cin >> a[i];
        printf("m[%lld] = ", i);
        cin >> m[i];
    }
    ChineseRemainder(n, a, m);
}