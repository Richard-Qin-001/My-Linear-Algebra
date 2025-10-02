#ifndef MATRIX_OPTIONS_BASE_H
#define MATRIX_OPTIONS_BASE_H

# include <iostream>
# include <vector>


// --- I/O 接口 ---
std::vector<std::vector<double>> input_matrix(size_t n, size_t m);
void print_matrix(const std::vector<std::vector<double>>& matrix);

// --- 核心操作接口 ---
// Permutation (用于行交换)
void Permutation(size_t i, size_t j, std::vector<std::vector<double>>& matrix);

// Elimination (高斯消元)
void Gauss_Elimination(std::vector<std::vector<double>>& matrix);
int gauss_forward_elimination(std::vector<std::vector<double>>& matrix);

// Matrix Multiply
std::vector<std::vector<double>> matrix_multiply(
    const std::vector<std::vector<double>>& m_1, 
    const std::vector<std::vector<double>>& m_2);

// Matrix Transpose
std::vector<std::vector<double>> matrix_transpose(const std::vector<std::vector<double>>& matrix);

// Determinant Calculation
double calculate_determinant_leibniz(const std::vector<std::vector<double>>& matrix);
long double calculate_determinant_gauss(const std::vector<std::vector<double>>& matrix);

#endif