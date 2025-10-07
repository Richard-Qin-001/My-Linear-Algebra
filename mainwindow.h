#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTextBrowser>
#include <vector>
#include <string>
#include "matrix_options_base.h" // 核心函数声明


// UIC 自动生成的头文件
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // QWidget *parent = nullptr 是 Qt 构造函数的标准写法
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 对应 Process 按钮的槽函数
    void on_pb_process_clicked();

    // 菜单栏 -> Open JSON Matrix -> Load Matrix A
    void on_actionLoad_Matrix_A_triggered();
    // 菜单栏 -> Open JSON Matrix -> Load Matrix B
    void on_actionLoad_Matrix_B_triggered();

    // 尺寸输入框编辑完成槽函数
    void on_lineEdit_rows_editingFinished();
    void on_lineEdit_columns_editingFinished();

private:
    // 自动生成的 UI 类指针
    Ui::MainWindow *ui;

    // 辅助函数声明
    std::vector<std::vector<double>> readMatrixFromTable(QTableWidget* table);
    void displayMatrixToTextBrowser(QTextBrowser* browser, const std::vector<std::vector<double>>& matrix, const QString& title);
    void displayMatrixInTable(QTableWidget* table, const std::vector<std::vector<double>>& matrix);
    void updateStatus(const QString& message, bool isError = false);
    void setTableSize(int rows, int cols);

    // 适配 Qt 环境的 JSON 加载
    std::vector<std::vector<double>> loadMatrixFromJSONFile();
};

#endif // MAINWINDOW_H