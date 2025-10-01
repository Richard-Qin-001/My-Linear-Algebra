# include <iostream>
# include <vector>
# include <cmath>

# include "matrix_options_base.h"

using namespace std;



// vector<double> line_elimination(int length, int index,vector<double> line_1, vector<double> line_2){
//     double e1 = line_1[index];
//     double e2 = line_2[index];
//     vector<double> result(length);
//     for (int i = 0; i < length; i++ ){
//         result[i] = line_2[i] - line_1[i] * (e2 / e1);
//     }
//     return result;


// }

void Elimination(int n, int m, vector<vector<double>>& matrix){
    // vector<double> line_1(m);
    // vector<double> line_e(m);
    int steps = min(m, n);
    for (int i = 0; i < steps; i++){
        int privot_row = i;
        double max_val = abs(matrix[i][i]);

        for (int k = i + 1; k < n; k++){
            if (abs(matrix[k][i]) > max_val){
                max_val = abs(matrix[k][i]);
                privot_row = k;
            }
        }

        if (privot_row != i){
                Permutation(i, privot_row, n, m, matrix);
        }
        

        if (abs(matrix[i][i]) < 1e-9) {
            continue;
        }

        // for (int j = 0; j < m; j++){
        //     line_1[j] = matrix[i][j];
        // }
        // for (int j = i+1; j < n; j++){
        //     for (int k = 0; k < m; k++){
        //         line_e[k] = matrix[j][k];
        //     }
        //     line_e = line_elimination(m, i, line_1, line_e);
        //     for (int k = 0; k < m; k++){
        //         matrix [j][k] = line_e[k];
        //     }
        // }
        // **标准的 in-place 消元过程 (Standard In-Place Elimination)**
        for (int j = i + 1; j < n; j++){ // 遍历要消元的行 (从 i+1 行开始)
            // 1. 计算乘数 (Multiplier): l_ji = A_ji / A_ii
            double multiplier = matrix[j][i] / matrix[i][i];
            
            // 2. 执行行操作: R_j <- R_j - multiplier * R_i
            // 从当前列 i 开始循环，因为 i 之前的元素应该已经为 0 
            for (int k = i; k < m; k++){ 
                matrix[j][k] = matrix[j][k] - multiplier * matrix[i][k];
            }
        }
    }
    // return matrix;
}

// int main(){
//     int n, m;
//     cout << "Input the number of rows and columns:";
//     cin >> n >> m;
//     vector<vector<double>> matrix(n, vector<double>(m));
//     cout << "Input your matrix:" << endl;
//     matrix = input_matrix(n, m);
//     Elimination(n, m, matrix);
//     cout << "Gauss Elimination result:" << endl;
//     output_matrix(n, m, matrix);
//     return 0;

// }
