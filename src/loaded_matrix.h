#ifndef LOADEDMATRICES_H
#define LOADEDMATRICES_H

#include <vector>

// 声明在 main.cpp 中定义的全局结构体
struct LoadedMatrices {
    std::vector<std::vector<double>> A;
    std::vector<std::vector<double>> B;
    bool is_A_loaded = false;
    bool is_B_loaded = false;
};

extern LoadedMatrices g_loaded_data;

#endif // LOADEDMATRICES_H