# include <vector>
# include <algorithm>
# include <cmath>
# include <numeric>

# include "matrix_options_base.h"

using namespace std;

// first version
// int count_inversions(const vector<int> p){
//     int inversions = 0;
//     size_t n = p.size();

//     for (size_t i = 0; i < n; i++){
//         for (size_t j = i + 1; j < n; j++){
//             if (p[i] > p[j]) inversions++;
//         }
//     }
//     return inversions;
// }

// vector<vector<int>> generate_permutaions_matrix(size_t n){
//     if (n <= 0) return {};
//     long long number_permutations = 1;
//     for (size_t i = 1; i <= n; i++) number_permutations *= i;
//     vector<vector<int>> result(number_permutations, vector<int>(n + 2));
//     vector<int> p(n);
//     iota(p.begin(), p.end(), 1);

//     size_t row_index = 0;

//     do {
//         int inversions = count_inversions(p);
//         // int s = 1;
//         double s = (inversions % 2 == 0) ? 1.0 : -1.0;
//         for (size_t i = 0; i < n; i++) result[row_index][i] = p[i];
//         // if (inversions % 2 == 0) s = 1;
//         // else s = -1;
//         result[row_index][n] = s;
//         result[row_index][n+1] = inversions;
//         row_index++;
//     } while (next_permutation(p.begin(), p.end()));
//     return result;

// }


// double calculate_determinant_leibniz(const vector<vector<double>>& matrix){
//     long double determinant = 0;
    
//     size_t rows = matrix.size();
//     vector<vector<int>> permutation_matrix = generate_permutaions_matrix(rows);
//     size_t permutations = permutation_matrix.size();
//     for (size_t i = 0; i < permutations; i++){
//         long double factor = 1;
//         for (size_t j = 0; j < rows; j++) {
//             size_t col_index = permutation_matrix[i][j] - 1;
//             factor *= matrix[j][col_index];
//         }
        
//         determinant += factor*permutation_matrix[i][rows];

//     }
//     return determinant;

// }

// Optimized version

// Statement: There is no necessity to optimize the function count_inversions because the minor performance improvements do have no improvements to the complex Leibniz's Algorithm.
// But as a beginer, I decided to optimized it in order to improve my level.

long long merge_and_count(std::vector<int>& arr, std::vector<int>& temp, size_t left, size_t mid, size_t right) {
    // 
    size_t i = left;      // 左子数组开始
    size_t j = mid + 1;   // 右子数组开始
    size_t k = left;      // 临时数组开始
    long long inversions = 0;

    // 1. 合并并计算逆序
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // 核心计算步骤：发现逆序！
            // arr[i] 及它后面的所有左半部分元素都大于 arr[j]
            inversions += (mid - i + 1); 
            temp[k++] = arr[j++];
        }
    }

    // 2. 复制剩余元素（无需额外计算逆序，因为另一半已用尽）
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // 3. 将结果复制回原数组
    for (i = left; i <= right; ++i) arr[i] = temp[i];

    return inversions;
}

long long count_inversions_recursive(std::vector<int>& arr, std::vector<int>& temp, size_t left, size_t right) {
    long long inversions = 0;
    
    // 递归终止条件
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        // 1. 递归计算左半部分逆序数
        inversions += count_inversions_recursive(arr, temp, left, mid);
        // 2. 递归计算右半部分逆序数
        inversions += count_inversions_recursive(arr, temp, mid + 1, right);

        // 3. 计算跨越左右两部分的逆序数，并合并数组
        inversions += merge_and_count(arr, temp, left, mid, right);
    }
    return inversions;
}

int count_inversions_optimized(const std::vector<int>& p) {
    if (p.empty()) return 0;
    
    // 归并排序会改变数组，所以需要复制原始排列 p
    std::vector<int> arr = p; 
    
    // 需要一个和 arr 一样大的临时数组用于合并操作
    std::vector<int> temp(arr.size());
    
    // 最好使用 long long 作为返回类型，以防 int 溢出（n! 逆序数可能很大）
    return (int)count_inversions_recursive(arr, temp, 0, arr.size() - 1);
}

double calculate_determinant_leibniz(const vector<vector<double>>& matrix){
    long double determinant = 0;
    size_t n = matrix.size();
    if (n <= 0) return 0;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);


    do {
        int inversions = count_inversions_optimized(p);
        double s = (inversions % 2 == 0) ? 1.0 : -1.0;
        long double factor = 1.0L;

        for (size_t i = 0; i < n; i++) factor *= matrix[i][p[i] - 1];

        determinant += factor*s;
        
    } while (next_permutation(p.begin(), p.end()));
        
    return determinant;   
}