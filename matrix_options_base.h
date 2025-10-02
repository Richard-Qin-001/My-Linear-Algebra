#ifndef MATRIX_OPTIONS_BASE_H
#define MATRIX_OPTIONS_BASE_H

# include <iostream>
# include <vector>


// --- I/O 接口 ---
std::vector<std::vector<double>> input_matrix(int n, int m);
void print_matrix(int n, int p, const std::vector<std::vector<double>>& matrix);

// --- 核心操作接口 ---
// Permutation (用于行交换)
void Permutation(int i, int j, int n, int m, std::vector<std::vector<double>>& matrix);

// Elimination (高斯消元)
void Elimination(int n, int m, std::vector<std::vector<double>>& matrix);

// Matrix Multiply
std::vector<std::vector<double>> matrix_multiply(
    const std::vector<std::vector<double>>& m_1, 
    const std::vector<std::vector<double>>& m_2, 
    int n, int m, int p);

// Matrix Transpose
std::vector<std::vector<double>> matrix_transpose(
    const std::vector<std::vector<double>>& matrix, 
    int n, int m);

// Determinant Calculation
double calculate_determinant(const std::vector<std::vector<double>>& matrix);

#endif