# include <iostream>
# include <vector>

# include "matrix_options_base.h"

using namespace std;


vector<vector<double>> input_matrix(int n, int m){
    vector<vector<double>> matrix(n, vector<double>(m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if(!(cin >> matrix[i][j])) return {};
        }
    }
    return matrix;
}

void print_matrix(int n, int p, const vector<vector<double>>& matrix){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < p; j++){
            cout << matrix[i][j];
            if (j < p - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}