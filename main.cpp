#include "matrix_options_base.h"
#include <iostream>
#include <vector>
#include <locale>
#include <windows.h>

using namespace std;

void clear_input() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void handle_multiply() {
    size_t n, m, p;
    cout << "\n--- 矩阵乘法 (A * B) ---\n";
    cout << "请输入第一个矩阵 (A) 的维度 (n m): ";
    if (!(cin >> n >> m)) { clear_input(); return; }
    cout << "请输入第二个矩阵 (B) 的列数 (p): ";
    if (!(cin >> p)) { clear_input(); return; }
    
    cout << "请输入矩阵 A (" << n << "x" << m << "):" << endl;
    vector<vector<double>> m_1 = input_matrix(n, m);
    if (m_1.empty()) { cout << "输入错误或中断。\n"; return; }

    cout << "请输入矩阵 B (" << m << "x" << p << "):" << endl;
    vector<vector<double>> m_2 = input_matrix(m, p);
    if (m_2.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> result = matrix_multiply(m_1, m_2);
    
    cout << "\n结果矩阵 (A * B):\n";
    print_matrix(result);
}

void handle_transpose() {
    size_t n, m;
    cout << "\n--- 矩阵转置 (A^T) ---\n";
    cout << "请输入矩阵的维度 (n m): ";
    if (!(cin >> n >> m)) { clear_input(); return; }

    cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n, m);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> transposed = matrix_transpose(matrix);

    cout << "\n转置结果 (" << m << "x" << n << "):\n";
    print_matrix(transposed);
}

void handle_gauss_elimination() {
    size_t n, m;
    cout << "\n--- 高斯消元 ---\n";
    cout << "请输入矩阵的维度 (n m): ";
    if (!(cin >> n >> m)) { clear_input(); return; }

    cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n, m);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> working_matrix = matrix; 

    gauss_elimination(working_matrix);

    cout << "\n高斯消元结果 (行阶梯形):\n";
    print_matrix(working_matrix);
}

void handle_gauss_jordan_elimination() {
    size_t n, m;
    cout << "\n--- 高斯若尔当消元 ---\n";
    cout << "请输入矩阵的维度 (n m): ";
    if (!(cin >> n >> m)) { clear_input(); return; }

    cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n, m);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> working_matrix = matrix; 

    gauss_jordan_elimination(working_matrix);

    cout << "\n高斯若尔当消元结果 (行阶梯形):\n";
    print_matrix(working_matrix);
}

void handle_inverse() {
    size_t n;
    cout << "\n--- 逆矩阵 ---\n";
    cout << "请输入矩阵的行数或列数 (n): ";
    if (!(cin >> n)) { clear_input(); return; }

    cout << "请输入矩阵 (" << n << "x" << n << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n, n);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> inversed_matrix; 

    inversed_matrix = inverse(matrix);

    cout << "\n逆矩阵结果:\n";
    print_matrix(inversed_matrix);
}

void handle_determinant_leibniz(){
    size_t n = 0;
    cout << "\n--- 行列式计算-莱布尼茨方法 ---\n";
    cout << "请输入方阵的行数或列数 (n): ";
    if (!(cin >> n)) { clear_input(); return; }
    cout << "请输入方阵(" << n << "x" << n << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n,n);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }
    double determinant;
    determinant = calculate_determinant_leibniz(matrix);
    cout << "行列式计算结果：\n" << determinant << endl;
}

void handle_determinant_gauss(){
    size_t n = 0;
    cout << "\n--- 行列式计算-高斯消元方法 ---\n";
    cout << "请输入方阵的行数或列数 (n): ";
    if (!(cin >> n)) { clear_input(); return; }
    cout << "请输入方阵(" << n << "x" << n << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n,n);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }
    double determinant;
    determinant = calculate_determinant_gauss(matrix);
    cout << "行列式计算结果：\n" << determinant << endl;
}

void handle_lu_decomposition(){
    size_t n = 0;
    cout << "\n--- LU 分解 (PA = LU) ---\n";
    cout << "请输入方阵的行数或列数 (n): ";
    if (!(cin >> n)) { clear_input(); return; }
    
    cout << "请输入方阵(" << n << "x" << n << "):" << endl;
    vector<vector<double>> A = input_matrix(n,n);
    if (A.empty()) { cout << "输入错误或中断。\n"; return; }
    
    vector<vector<double>> L, U;
    vector<int> P_vector;

    lu_decomposition(A, L, U, P_vector);
    
    if (L.empty()){
        cout << "无法进行 LU 分解 (矩阵维度错误)。\n";
        return;
    }

    cout << "\nL 矩阵 (Lower Triangular):\n";
    print_matrix(L);

    cout << "\nU 矩阵 (Upper Triangular):\n";
    print_matrix(U);

    cout << "\nP 向量 (Permutation Vector，表示行交换顺序):\n";
    for(int val : P_vector) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    SetConsoleOutputCP(65001); // 设置输出编码为 UTF-8
    SetConsoleCP(65001);       // 设置输入编码为 UTF-8
    std::locale::global(std::locale(""));
    wcout.imbue(std::locale());
    wcin.imbue(std::locale());

    int choice;
    do {
        cout << "\n================================\n";
        cout << "      矩阵功能管理程序\n";
        cout << "================================\n";
        cout << "1. 矩阵乘法 (A * B)\n";
        cout << "2. 矩阵转置 (A^T)\n";
        cout << "3. 高斯消元 (Gauss Elimination)\n";
        cout << "4. 高斯若尔当消元 (Gauss-Jordan Elimination)\n";
        cout << "5. 逆矩阵 (Inversed Matrix)\n";
        cout << "6. 行列式计算-莱布尼茨方法(Determination Calculation - Leibniz)\n";
        cout << "7. 行列式计算-高斯消元方法(Determination Calculation - Gauss)\n";
        cout << "8. LU 分解 (LU Decomposition - PA = LU)\n";
        cout << "0. 退出\n";
        cout << "请选择功能编号: ";
        
        if (!(cin >> choice)) {
            clear_input();
            cout << "输入错误，退出程序。\n";
            break;
        }

        switch (choice) {
            case 1:
                handle_multiply();
                break;
            case 2:
                handle_transpose();
                break;
            case 3:
                handle_gauss_elimination();
                break;
            case 4:
                handle_gauss_jordan_elimination();
                break;
            case 5:
                handle_inverse();
                break;
            case 6:
                handle_determinant_leibniz();
                break;
            case 7:
                handle_determinant_gauss();
                break;
            case 8:
                handle_lu_decomposition();
                break;
            case 0:
                cout << "程序退出。\n";
                break;
            default:
                cout << "选择无效，请重新输入。\n";
                break;
        }
    } while (choice != 0);

    return 0;
}