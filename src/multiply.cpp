# include <vector>

# include "matrix_options_base.h"

using namespace std;

vector<vector<double>> matrix_multiply(const vector<vector<double>>& m_1, const vector<vector<double>>& m_2){
    size_t n = m_1.size();
    size_t m = m_2.size();
    size_t p = m_2[0].size();
    vector<vector<double>> matrix(n, vector<double>(p));
    for (size_t i = 0; i < n; i++){
        for (size_t j = 0; j < p; j++){
            double combination = 0;
            for (size_t k = 0; k < m; k++){
                combination += m_1[i][k] * m_2[k][j];
            }
            matrix[i][j] = combination;
        }
    }
    return matrix;
}
