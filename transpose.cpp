// # include <iostream>
// # include <vector>
// # include <algorithm>

// # include "matrix_options_base.h"

// using namespace std;

// void solve(int n, int m){
//     int matrix[n][m];
//     for (int i = 0; i < n; i++){
//         for (int j = 0; j < m; j++){
//             cin >> matrix[i][j];
//         }
//     }
//     for (int j = 0; j < m; j++){
//         for (int i = 0; i < n; i++){
//             if (i != 0) cout << " ";
//             cout << matrix[i][j];
//         }
//         cout << endl;
//     }

// }
// // int main(){
// //     int n, m;
// //     cin >> n >> m;
// //     solve(n, m);
// //     return 0;
// // }

// transpose.cpp
#include "matrix_options_base.h"
#include <vector>

using namespace std;

vector<vector<double>> matrix_transpose(
    const vector<vector<double>>& matrix, 
    int n, int m)
{
    vector<vector<double>> transposed_matrix(m, vector<double>(n));
    
    for (int i = 0; i < n; i++){ 
        for (int j = 0; j < m; j++){ 
            transposed_matrix[j][i] = matrix[i][j];
        }
    }
    return transposed_matrix;
}
