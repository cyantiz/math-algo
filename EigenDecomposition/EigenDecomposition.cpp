#include <iostream>
#include <Eigen/Dense>
using namespace std;
using Eigen::MatrixXd;
void getCofactor(double matrix[100][100], double cofactorMatrix[100][100], int p, int q, int n);
void displayMatrix(double matrix[100][100], int n);
double determinant(double matrix[100][100], int n);
void adjoint(double matrix[100][100], double adj[100][100], int n);
bool inverse(double matrix[100][100], double inverse[100][100], int n);
int main()
{
	// For square matrix only
	int size;
	cin >> size;
	MatrixXd m(size, size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int value;
			cin >> value;
			m(i, j) = value;
		}
	}
	// Step 1: Calculate eigen values
	Eigen::EigenSolver<MatrixXd> es(m);
	cout << "Eigen Values: " << endl;
	cout << es.pseudoEigenvalueMatrix() << endl;
	// Step 2: Calculate eigen vectors

	cout << "Eigen Vectors: " << endl;
	MatrixXd eigenVectors = es.pseudoEigenvectors();
	MatrixXd usedMatrix = eigenVectors.inverse();

	double usedMatrix1[100][100];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			usedMatrix1[i][j] = eigenVectors(i, j);
		}
	}
	displayMatrix(usedMatrix1, size);
	// Step 3 : Calculate Inverse Matrix of Eigen Values Matrix
	double inverseMatrix[100][100];
	cout << "Inverse Matrix:" << endl;
	if (inverse(usedMatrix1, inverseMatrix, size))
	{
		cout << usedMatrix << endl;
	}
}
void getCofactor(double matrix[100][100], double cofactorMatrix[100][100], int p, int q, int size)
{
	int i = 0, j = 0;

	// Looping for each element of the matrix
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			//  Copying into temporary matrix only those element
			//  which are not in given row and column
			if (row != p && col != q)
			{
				cofactorMatrix[i][j++] = matrix[row][col];

				// Row is filled, so increase row index and
				// reset col index
				if (j == size - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}
double determinant(double matrix[100][100], int size)
{
	double D = 0; // Initialize result

	//  Base case : if matrix contains single element
	if (size == 1)
		return matrix[0][0];

	double temp[100][100]; // To store cofactors

	int sign = 1; // To store sign multiplier

	// Iterate for each element of first row
	for (int f = 0; f < size; f++)
	{
		// Getting Cofactor of A[0][f]
		getCofactor(matrix, temp, 0, f, size);
		D += sign * matrix[0][f] * determinant(temp, size - 1);

		// terms are to be added with alternate sign
		sign = -sign;
	}

	return D;
}
void adjoint(double matrix[100][100], double adj[100][100], int size)
{
	if (size == 1)
	{
		adj[0][0] = 1;
		return;
	}

	// temp is used to store cofactors of A[][]
	int sign = 1;
	double temp[100][100];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Get cofactor of A[i][j]
			getCofactor(matrix, temp, i, j, size);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adj[j][i] = (sign) * (determinant(temp, size - 1));
		}
	}
}
bool inverse(double matrix[100][100], double inverse[100][100], int size)
{
	// Find determinant of A[][]
	int det = determinant(matrix, size);
	if (det == 0)
	{
		cout << "Singular matrix, can't find its inverse";
		return false;
	}

	// Find adjoint
	double adj[100][100];
	adjoint(matrix, adj, size);

	// Find Inverse using formula "inverse(A) = adj(A)/det(A)"
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			inverse[i][j] = adj[i][j] / float(det);

	return true;
}
void displayMatrix(double matrix[100][100], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}