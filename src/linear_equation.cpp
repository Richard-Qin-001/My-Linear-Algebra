# include <vector>
# include "matrix_options_base.h"

using namespace std;
vector<vector<double>> solve_nullspace(vector<vector<double>> matrix){
	size_t n = matrix.size();
    if (n == 0) return {};
    size_t m = matrix[0].size();
    if (m == 0) return {};
    size_t steps = min(n, m);
    size_t rank = 0;
    gauss_jordan_elimination(matrix);
    for (size_t i = 0; i < steps; i++){
        if (matrix[i][i] == 1){
            rank += 1;
        }
        else break;
    }
    vector<vector<double>> nullspace(n, vector<double>(m-rank));
    for (size_t i = 0; i < m - rank; i++){
        for (size_t j = 0; j < n; j++){
            nullspace[j][i] = 0.0 - matrix[j][i + rank];
        }
    }
    return nullspace;
}

vector<vector<double>> solve_leftnullspace(vector<vector<double>> matrix){
	matrix = matrix_transpose(matrix);
    size_t n = matrix.size();
    if (n == 0) return {};
    size_t m = matrix[0].size();
    if (m == 0) return {};
    size_t steps = min(n, m);
    size_t rank = 0;
    gauss_jordan_elimination(matrix);
    for (size_t i = 0; i < steps; i++){
        if (matrix[i][i] == 1){
            rank += 1;
        }
        else break;
    }
    vector<vector<double>> leftnullspace(n, vector<double>(m-rank));
    for (size_t i = 0; i < m - rank; i++){
        for (size_t j = 0; j < n; j++){
            leftnullspace[j][i] = 0.0 - matrix[j][i + rank];
        }
    }
    return leftnullspace;
}