# include <vector>
# include <algorithm>
# include "matrix_options_base.h"


using namespace std;

void Permutation(size_t i, size_t j, vector<vector<double>>& matrix){
    // // 临时存储一行数据，用于交换
    // vector<double> temp_row(m); 
    
    // // 1. 备份行 i
    // for (int a = 0; a < m; a++){
    //     temp_row[a] = matrix[i][a];
    // }
    
    // // 2. 将行 j 复制到行 i
    // for (int a = 0; a < m; a++){
    //     matrix[i][a] = matrix[j][a];
    // }
    
    // // 3. 将备份的行 i (即 temp_row) 复制到行 j
    // for (int a = 0; a < m; a++){
    //     matrix[j][a] = temp_row[a];
    // }
    
    // // return matrix;
    swap(matrix[i], matrix[j]);

}
