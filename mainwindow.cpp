#include "mainwindow.h"
#include "ui_MyLinearAlgebra.h"
# include "loaded_matrix.h"

#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>

// ----------------------------------------------------------------------
// 访问 main.cpp 中的全局状态
// ----------------------------------------------------------------------

// 声明 main.cpp 中定义的全局变量，这样可以在 GUI 中修改它
extern LoadedMatrices g_loaded_data;

// ----------------------------------------------------------------------
// 矩阵 I/O 辅助函数
// ----------------------------------------------------------------------

// 从 QTableWidget 读取数据
std::vector<std::vector<double>> MainWindow::readMatrixFromTable(QTableWidget* table) {
    int rows = table->rowCount();
    int cols = table->columnCount();

    if (rows == 0 || cols == 0) {
        throw std::runtime_error("矩阵尺寸无效 (0x0)。");
    }

    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem* item = table->item(i, j);
            if (!item) {
                // 如果单元格为空，默认为 0.0
                result[i][j] = 0.0;
                continue;
            }
            bool ok;
            double value = item->text().toDouble(&ok);
            if (!ok) {
                 throw std::runtime_error(QString("表格中发现非数字输入 (行%1, 列%2)。").arg(i+1).arg(j+1).toStdString());
            }
            result[i][j] = value;
        }
    }
    return result;
}

// 将数据显示到 QTextBrowser (输出结果)
void MainWindow::displayMatrixToTextBrowser(QTextBrowser* browser, const std::vector<std::vector<double>>& matrix, const QString& title) {
    if (matrix.empty() || matrix[0].empty()) {
        browser->setText(title + "\n结果矩阵为空。");
        return;
    }
    // 使用 HTML 格式化输出，适应深色背景
    QString html = QString("<h4 style='color: #eee;'>%1</h4>").arg(title);
    html += "<table border='1' cellpadding='5' style='border-collapse: collapse; font-family: Consolas, monospace; background-color: #2e2e2e; color: white;'>";
    for (size_t i = 0; i < matrix.size(); ++i) {
        html += "<tr>";
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            QString val = QString::number(matrix[i][j], 'g', 10); // 使用 'g' 以避免过多零
            html += QString("<td align='right'>%1</td>").arg(val);
        }
        html += "</tr>";
    }
    html += "</table>";

    browser->setHtml(html);
}

// 将数据显示到 QTableWidget (用于 JSON 加载后显示 A)
void MainWindow::displayMatrixInTable(QTableWidget* table, const std::vector<std::vector<double>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return;
    int rows = matrix.size();
    int cols = matrix[0].size();
    setTableSize(rows, cols); // 调整表格大小

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QString val = QString::number(matrix[i][j], 'g', 10);
            QTableWidgetItem* item = table->item(i, j);
            if (!item) {
                item = new QTableWidgetItem();
                table->setItem(i, j, item);
            }
            item->setText(val);
        }
    }
}

// 更新状态标签
void MainWindow::updateStatus(const QString& message, bool isError) {
    if (isError) {
        ui->lable_status->setStyleSheet("color: red;");
    } else {
        ui->lable_status->setStyleSheet("color: lime;"); // 成功使用亮绿色
    }

    // 显示当前加载的矩阵状态
    QString matrixA_info = g_loaded_data.is_A_loaded ? QString("%1x%2").arg(g_loaded_data.A.size()).arg(g_loaded_data.A[0].size()) : "Unloaded";
    QString matrixB_info = g_loaded_data.is_B_loaded ? QString("%1x%2").arg(g_loaded_data.B.size()).arg(g_loaded_data.B[0].size()) : "Unloaded";

    QString full_status = QString("Status: %1\nMatrix A: %2 | Matrix B: %3").arg(message).arg(matrixA_info).arg(matrixB_info);
    ui->lable_status->setText(full_status);
}

// 设置表格尺寸，并确保单元格存在
void MainWindow::setTableSize(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return;
    ui->InputMatrix->setRowCount(rows);
    ui->InputMatrix->setColumnCount(cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!ui->InputMatrix->item(i, j)) {
                ui->InputMatrix->setItem(i, j, new QTableWidgetItem("0.0"));
            }
        }
    }
    // 更新行/列输入框
    ui->lineEdit_rows->setText(QString::number(rows));
    ui->lineEdit_columns->setText(QString::number(cols));
}


