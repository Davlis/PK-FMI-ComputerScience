#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

vector<double> decomposition(vector<vector<double>> &matrix);
vector<double> solve(const vector<vector<double>> &matrix_LU, const vector<double> &vector_b, const vector<double> &permutation);
void print_vector(const vector<double> &vec);
void print_matrix(const vector<vector<double>> &matrix);

int main(void) {
	vector<vector<double>> matrix_A = {
		{  1,  20, -30, - 4 },
		{  4,  20, - 6,  50 },
		{  9, -18,  12, -11 },
		{ 16, -15,  14, 130 }
	};
	
	vector<double> vector_b = {
		0, 114, -5, 177 
	};
	
	printf("\n\n");
	printf("  Matrix A\n");
	print_matrix(matrix_A);
	
	printf("  Vector b\n");
	print_vector(vector_b);
	
	vector<double> perm = decomposition(matrix_A);
	printf("  Matrix after decomposition\n");
	print_matrix(matrix_A);
	
	printf("  Solution\n");
	print_vector(solve(matrix_A, vector_b, perm));
	
	return 0;
}

vector<double> decomposition(vector<vector<double>> &matrix) {
	if(matrix.size() != matrix.at(0).size()) {
		printf("The matrix must be square.");
		return vector<double>();
	}

	int n = matrix.size();
	double pivot, k_prime;
	vector<double> permutation = vector<double>(n);
	
	for(int i = 0; i < n; i++)
		permutation[i] = i;
		
	for(int k = 0; k < n; k++) {
		pivot = 0;
		
		for(int i = k; i < n; i++) {
			if(fabs(matrix[i][k]) > pivot) {
				pivot = fabs(matrix[i][k]);
				k_prime = i;
			}
		}
		
		if(pivot == 0) {
			printf("The matrix is singular.");
			return vector<double>();
		}
		
		swap(permutation[k], permutation[k_prime]);
		swap(matrix[k], matrix[k_prime]);
		
		for(int i = k + 1; i < n; i++) {
			matrix[i][k] /= matrix[k][k];
			
			for(int j = k + 1; j < n; j++)
				matrix[i][j] -= matrix[i][k] * matrix[k][j];
		}
	}
	
	return permutation;
}

vector<double> solve(const vector<vector<double>> &matrix_LU, const vector<double> &vector_b, const vector<double> &permutation) {
	double sum;
	const int n = matrix_LU.size();
	vector<double> vector_Y = vector<double>(n);
	vector<double> vector_X = vector<double>(n);
	
	for(int i = 0; i < n; i++) {
		sum = 0;
		for (int k = 0; k < i; k++)
			sum += matrix_LU[i][k] * vector_Y[k];
		vector_Y[i] = vector_b[permutation[i]] - sum;
	}
	
	for(int i = n - 1; i >= 0; i--) {
		sum = 0;
		for (int k = i + 1; k < n; k++)
			sum += matrix_LU[i][k] * vector_X[k];
		vector_X[i] = (vector_Y[i] - sum) / matrix_LU[i][i];
	}
	
	return vector_X;
}

void print_vector(const vector<double> &vec) {
	print_matrix(vector<vector<double>>({ vec }));
}

void print_matrix(const vector<vector<double>> &matrix) {
	printf("  /%*s\\", 9 * matrix.at(0).size(), " ");

	for(int i = 0; i < matrix.size(); i++) {
		printf("\n |");
		for(int j = 0; j < matrix[i].size(); j++) {
			printf("% 8.3f ", matrix[i][j]);
		}
		
		printf("  |");
	}
	
	printf("\n  \\%*s/\n\n", 9 * matrix.at(0).size(), " ");
}