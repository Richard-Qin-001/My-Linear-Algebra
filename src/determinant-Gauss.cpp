# include <vector>

# include "matrix_options_base.h"

using namespace std;

long double calculate_determinant_gauss(const vector<vector<double>>& matrix){
    size_t n = matrix.size();
    long double determinant = 1.0L;
    vector<vector<double>> e_matrix = matrix;
    int sign_factor = gauss_forward_elimination(e_matrix);
    for (size_t i = 0; i < n; i++){
        determinant *= e_matrix[i][i];
    }
    return determinant * sign_factor;

}