// 适配 Qt 环境的 JSON 加载
std::vector<std::vector<double>> MainWindow::loadMatrixFromJSONFile() {
    // 使用 Qt 的文件对话框获取文件路径
    QString filePath = QFileDialog::getOpenFileName(this, "打开 JSON 矩阵文件", QString(), "JSON 文件 (*.json);;所有文件 (*.*)");

    if (filePath.isEmpty()) {
        throw std::runtime_error("文件导入已取消。");
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("无法打开文件。");
    }

    // 注意：使用 QJsonDocument 解析，因为在 GUI 中直接使用文件流更容易出错
    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isNull() || !doc.isArray()) {
        throw std::runtime_error("JSON 文件格式无效或根元素不是数组 (期望格式: [[1, 2], [3, 4]])。");
    }

    QJsonArray jsonArray = doc.array();
    if (jsonArray.isEmpty()) { throw std::runtime_error("JSON 矩阵为空。"); }

    size_t rows = jsonArray.size();
    if (!jsonArray[0].isArray()) { throw std::runtime_error("JSON 格式错误: 矩阵行不是数组。"); }
    size_t cols = jsonArray[0].toArray().size();
    if (cols == 0) { throw std::runtime_error("矩阵列数不能为零。"); }

    std::vector<std::vector<double>> matrix;
    matrix.resize(rows, std::vector<double>(cols));

    for (size_t i = 0; i < rows; ++i) {
        QJsonArray rowArray = jsonArray[i].toArray();
        if (rowArray.size() != (int)cols) {
            throw std::runtime_error(QString("矩阵行 %1 长度不一致。").arg(i+1).toStdString());
        }
        for (size_t j = 0; j < cols; ++j) {
            // Qt 的 toDouble 默认是安全的
            matrix[i][j] = rowArray[j].toDouble();
        }
    }
    return matrix;
}

