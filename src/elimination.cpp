# include <vector>
# include <cmath>
# include <algorithm>
# include "matrix_options_base.h"

using namespace std;


void gauss_elimination(vector<vector<double>>& matrix){
    size_t n = matrix.size();
    if (n == 0) return;
    size_t m = matrix[0].size();
    if (m == 0) return;
    size_t steps = min(m, n);
    for (size_t i = 0; i < steps; i++){
        size_t privot_row = i;
        double max_val = abs(matrix[i][i]);

        for (size_t k = i + 1; k < n; k++){
            if (abs(matrix[k][i]) > max_val){
                max_val = abs(matrix[k][i]);
                privot_row = k;
            }
        }

        if (privot_row != i){
                Permutation(i, privot_row, matrix);
        }
        

        if (abs(matrix[i][i]) < 1e-9) {
            continue;
        }

        for (size_t j = i + 1; j < n; j++){
            double multiplier = matrix[j][i] / matrix[i][i]; 
            for (size_t k = i; k < m; k++){ 
                matrix[j][k] = matrix[j][k] - multiplier * matrix[i][k];
            }
        }
    }
}


int gauss_forward_elimination(vector<vector<double>>& matrix) {
    size_t n = matrix.size();
    if (n == 0) return 1;
    size_t m = matrix[0].size();
    if (m == 0) return 1;
    size_t steps = min(m, n);
    size_t swap_count = 0;

    for (size_t i = 0; i < steps; i++){
        size_t privot_row = i;
        double max_val = abs(matrix[i][i]);

        for (size_t k = i + 1; k < n; k++){
            if (abs(matrix[k][i]) > max_val){
                max_val = abs(matrix[k][i]);
                privot_row = k;
            }
        }

        if (privot_row != i){
            Permutation(i, privot_row, matrix);
            swap_count++; 
        }
        

        if (abs(matrix[i][i]) < 1e-9) {
            continue;
        }

        for (size_t j = i + 1; j < n; j++){ 
            double multiplier = matrix[j][i] / matrix[i][i];
            
            for (size_t k = i; k < m; k++){ 
                matrix[j][k] = matrix[j][k] - multiplier * matrix[i][k];
            }
        }
    }
    return (swap_count % 2 == 0) ? 1 : -1;
}

void gauss_jordan_elimination(vector<vector<double>>& matrix){
    size_t n = matrix.size();
    if (n == 0) return;
    size_t m = matrix[0].size();
    if (m == 0) return;
    gauss_elimination(matrix);
    double factor = 0.0;

    size_t i = n;

    while(i > 0){
        i--;
        size_t pivot_col = m;
        for (size_t j = 0; j < m; j++){
            if (abs(matrix[i][j]) >= 1e-9){
                pivot_col = j;
                break;
            }
        }
        if (pivot_col == m) continue;
        factor = matrix[i][pivot_col];
        if (abs(factor) < 1e-9) continue;
        for (size_t k = pivot_col; k < m; k++){
                matrix[i][k] = matrix[i][k] / factor;
        }
        for (size_t t = 0; t < i; t++){
            double multiplier = matrix[t][pivot_col];
            for (size_t k = pivot_col; k < m; k++){
                    matrix[t][k] = matrix[t][k] - matrix[i][k] * multiplier;
            }
        }    
    }
    
}
