# include <iostream>
# include <vector>

# include "matrix_options_base.h"

using namespace std;


vector<vector<double>> input_matrix(size_t n, size_t m){
    vector<vector<double>> matrix(n, vector<double>(m));
    for (size_t i = 0; i < n; i++){
        for (size_t j = 0; j < m; j++){
            if(!(cin >> matrix[i][j])) return {};
        }
    }
    return matrix;
}

void print_matrix(const vector<vector<double>>& matrix){
    size_t n = matrix.size();
    size_t m = matrix[0].size();
    for (size_t i = 0; i < n; i++){
        for (size_t j = 0; j < m; j++){
            cout << matrix[i][j];
            if (j < m - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}