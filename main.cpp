# include "matrix_options_base.h"
# include <iostream>
# include <vector>
# include <locale>
# include <windows.h>
# include <fstream>
# include "json.hpp"

using namespace std;
using json = nlohmann::json;

// --- 新增：全局存储结构 ---
// 用于存储从 JSON 加载的矩阵数据，方便后续功能直接调用。
struct LoadedMatrices {
    vector<vector<double>> A;
    vector<vector<double>> B;
    bool is_A_loaded = false;
    bool is_B_loaded = false;
};

LoadedMatrices g_loaded_data; // 定义全局变量

void clear_input() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void handle_load_matrix_from_json() {
    int choice;
    string filename;
    cout << "\n--- 从 JSON 文件加载矩阵 ---\n";
    cout << "选择要加载为哪个矩阵 (1: 矩阵A, 2: 矩阵B): ";
    if (!(cin >> choice)) { clear_input(); return; }

    if (choice != 1 && choice != 2) {
        cout << "选择无效。\n";
        return;
    }

    cout << "请输入 JSON 文件名: ";
    if (!(cin >> filename)) { clear_input(); return; }

    vector<vector<double>> matrix = read_matrix_from_json(filename);

    if (matrix.empty()) {
        cout << "加载失败。\n";
        return;
    }

    if (choice == 1) {
        g_loaded_data.A = std::move(matrix);
        g_loaded_data.is_A_loaded = true;
        cout << "矩阵 A 已从 JSON 文件加载并存储。\n";
    } else { // choice == 2
        g_loaded_data.B = std::move(matrix);
        g_loaded_data.is_B_loaded = true;
        cout << "矩阵 B 已从 JSON 文件加载并存储。\n";
    }
}

void handle_multiply() {
    cout << "\n--- 矩阵乘法 (A * B) ---\n";
    // --- 矩阵 A 输入逻辑 ---
    vector<vector<double>> m_1;
    if (g_loaded_data.is_A_loaded) {
        char use_loaded;
        cout << "是否使用已加载的矩阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A[0].size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            m_1 = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }
    size_t n, m;
    if (m_1.empty()) { // 如果没有使用已加载数据，则进行手动输入
        cout << "请输入第一个矩阵 (A) 的维度 (n m): ";
        if (!(cin >> n >> m)) { clear_input(); return; }
        cout << "请输入矩阵 A (" << n << "x" << m << "):" << endl;
        m_1 = input_matrix(n, m);
    } else {
        n = m_1.size();
        m = m_1[0].size();
    }
    if (m_1.empty()) { cout << "输入错误或中断。\n"; return; }


    // --- 矩阵 B 输入逻辑 ---
    vector<vector<double>> m_2;
    size_t p;
    // 检查乘法规则，矩阵 B 的行数必须等于矩阵 A 的列数 m
    if (g_loaded_data.is_B_loaded && g_loaded_data.B.size() == m) {
        char use_loaded;
        cout << "是否使用已加载的矩阵 B (" << g_loaded_data.B.size() << "x" << g_loaded_data.B[0].size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            m_2 = g_loaded_data.B;
            p = m_2[0].size();
            cout << "使用已加载的矩阵 B。\n";
        }
    }
    
    if (m_2.empty()) { // 如果没有使用已加载数据，则进行手动输入
        cout << "请输入第二个矩阵 (B) 的列数 (p): ";
        if (!(cin >> p)) { clear_input(); return; }
        cout << "请输入矩阵 B (" << m << "x" << p << "):" << endl;
        m_2 = input_matrix(m, p);
    } else {
        p = m_2[0].size();
    }
    if (m_2.empty()) { cout << "输入错误或中断。\n"; return; }
    vector<vector<double>> result = matrix_multiply(m_1, m_2);
    
    cout << "\n结果矩阵 (A * B):\n";
    print_matrix(result);
}

