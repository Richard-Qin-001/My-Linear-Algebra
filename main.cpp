#include "matrix_options_base.h"
#include <iostream>
#include <vector>
#include <locale>
#include <windows.h>

using namespace std;

// 辅助函数：处理输入失败，避免程序崩溃
void clear_input() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void handle_multiply() {
    int n, m, p;
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

    vector<vector<double>> result = matrix_multiply(m_1, m_2, n, m, p);
    
    cout << "\n结果矩阵 (A * B):\n";
    print_matrix(n, p, result);
}

void handle_transpose() {
    int n, m;
    cout << "\n--- 矩阵转置 (A^T) ---\n";
    cout << "请输入矩阵的维度 (n m): ";
    if (!(cin >> n >> m)) { clear_input(); return; }

    cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n, m);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> transposed = matrix_transpose(matrix, n, m);

    cout << "\n转置结果 (" << m << "x" << n << "):\n";
    print_matrix(m, n, transposed);
}

void handle_elimination() {
    int n, m;
    cout << "\n--- 高斯消元 ---\n";
    cout << "请输入矩阵的维度 (n m): ";
    if (!(cin >> n >> m)) { clear_input(); return; }

    cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n, m);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    // 这里使用临时副本，因为 Elimination 是原地修改
    vector<vector<double>> working_matrix = matrix; 

    Elimination(n, m, working_matrix);

    cout << "\n高斯消元结果 (行阶梯形):\n";
    print_matrix(n, m, working_matrix);
}

void handle_determinant1(){
    int n = 0;
    cout << "请输入方阵的行数或列数 (n): ";
    if (!(cin >> n)) { clear_input(); return; }
    cout << "请输入方阵(" << n << "x" << n << "):" << endl;
    vector<vector<double>> matrix = input_matrix(n,n);
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }
    double determinant;
    determinant = calculate_determinant(matrix);
    cout << "行列式计算结果：" << determinant << endl;
}

int main() {
    SetConsoleOutputCP(65001); // 设置输出编码为 UTF-8
    SetConsoleCP(65001);       // 设置输入编码为 UTF-8
    locale::global(locale(""));
    wcout.imbue(locale());
    wcin.imbue(locale());

    int choice;
    do {
        cout << "\n================================\n";
        cout << "      矩阵功能管理程序\n";
        cout << "================================\n";
        cout << "1. 矩阵乘法 (A * B)\n";
        cout << "2. 矩阵转置 (A^T)\n";
        cout << "3. 高斯消元 (Gauss Elimination)\n";
        cout << "4. 行列式计算-莱布尼茨方法(Determination Calculation - Leibniz)\n";
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
                handle_elimination();
                break;
            case 4:
                handle_determinant1();
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