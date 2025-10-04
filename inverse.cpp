# include <vector>
# include <cmath>
# include <stdexcept>

# include "matrix_options_base.h"

using namespace std;

vector<vector<double>> inverse(const vector<vector<double>>& matrix){
    size_t n = matrix.size();
    if (n == 0 || matrix[0].size() != n) {
        throw std::invalid_argument("Matrix must be a non-empty square matrix (n x n) to compute inverse.");
    }
    vector<vector<double>> augmented_matrix, identity_matrix = create_identity_matrix(n), inversed_matrix;
    augmented_matrix.reserve(n);
    inversed_matrix.reserve(n);
    for(size_t i = 0; i < n; i++){
        // 1. 复制 A 的第 i 行 (作为新行)
        vector<double> row = matrix[i];    
        // 2. 将 I 的第 i 行的元素追加到该行的末尾 (水平拼接)
        row.insert(row.end(), identity_matrix[i].begin(), identity_matrix[i].end());  
        // 3. 将完整的 n x 2n 行添加到 augmented_matrix
        augmented_matrix.push_back(std::move(row));
    }
    gauss_jordan_elimination(augmented_matrix);
    for (size_t i = 0; i < n; i++){
        if (std::abs(augmented_matrix[i][i] - 1.0) > 1e-9) {
            throw std::runtime_error("Matrix is singular (det=0) and cannot be inverted.");
        }      
        vector<double> inverse_row;
        inverse_row.reserve(n);
        for (size_t j = n; j < 2 * n; j++) {
            inverse_row.push_back(augmented_matrix[i][j]);
        }
        inversed_matrix.push_back(std::move(inverse_row));
    }
    return inversed_matrix;

}