void handle_transpose() {
    cout << "\n--- 矩阵转置 (A^T) ---\n";
    vector<vector<double>> matrix;
    size_t n, m;
    // --- 矩阵 A/Matrix 输入逻辑 ---
    if (g_loaded_data.is_A_loaded) {
        char use_loaded;
        cout << "是否使用已加载的矩阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A[0].size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            matrix = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }

    if (matrix.empty()) { // 如果没有使用已加载数据，则进行手动输入
        cout << "请输入矩阵的维度 (n m): ";
        if (!(cin >> n >> m)) { clear_input(); return; }
        cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
        matrix = input_matrix(n, m);
    } else {
        n = matrix.size();
        m = matrix[0].size();
    }
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> transposed = matrix_transpose(matrix);
    cout << "\n转置结果 (" << m << "x" << n << "):\n";
    print_matrix(transposed);
}

void handle_gauss_elimination() {
    cout << "\n--- 高斯消元 ---\n";
    vector<vector<double>> matrix;
    
    if (g_loaded_data.is_A_loaded) {
        char use_loaded;
        cout << "是否使用已加载的矩阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A[0].size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            matrix = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }
    size_t n, m;
    if (matrix.empty()) {
        cout << "请输入矩阵的维度 (n m): ";
        if (!(cin >> n >> m)) { clear_input(); return; }
        cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
        matrix = input_matrix(n, m);
    } else {
        n = matrix.size();
        m = matrix[0].size();
    }
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> working_matrix = matrix; 

    gauss_elimination(working_matrix);

    cout << "\n高斯消元结果 (行阶梯形):\n";
    print_matrix(working_matrix);
}

void handle_gauss_jordan_elimination() {  
    cout << "\n--- 高斯若尔当消元 ---\n";
    vector<vector<double>> matrix;
    
    if (g_loaded_data.is_A_loaded) {
        char use_loaded;
        cout << "是否使用已加载的矩阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A[0].size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            matrix = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }
    size_t n, m;
    if (matrix.empty()) {
        cout << "请输入矩阵的维度 (n m): ";
        if (!(cin >> n >> m)) { clear_input(); return; }
        cout << "请输入矩阵 (" << n << "x" << m << "):" << endl;
        matrix = input_matrix(n, m);
    } else {
        n = matrix.size();
        m = matrix[0].size();
    }
    if (matrix.empty()) { cout << "输入错误或中断。\n"; return; }

    vector<vector<double>> working_matrix = matrix; 

    gauss_jordan_elimination(working_matrix);

    cout << "\n高斯若尔当消元结果 (行阶梯形):\n";
    print_matrix(working_matrix);
}

void handle_inverse() {
    size_t n;
    cout << "\n--- 逆矩阵 ---\n";
    vector<vector<double>> matrix;
    
    if (g_loaded_data.is_A_loaded && g_loaded_data.A.size() == g_loaded_data.A[0].size()) {
        char use_loaded;
        cout << "是否使用已加载的方阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A.size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            matrix = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }
    
    if (matrix.empty()) {
        cout << "请输入矩阵的行数或列数 (n): ";
        if (!(cin >> n)) { clear_input(); return; }
        cout << "请输入矩阵 (" << n << "x" << n << "):" << endl;
        matrix = input_matrix(n, n);
    } else {
        n = matrix.size();
    }
    if (matrix.empty() || n != matrix[0].size()) { 
        cout << "输入错误或中断，或矩阵不是方阵。\n"; 
        return; 
    }
    vector<vector<double>> inversed_matrix; 

    inversed_matrix = inverse(matrix);

    cout << "\n逆矩阵结果:\n";
    print_matrix(inversed_matrix);
}

void handle_determinant_leibniz(){
    size_t n = 0;
    cout << "\n--- 行列式计算-莱布尼茨方法 ---\n";
    vector<vector<double>> matrix;
    
    // --- 新增：JSON 数据选择逻辑 ---
    if (g_loaded_data.is_A_loaded && g_loaded_data.A.size() == g_loaded_data.A[0].size()) {
        char use_loaded;
        cout << "是否使用已加载的方阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A.size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            matrix = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }
    
    if (matrix.empty()) { // 仍需手动输入
        cout << "请输入矩阵的行数或列数 (n): ";
        if (!(cin >> n)) { clear_input(); return; }
        cout << "请输入矩阵 (" << n << "x" << n << "):" << endl;
        matrix = input_matrix(n, n);
    } else {
        n = matrix.size();
    }
    if (matrix.empty() || n != matrix[0].size()) { 
        cout << "输入错误或中断，或矩阵不是方阵。\n"; 
        return; 
    }
    double determinant;
    determinant = calculate_determinant_leibniz(matrix);
    cout << "行列式计算结果：\n" << determinant << endl;
}

void handle_determinant_gauss(){
    size_t n = 0;
    cout << "\n--- 行列式计算-高斯消元方法 ---\n";
    vector<vector<double>> matrix;
    
    // --- 新增：JSON 数据选择逻辑 ---
    if (g_loaded_data.is_A_loaded && g_loaded_data.A.size() == g_loaded_data.A[0].size()) {
        char use_loaded;
        cout << "是否使用已加载的方阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A.size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            matrix = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }
    
    if (matrix.empty()) { // 仍需手动输入
        cout << "请输入矩阵的行数或列数 (n): ";
        if (!(cin >> n)) { clear_input(); return; }
        cout << "请输入矩阵 (" << n << "x" << n << "):" << endl;
        matrix = input_matrix(n, n);
    } else {
        n = matrix.size();
    }
    if (matrix.empty() || n != matrix[0].size()) { 
        cout << "输入错误或中断，或矩阵不是方阵。\n"; 
        return; 
    }
    double determinant;
    determinant = calculate_determinant_gauss(matrix);
    cout << "行列式计算结果：\n" << determinant << endl;
}

void handle_lu_decomposition(){
    size_t n = 0;
    cout << "\n--- LU 分解 (PA = LU) ---\n";
    vector<vector<double>> A;
    
    if (g_loaded_data.is_A_loaded && g_loaded_data.A.size() == g_loaded_data.A[0].size()) {
        char use_loaded;
        cout << "是否使用已加载的方阵 A (" << g_loaded_data.A.size() << "x" << g_loaded_data.A.size() << ")? (y/n): ";
        if (!(cin >> use_loaded)) { clear_input(); return; }
        if (tolower(use_loaded) == 'y') {
            A = g_loaded_data.A;
            cout << "使用已加载的矩阵 A。\n";
        }
    }
    
    if (A.empty()) { // 仍需手动输入
        cout << "请输入矩阵的行数或列数 (n): ";
        if (!(cin >> n)) { clear_input(); return; }
        cout << "请输入矩阵 (" << n << "x" << n << "):" << endl;
        A = input_matrix(n, n);
    } else {
        n = A.size();
    }
    if (A.empty() || n != A[0].size()) { 
        cout << "输入错误或中断，或矩阵不是方阵。\n"; 
        return; 
    }
    
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
        cout << "0. 退出\n";
        cout << "--- 数据源管理 ---\n";
        cout << "9. 从 JSON 文件加载矩阵 (A/B)\n"; // 新增加载功能
        cout << "--- 核心运算功能 ---\n";
        cout << "1. 矩阵乘法 (A * B)\n";
        cout << "2. 矩阵转置 (A^T)\n";
        cout << "3. 高斯消元 (Gauss Elimination)\n";
        cout << "4. 高斯若尔当消元 (Gauss-Jordan Elimination)\n";
        cout << "5. 逆矩阵 (Inversed Matrix)\n";
        cout << "6. 行列式计算-莱布尼茨方法(Determination Calculation - Leibniz)\n";
        cout << "7. 行列式计算-高斯消元方法(Determination Calculation - Gauss)\n";
        cout << "8. LU 分解 (LU Decomposition - PA = LU)\n";       
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
            case 9:
                handle_load_matrix_from_json();
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