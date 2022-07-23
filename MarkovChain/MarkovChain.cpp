#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define R 3 // Number of Rows in the Matrix
#define C 3 // Number of Columns in the Matrix

// Function to multiply two matrices
double** mulMat(double *m1[C], double *m2[C]) {
    double** res;
    res = new double *[R];
    for (int i = 0; i < R; i++) {
        res[i] = new double[C];
        for (int j = 0; j < C; j++) {
            res[i][j] = 0;
            for (int k = 0; k < R; k++)
                res[i][j] += m1[i][k] * m2[k][j];
        }
    }
    return res;
}

// Function to power the matrix
double** powMat(double *m[C], int exponent) {
    double **res= m;
    while (--exponent) {
        res = mulMat(res, m);
    }
    return res;
}

int main() {
    double **p = new double *[R];
    int t = 0;
    ifstream fin("input.txt");
    for (int i = 0; i < R ; i++) {
        p[i] = new double[C];
        for (int j = 0; j < C; j++)
            fin >> p[i][j];
        fin.ignore();
    }
    cout << "At time t + ?: ";
    cin >> t;

    double **res = powMat(p, t);
    
    cout << "The transition matrix at time t + " << t << ": " << endl;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++) 
            cout << setw(15) << res[i][j];
        cout << endl;
    }
}
