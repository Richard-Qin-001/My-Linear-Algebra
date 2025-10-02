# include <iostream>
# include <vector>
# include <algorithm>
# include <cmath>
# include <numeric>

# include "matrix_options_base.h"

using namespace std;

int count_inversions(const vector<int> p){
    int inversions = 0;
    int n = p.size();

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (p[i] > p[j]) inversions++;
        }
    }
    return inversions;
}

vector<vector<int>> generate_permutaions_matrix(int n){
    if (n <= 0) return {};
    long long number_permutations = 1;
    for (int i = 1; i <= n; i++) number_permutations *= i;
    vector<vector<int>> result(number_permutations, vector<int>(n + 2));
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    int row_index = 0;

    do {
        int inversions = count_inversions(p);
        int s = 1;
        for (int i = 0; i < n; i++) result[row_index][i] = p[i];
        if (inversions % 2 == 0) s = 1;
        else s = -1;
        result[row_index][n] = s;
        result[row_index][n+1] = inversions;
        row_index++;
    } while (next_permutation(p.begin(), p.end()));
    return result;

}


double calculate_determinant(const vector<vector<double>>& matrix){
    double determinant = 0;
    size_t rows = matrix.size();
    vector<vector<int>> permutation_matrix = generate_permutaions_matrix(rows);
    long long permutations = permutation_matrix.size();
    for (int i = 0; i < permutations; i++){
        long double factor = 1;
        for (int j = 0; j < (int)rows; j++) {
            int col_index = permutation_matrix[i][j] - 1;
            factor *= matrix[j][col_index];
        }
        
        determinant += factor*permutation_matrix[i][rows];

    }
    return determinant;

}
