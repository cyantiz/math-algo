#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

const int MAX = 100;

bool isSymmetricMatrix(int matrix[][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(matrix[i][j] != matrix[j][i])
                return false;
        }
    }
    return true;
}

void Cholesky(int matrix[][MAX], int n) {
	double L[n][n];
	memset(L, 0, sizeof(L));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			double temp = 0;

			if (i == j) {
				for (int k = 0; k < j; k++)
					temp += pow(L[j][k], 2);
				L[j][j] = sqrt(matrix[j][j] - temp);
			} else {
				for (int k = 0; k < j; k++)
					temp += (L[i][k] * L[j][k]);
				L[i][j] = (matrix[i][j] - temp) / L[j][j];
			}
		}
	}

	cout << setw(8) << " L"
		<< setw(55) << "LT" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << setw(8) << L[i][j] << "\t";
		cout << "\t";
		
		for (int j = 0; j < n; j++)
			cout << setw(8) << L[j][i] << "\t";
		cout << endl;
	}
}

int main() {
	int n;
	cout << "n = ";
    cin >> n;
    int A[MAX][MAX];
    for (int i = 0;i < n; i++) {
        for (int j = 0;j < n; j++) {
            cout << "A[" << i << "," << j << "] = ";
            cin >> A[i][j];
        }
    }
    if(isSymmetricMatrix(A, n)) {
        Cholesky(A, n);
    }
    else {
        printf("Not a Symmetric Matrix\n");
    }
    return 0;
}
