#include "MathLib.h"

std::vector<std::vector<double>> Transpose(std::vector<std::vector<double>> mat) {
	std::vector<std::vector<double>> trans_vec(mat[0].size(), std::vector<double>());

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			trans_vec[j].push_back(mat[i][j]);
		}
	}

	return trans_vec;
}

std::vector<std::vector<double>> MatMult(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B) {
	std::vector<std::vector<double>> result_mat;

	result_mat.resize(A.size());
	for (auto it = result_mat.begin(); it != result_mat.end(); ++it) {
		it->resize(B[0].size());
	}

	for (int i = 0; i < result_mat.size(); ++i) {
		for (int j = 0; j < result_mat[0].size(); ++j) {
			double val = 0.0f;
			for (int k = 0; k < A[0].size(); k++) {
				val += (A[i][k] * B[k][j]);
			}
			result_mat[i][j] = double(val);
		}
	}

	return result_mat;
}
std::vector<double> MatVecMult(std::vector<std::vector<double>> A, std::vector<double> B) {
	std::vector<double> result_mat;

	for (int i = 0; i < A.size(); i++) {
		double val = 0.0;
		for (int j = 0; j < B.size(); j++) {
			val += A[i][j] * B[j];
		}
		result_mat.push_back(val);
	}

	return result_mat;
}
std::vector<double> VecSub(std::vector<double> A, std::vector<double> B) {
	std::vector<double> result_mat;

	for (int i = 0; i < A.size(); i++) {
		result_mat.push_back(A[i] - B[i]);
	}

	return result_mat;
}
std::vector<double> VecAdd(std::vector<double> A, std::vector<double> B) {
	std::vector<double> result_mat;

	for (int i = 0; i < A.size(); i++) {
		result_mat.push_back(A[i] + B[i]);
	}

	return result_mat;
}
std::vector<std::vector<double>> MatScalarMult(std::vector<std::vector<double>> mat, double scalar) {
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			mat[i][j] *= scalar;
		}
	}
	return mat;
}
std::vector<double> LinearSolve(std::vector<std::vector<double>> a, std::vector<double> b) {
	int N = a.size();
	std::vector<double> x(a.size());
	std::fill(x.begin(), x.end(), 0);
	for (int i = 0; i < a.size(); i++) {
		a[i].push_back(b[i]);
	}
	// Applying Gauss Elimination to find the elements of diagonal matrix
	int i, j, k;
	for (j = 0; j < N - 1; j++)
	{
		for (i = j + 1; i < N; i++)
		{
			double temp = a[i][j] / a[j][j];

			for (k = 0; k < N + 1; k++)
				a[i][k] -= a[j][k] * temp;
		}
	}

	for (i = N - 1; i >= 0; i--)
	{
		double s = 0;
		for (j = i + 1; j < N; j++)
			s += a[i][j] * x[j];
		x[i] = (a[i][N] - s) / a[i][i];
	}
	return x;
}
