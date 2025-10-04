# include <vector>
# include "matrix_options_base.h"

using namespace std;

vector<vector<double>> create_identity_matrix(size_t n){
    vector<vector<double>> identity_matrix(n, vector<double>(n, 0.0));
    for (size_t i = 0; i < n; i++){
        identity_matrix[i][i] = 1.0;
    }
    return identity_matrix;
}