// ----------------------------------------------------------------------
// 构造函数与槽函数实现
// ----------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 应用程序设置
    this->setWindowTitle("My Linear Algebra - GUI");
    ui->InputMatrix->setAlternatingRowColors(true);
    ui->OutputMatrix->setReadOnly(true);
    ui->OutputMatrix->setFontFamily("Consolas"); // 设置等宽字体

    //在Qt Designer中已经设计过了，不需要再设置一遍了，所以注释了
    // ui->qcb_operation->addItem("Choose one operation");
    // ui->qcb_operation->addItem("加载矩阵A(Load Matrix A)");
    // ui->qcb_operation->addItem("加载矩阵B(Load Matrix B)");
    // ui->qcb_operation->addItem("矩阵乘法 (A * B)");
    // ui->qcb_operation->addItem("矩阵转置 (A^T)");
    // ui->qcb_operation->addItem("高斯消元 (Gauss Elimination)");
    // ui->qcb_operation->addItem("高斯若尔当消元 (Gauss-Jordan Elimination)");
    // ui->qcb_operation->addItem("逆矩阵 (Inversed Matrix)");
    // ui->qcb_operation->addItem("行列式计算-莱布尼茨方法");
    // ui->qcb_operation->addItem("行列式计算-高斯消元方法");
    // ui->qcb_operation->addItem("LU 分解 (PA = LU)");

    // 初始化默认尺寸
    int initialSize = 3;
    setTableSize(initialSize, initialSize);
    updateStatus("Ready...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// JSON 导入槽函数 (Matrix A)
void MainWindow::on_actionLoad_Matrix_A_triggered()
{
    try {
        std::vector<std::vector<double>> loadedMatrix = loadMatrixFromJSONFile();

        g_loaded_data.A = loadedMatrix;
        g_loaded_data.is_A_loaded = true;

        displayMatrixInTable(ui->InputMatrix, loadedMatrix);

        updateStatus(QString("矩阵 A (大小: %1x%2) 从 JSON 成功加载。")
            .arg(loadedMatrix.size())
            .arg(loadedMatrix[0].size()));

    } catch (const std::exception& e) {
        updateStatus(QString("加载矩阵 A 失败: %1").arg(e.what()), true);
    }
}

// JSON 导入槽函数 (Matrix B)
void MainWindow::on_actionLoad_Matrix_B_triggered()
{
    try {
        std::vector<std::vector<double>> loadedMatrix = loadMatrixFromJSONFile();

        g_loaded_data.B = loadedMatrix;
        g_loaded_data.is_B_loaded = true;

        updateStatus(QString("矩阵 B (大小: %1x%2) 从 JSON 成功加载。").arg(loadedMatrix.size()).arg(loadedMatrix[0].size()));

    } catch (const std::exception& e) {
        updateStatus(QString("加载矩阵 B 失败: %1").arg(e.what()), true);
    }
}

// 尺寸控制槽函数：更新行数
void MainWindow::on_lineEdit_rows_editingFinished() {
    bool ok;
    int rows = ui->lineEdit_rows->text().toInt(&ok);
    int cols = ui->InputMatrix->columnCount();

    if (ok && rows > 0 && rows <= 50) { // 限制最大 50 维
        setTableSize(rows, cols);
        updateStatus(QString("行数已更新为 %1。").arg(rows));
    } else {
        ui->lineEdit_rows->setText(QString::number(ui->InputMatrix->rowCount()));
        updateStatus("行数输入无效 (需在 1-50 之间)。", true);
    }
}

// 尺寸控制槽函数：更新列数
void MainWindow::on_lineEdit_columns_editingFinished() {
    bool ok;
    int cols = ui->lineEdit_columns->text().toInt(&ok);
    int rows = ui->InputMatrix->rowCount();

    if (ok && cols > 0 && cols <= 50) {
        setTableSize(rows, cols);
        updateStatus(QString("列数已更新为 %1。").arg(cols));
    } else {
        ui->lineEdit_columns->setText(QString::number(ui->InputMatrix->columnCount()));
        updateStatus("列数输入无效 (需在 1-50 之间)。", true);
    }
}


// 核心计算逻辑槽函数
void MainWindow::on_pb_process_clicked()
{
    QString selectedOperation = ui->qcb_operation->currentText();
    std::vector<std::vector<double>> result_matrix;
    QString result_title = "";

    try {
        if (selectedOperation == "Choose one operation") {
            throw std::runtime_error("请在下拉框中选择一个有效的操作。");
        }

        // // 1. 从表格中读取矩阵 A 的当前值，并更新全局状态
        // g_loaded_data.A = readMatrixFromTable(ui->InputMatrix);
        // g_loaded_data.is_A_loaded = true;
        // // 清除上一次的矩阵 B 缓存
        // // g_loaded_data.is_B_loaded = false;
        // 1.实现从表格中加载矩阵A和矩阵B的操作
        if (selectedOperation == "加载矩阵A(Load Matrix A)") {
            g_loaded_data.A = readMatrixFromTable(ui->InputMatrix);
            g_loaded_data.is_A_loaded = true;
        }

        if (selectedOperation == "加载矩阵B(Load Matrix B)") {
            g_loaded_data.B = readMatrixFromTable(ui->InputMatrix);
            g_loaded_data.is_B_loaded = true;
        }


        // 2. 核心计算逻辑：调用您现有的 C++ 函数
        if (selectedOperation == "矩阵乘法 (A * B)") {
            if (!g_loaded_data.is_B_loaded) {
                throw std::runtime_error("执行 A * B 需要先通过菜单加载矩阵 B。");
            }
            if (g_loaded_data.A[0].size() != g_loaded_data.B.size()) {
                throw std::runtime_error("矩阵维度不匹配，A 的列数必须等于 B 的行数。");
            }
            result_matrix = matrix_multiply(g_loaded_data.A, g_loaded_data.B);
            result_title = "结果矩阵 C = A * B";

        } else if (selectedOperation == "矩阵转置 (A^T)") {
            result_matrix = matrix_transpose(g_loaded_data.A);
            result_title = "转置矩阵 A^T";

        } else if (selectedOperation == "高斯消元 (Gauss Elimination)") {
            std::vector<std::vector<double>> temp_A = g_loaded_data.A;
            gauss_elimination(temp_A); // 原地修改 temp_A
            result_matrix = temp_A;
            result_title = "高斯消元后的矩阵 (行阶梯形)";

        } else if (selectedOperation == "高斯若尔当消元 (Gauss-Jordan Elimination)") {
            std::vector<std::vector<double>> temp_A = g_loaded_data.A;
            gauss_jordan_elimination(temp_A); // 原地修改 temp_A
            result_matrix = temp_A;
            result_title = "高斯若尔当消元后的矩阵 (行最简形)";

        } else if (selectedOperation == "逆矩阵 (Inversed Matrix)") {
            result_matrix = inverse(g_loaded_data.A);
            result_title = "逆矩阵 A^-1";

        } else if (selectedOperation == "行列式计算-莱布尼茨方法(Determination Calculation - Leibniz)") {
            long double det = calculate_determinant_leibniz(g_loaded_data.A);
            QString html_result = QString("<h4 style='color: #eee;'>行列式 (莱布尼茨方法):</h4>"
                                         "<p style='color: white; font-size: 16px; font-family: Consolas, monospace;'>"
                                         "det(A) = %1</p>").arg(QString::number(det, 'g', 15));
            ui->OutputMatrix->setHtml(html_result);
            updateStatus("行列式计算成功。", false);
            return;

        } else if (selectedOperation == "行列式计算-高斯消元方法(Determination Calculation - Gauss)") {
            long double det = calculate_determinant_gauss(g_loaded_data.A);
            QString html_result = QString("<h4 style='color: #eee;'>行列式 (高斯方法):</h4>"
                                         "<p style='color: white; font-size: 16px; font-family: Consolas, monospace;'>"
                                         "det(A) = %1</p>").arg(QString::number(det, 'g', 15));
            ui->OutputMatrix->setHtml(html_result);
            updateStatus("行列式计算成功。", false);
            return;

        } else if (selectedOperation == "LU 分解 (LU Decomposition - PA = LU)") {
            std::vector<std::vector<double>> L, U;
            std::vector<int> P_vector;
            // lu_decomposition 可能会抛出异常或返回空矩阵
            lu_decomposition(g_loaded_data.A, L, U, P_vector);

            if (U.empty()) {
                throw std::runtime_error("LU 分解失败，请检查矩阵是否为方阵或是否奇异。");
            }

            QString lu_result;
            // 1. 显示 U 矩阵
            lu_result += QString("<h4 style='color: #eee;'>U 矩阵 (上三角):</h4>");
            lu_result += "<table border='1' cellpadding='5' style='border-collapse: collapse; font-family: Consolas, monospace; background-color: #2e2e2e; color: white; margin-bottom: 20px;'>";
            for (size_t i = 0; i < U.size(); ++i) {
                lu_result += "<tr>";
                for (size_t j = 0; j < U[0].size(); ++j) {
                    QString val = QString::number(U[i][j], 'g', 10);
                    lu_result += QString("<td align='right'>%1</td>").arg(val);
                }
                lu_result += "</tr>";
            }
            lu_result += "</table>";

            // 2. 显示 L 矩阵
            lu_result += QString("<h4 style='color: #eee;'>L 矩阵 (下三角):</h4>");
            lu_result += "<table border='1' cellpadding='5' style='border-collapse: collapse; font-family: Consolas, monospace; background-color: #2e2e2e; color: white; margin-bottom: 20px;'>";
            for (size_t i = 0; i < L.size(); ++i) {
                lu_result += "<tr>";
                for (size_t j = 0; j < L[0].size(); ++j) {
                    QString val = QString::number(L[i][j], 'g', 10);
                    lu_result += QString("<td align='right'>%1</td>").arg(val);
                }
                lu_result += "</tr>";
            }
            lu_result += "</table>";

            // 3. 显示 P 向量
            QString P_str = "";
            for (int p_val : P_vector) {
                P_str += QString::number(p_val + 1) + " "; // 显示 1-based 索引
            }
            lu_result += QString("<h4 style='color: #eee;'>P 向量 (行置换):</h4>"
                                "<p style='color: white; font-family: Consolas, monospace; font-size: 16px;'>%1</p>").arg(P_str.trimmed());
            
            ui->OutputMatrix->setHtml(lu_result);
            updateStatus("LU 分解成功完成 (PA = LU)。", false);
            return;
        }

        // 3. 显示结果矩阵 (适用于所有返回矩阵的操作)
        displayMatrixToTextBrowser(ui->OutputMatrix, result_matrix, result_title);

        // 4. 更新状态
        updateStatus(QString("操作 [%1] 成功完成。").arg(selectedOperation));

    } catch (const std::exception& e) {
        // 捕获所有 C++ 异常并显示在输出框中
        ui->OutputMatrix->setText(QString("<h3 style='color: red;'>计算错误：</h3><p>%1</p>").arg(e.what()));
        updateStatus(QString("操作失败: %1").arg(e.what()), true);
    }
}