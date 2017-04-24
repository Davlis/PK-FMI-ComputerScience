#include <iostream>
#include <vector> // vector

using namespace std;

void thomas(vector<vector<double>> &matrix);
void solve(vector<vector<double>> matrix, vector<double> &vector);
void print_vector(vector<double> vec);
void print_matrix(vector<vector<double>> matrix);

int main(void) {
	vector<vector<double>> matrix_A = {
		{    30.0, 2.0/3.0,       0.0,       0.0,       0.0,       0.0 },
		{ 3.0/4.0,    20.0,   5.0/6.0,       0.0,       0.0,       0.0 },
		{     0.0, 7.0/8.0,      10.0,  9.0/10.0,       0.0,       0.0 },
		{     0.0,     0.0, 11.0/12.0,      10.0, 13.0/14.0,       0.0 },
		{     0.0,     0.0,       0.0, 15.0/16.0,      20.0, 17.0/18.0 },
		{     0.0,     0.0,       0.0,       0.0, 19.0/20.0,      30.0 }
	};
	
	vector<double> vector_b = {
		   94.0/3.0,
		  173.0/4.0,
		  581.0/20.0,
		 -815.0/28.0,
		-6301.0/144.0,
		 -319.0/10.0
	};
	
	printf("\n\n");
	printf("  Matrix A\n");
	print_matrix(matrix_A);
	
	printf("  Vector b\n");
	print_vector(vector_b);
	
	thomas(matrix_A);
	printf("  Matrix after changes\n");
	print_matrix(matrix_A);
	
	solve(matrix_A, vector_b);
	printf("  Solution\n");
	print_vector(vector_b);

	return 0;
}

//https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm#Method

void thomas(vector<vector<double>> &matrix) {
	const int n = matrix.size();

	if(n != matrix.at(0).size()) {
		printf("The matrix must be square.");
		return;
	}
	
	matrix[0][1] /= matrix[0][0];
	for(int i = 1; i < n - 1; i++)
		matrix[i][i+1] /= matrix[i][i] - matrix[i][i-1] * matrix[i-1][i];
}

void solve(vector<vector<double>> matrix, vector<double> &vector) {
	const int n = matrix.size();
	
	if(n != matrix.at(0).size()) {
		printf("The matrix must be square.");
		return;
	}
	
	vector[0] /= matrix[0][0];
	for(int i = 1; i < n; i++)
		vector[i] = (vector[i] - matrix[i][i-1] * vector[i-1]) / (matrix[i][i] - matrix[i][i-1] * matrix[i-1][i]);
	
	for(int i = n-2; i >= 0; i--)
		vector[i] -= matrix[i][i+1] * vector[i+1];
}

void print_vector(vector<double> vec) {
	print_matrix(vector<vector<double>>({ vec }));
}

void print_matrix(vector<vector<double>> matrix) {
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