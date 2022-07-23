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

int* calctExponent(ull n, bool* isPrime) {
    int *exponent = new int[n + 1];
    for (int i = 2; i <= n; i++) {
        exponent[i] = 0;
    }
    ull i = 1;
    while (n > 1) {
        i++;
        if (!isPrime[i])
            continue;
        while(n % i == 0) {
            n /= i;
            exponent[i]++;
        }
    }
    return exponent;
}

ull numberOfFactors(ull n, int* exponentArr) {
    ull res = 1;
    for (ull i = 2; i <= n; i++) {
        res *= (exponentArr[i] + 1);
    }
    return res;
}

ull sumOfFactors(ull n, int* exponentArr) {
    ull res = 1;
    for (ull i = 0; i <= n; i++)
    {
        if(exponentArr[i]) {
            res *= (pow(i, exponentArr[i] + 1) - 1) / (i - 1);
        }
    }
    return res;
}

ull productOfFactors(ull n, int* exponentArr) {
    return (ull)pow(n, ((long double)numberOfFactors(n, exponentArr)) / 2);
}

bool isPerfectNumber(ull n, int* exponentArr) {
    return (sumOfFactors(n, exponentArr) - n == n);
}

int main() {
    ull n;
    cout << "input n = ";
    cin >> n;
    bool *prime = eratosthenesSieve(n); //sang nguyen to
    int *exponent = calctExponent(n, prime); //luu so mu~ cua prime

    cout << "Number of factors: " << numberOfFactors(n, exponent) << endl
         << "Sum of factors: " << sumOfFactors(n, exponent) << endl
         << "Product of factors: " << productOfFactors(n, exponent) << endl
         << "Is a perfect number: " << boolalpha << isPerfectNumber(n, exponent);
}