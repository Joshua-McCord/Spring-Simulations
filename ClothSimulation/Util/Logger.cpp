#include "Logger.h"
#include <vector>
#include <string>
#include <iostream>

void Logger::PrintMatrix(std::vector<std::vector<double>> mat, std::string name) {
	std::cout << name << " = " << std::endl;
	std::cout << "[";
	for (int i = 0; i < mat.size(); ++i) {
		std::cout << "[";
		for (int j = 0; j < mat[0].size(); ++j) {
			std::cout << mat[i][j];
			if (j != mat[0].size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]";
		if (i != mat.size() - 1) {
			std::cout << ",\n";
		}
	}
	std::cout << "]" << std::endl;
}
void Logger::PrintVector(std::vector<double> vec, std::string name) {
	std::cout << name << " = " << std::endl;
	std::cout << "[";
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if (i != vec.size() - 1) {
			std::cout << " , ";
		}
	}
	std::cout << "]" << std::endl;
}