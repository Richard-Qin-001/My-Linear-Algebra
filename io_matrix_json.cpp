# include "matrix_options_base.h"
# include <iostream>
# include <vector>
# include <fstream>
# include "json.hpp"

using namespace std;
using json = nlohmann::json; 

vector<vector<double>> read_matrix_from_json(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "错误: 无法打开文件 " << filepath << endl;
        return {};
    }

    try {
        json j;
        file >> j; // 从文件读取 JSON 数据

        // 检查 JSON 结构是否符合预期 (例如，一个包含 double 数组的数组)
        if (!j.is_array() || j.empty()) {
            cerr << "错误: JSON 根元素不是数组或为空。" << endl;
            return {};
        }

        vector<vector<double>> matrix;
        size_t expected_cols = 0;
        bool first_row = true;

        for (const auto& json_row : j) {
            if (!json_row.is_array()) {
                cerr << "错误: JSON 内部元素不是数组 (不是二维结构)。" << endl;
                return {};
            }

            vector<double> row;
            for (const auto& val : json_row) {
                if (!val.is_number()) {
                    cerr << "错误: 矩阵元素不是数字。" << endl;
                    return {};
                }
                row.push_back(val.get<double>());
            }
            
            // 确保所有行具有相同的列数
            if (first_row) {
                expected_cols = row.size();
                first_row = false;
            } else if (row.size() != expected_cols) {
                cerr << "错误: 矩阵行数不一致。" << endl;
                return {};
            }
            
            matrix.push_back(std::move(row));
        }

        return matrix;

    } catch (const json::parse_error& e) {
        cerr << "错误: JSON 解析失败 - " << e.what() << endl;
        return {};
    } catch (const exception& e) {
        cerr << "发生未知错误: " << e.what() << endl;
        return {};
    }
}