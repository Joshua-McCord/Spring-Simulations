#pragma once
#ifndef MATH_LIB_H
#define MATH_LIB_H
#include <vector>

std::vector<std::vector<double>> Transpose(std::vector<std::vector<double>> mat);
std::vector<std::vector<double>> MatMult(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B);
std::vector<double> MatVecMult(std::vector<std::vector<double>> A, std::vector<double> B);
std::vector<double> VecSub(std::vector<double> A, std::vector<double> B);
std::vector<double> VecAdd(std::vector<double> A, std::vector<double> B);
std::vector<std::vector<double>> MatScalarMult(std::vector<std::vector<double>> mat, double scalar);
std::vector<double> LinearSolve(std::vector<std::vector<double>> a, std::vector<double> b);

#endif // !MATH_LIB_H