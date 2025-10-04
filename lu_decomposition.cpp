# include <vector>
# include <cmath>
# include <numeric> // For std::iota

# include "matrix_options_base.h"

using namespace std;

void lu_decomposition(const vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, vector<int>& P_vector){
    size_t n = A.size();
    if (n == 0 || A[0].size() != n){
        L.clear(); U.clear(); P_vector.clear();
        return;
    }
    U = A;
    L.assign(n, vector<double>(n, 0.0));
    P_vector.resize(n);
    iota(P_vector.begin(), P_vector.end(), 0);

    for (size_t i = 0; i < n; i++){
        L[i][i] = 1.0;
    }

    for (size_t i = 0; i < n; i++){
        size_t privot_row = i;
        double max_val = abs(U[i][i]);

        for (size_t k = i + 1; k < n; k++){
            if (abs(U[k][i]) > max_val){
                max_val = abs(U[k][i]);
                privot_row = k;
            }
        }

        if (privot_row != i){
            Permutation(i, privot_row, U); 
            for (size_t j = 0; j < i; j++) {
                swap(L[i][j], L[privot_row][j]);
            }
            swap(P_vector[i], P_vector[privot_row]); 
        }
        
        if (abs(U[i][i]) < 1e-9) {
            continue;
        }
        for (size_t j = i + 1; j < n; j++){ 
            double multiplier = U[j][i] / U[i][i];
            
            L[j][i] = multiplier;
            
            for (size_t k = i; k < n; k++){ 
                U[j][k] = U[j][k] - multiplier * U[i][k];
            }
        }
    }
}

