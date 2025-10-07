#ifndef MATRIX_OPTIONS_BASE_H
#define MATRIX_OPTIONS_BASE_H

# include <iostream>
# include <vector>
# include <string>


// --- I/O 接口 ---
std::vector<std::vector<double>> input_matrix(size_t n, size_t m);
void print_matrix(const std::vector<std::vector<double>>& matrix);

// --- I/O - JSON 接口 ---
std::vector<std::vector<double>> read_matrix_from_json(const std::string& filepath);

// --- 核心操作接口 ---
// Permutation (用于行交换)
void Permutation(size_t i, size_t j, std::vector<std::vector<double>>& matrix);

// Elimination
void gauss_elimination(std::vector<std::vector<double>>& matrix);
int gauss_forward_elimination(std::vector<std::vector<double>>& matrix);
void gauss_jordan_elimination(std::vector<std::vector<double>>& matrix);

// Identity Matrix
std::vector<std::vector<double>> create_identity_matrix(size_t n);

// Inverse
std::vector<std::vector<double>> inverse(const std::vector<std::vector<double>>& matrix);

// Matrix Multiply
std::vector<std::vector<double>> matrix_multiply(
    const std::vector<std::vector<double>>& m_1, 
    const std::vector<std::vector<double>>& m_2);

// Matrix Transpose
std::vector<std::vector<double>> matrix_transpose(const std::vector<std::vector<double>>& matrix);

// Determinant Calculation
double calculate_determinant_leibniz(const std::vector<std::vector<double>>& matrix);
long double calculate_determinant_gauss(const std::vector<std::vector<double>>& matrix);

// LU Decomposition (PA = LU)
void lu_decomposition(
    const std::vector<std::vector<double>>& A,
    std::vector<std::vector<double>>& L,
    std::vector<std::vector<double>>& U,
    std::vector<int>& P_vector); 

#endif