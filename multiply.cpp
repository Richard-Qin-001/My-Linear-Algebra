# include <iostream>
# include <vector>

# include "matrix_options_base.h"

using namespace std;

// vector<vector<double>> input_matrix(int n, int m){
//     vector<vector<double>> matrix(n, vector<double>(m));
//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < m; j++){
//             if(!(cin >> matrix[i][j])) return {};
//         }
//     }
//     return matrix;
// }

vector<vector<double>> matrix_multiply(const vector<vector<double>>& m_1, const vector<vector<double>>& m_2, int n, int m, int p){
    vector<vector<double>> matrix(n, vector<double>(p));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < p; j++){
            double combination = 0;
            for (int k = 0; k < m; k++){
                combination += m_1[i][k] * m_2[k][j];
            }
            matrix[i][j] = combination;
        }
    }
    return matrix;
}

// void print_matrix(vector<vector<double>> matrix, int n, int p){
//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < p; j++){
//             cout << matrix[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

// int main(){
//     int n, m, p;
//     cin >> n >> m >> p;
//     vector<vector<double>> m_1 = input_matrix(n, m);
//     vector<vector<double>> m_2= input_matrix(m, p);
//     vector<vector<double>> matrix = matrix_multiply(m_1, m_2, n, m, p);
//     print_matrix(matrix, n, p);
//     return 0;

// }