/********************************************************************************
** Form generated from reading UI file 'MyLinearAlgebra.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYLINEARALGEBRA_H
#define UI_MYLINEARALGEBRA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Matrix_A;
    QAction *actionLoad_Matrix_B;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *lable_title;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lable_matrix;
    QHBoxLayout *horizontalLayout;
    QLabel *label_rows;
    QLineEdit *lineEdit_rows;
    QLabel *label_columns;
    QLineEdit *lineEdit_columns;
    QTableWidget *InputMatrix;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *lable_matrix_2;
    QTextBrowser *OutputMatrix;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *qcb_operation;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_process;
    QSpacerItem *verticalSpacer_2;
    QLabel *lable_status;
    QMenuBar *menubar;
    QMenu *menuMyLinearAlgebra;
    QMenu *menuOpen_JSON_Matrix;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(614, 453);
        MainWindow->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8("matrix_icon_137416.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        actionLoad_Matrix_A = new QAction(MainWindow);
        actionLoad_Matrix_A->setObjectName("actionLoad_Matrix_A");
        actionLoad_Matrix_B = new QAction(MainWindow);
        actionLoad_Matrix_B->setObjectName("actionLoad_Matrix_B");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        lable_title = new QLabel(centralwidget);
        lable_title->setObjectName("lable_title");
        QFont font;
        font.setFamilies({QString::fromUtf8("Script MT")});
        font.setPointSize(20);
        font.setBold(true);
        lable_title->setFont(font);
        lable_title->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        lable_title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(lable_title);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lable_matrix = new QLabel(centralwidget);
        lable_matrix->setObjectName("lable_matrix");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setItalic(true);
        lable_matrix->setFont(font1);

        verticalLayout->addWidget(lable_matrix);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_rows = new QLabel(centralwidget);
        label_rows->setObjectName("label_rows");

        horizontalLayout->addWidget(label_rows);

        lineEdit_rows = new QLineEdit(centralwidget);
        lineEdit_rows->setObjectName("lineEdit_rows");

        horizontalLayout->addWidget(lineEdit_rows);

        label_columns = new QLabel(centralwidget);
        label_columns->setObjectName("label_columns");

        horizontalLayout->addWidget(label_columns);

        lineEdit_columns = new QLineEdit(centralwidget);
        lineEdit_columns->setObjectName("lineEdit_columns");

        horizontalLayout->addWidget(lineEdit_columns);


        verticalLayout->addLayout(horizontalLayout);

        InputMatrix = new QTableWidget(centralwidget);
        InputMatrix->setObjectName("InputMatrix");

        verticalLayout->addWidget(InputMatrix);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        lable_matrix_2 = new QLabel(centralwidget);
        lable_matrix_2->setObjectName("lable_matrix_2");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Times New Roman")});
        font2.setPointSize(18);
        font2.setItalic(true);
        lable_matrix_2->setFont(font2);

        verticalLayout_2->addWidget(lable_matrix_2);

        OutputMatrix = new QTextBrowser(centralwidget);
        OutputMatrix->setObjectName("OutputMatrix");

        verticalLayout_2->addWidget(OutputMatrix);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        qcb_operation = new QComboBox(centralwidget);
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->addItem(QString());
        qcb_operation->setObjectName("qcb_operation");
        qcb_operation->setEnabled(true);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Times New Roman")});
        font3.setPointSize(14);
        font3.setItalic(true);
        qcb_operation->setFont(font3);
        qcb_operation->setInsertPolicy(QComboBox::InsertPolicy::InsertAlphabetically);

        horizontalLayout_3->addWidget(qcb_operation);

        horizontalSpacer = new QSpacerItem(78, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pb_process = new QPushButton(centralwidget);
        pb_process->setObjectName("pb_process");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Times New Roman")});
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setItalic(true);
        pb_process->setFont(font4);

        horizontalLayout_3->addWidget(pb_process);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        lable_status = new QLabel(centralwidget);
        lable_status->setObjectName("lable_status");
        lable_status->setFont(font3);
        lable_status->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        lable_status->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        verticalLayout_3->addWidget(lable_status);


        verticalLayout_4->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 614, 17));
        menuMyLinearAlgebra = new QMenu(menubar);
        menuMyLinearAlgebra->setObjectName("menuMyLinearAlgebra");
        menuOpen_JSON_Matrix = new QMenu(menuMyLinearAlgebra);
        menuOpen_JSON_Matrix->setObjectName("menuOpen_JSON_Matrix");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMyLinearAlgebra->menuAction());
        menuMyLinearAlgebra->addAction(menuOpen_JSON_Matrix->menuAction());
        menuOpen_JSON_Matrix->addAction(actionLoad_Matrix_A);
        menuOpen_JSON_Matrix->addAction(actionLoad_Matrix_B);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "My Linear Algebra", nullptr));
        actionLoad_Matrix_A->setText(QCoreApplication::translate("MainWindow", "Load Matrix A", nullptr));
        actionLoad_Matrix_B->setText(QCoreApplication::translate("MainWindow", "Load Matrix B", nullptr));
        lable_title->setText(QCoreApplication::translate("MainWindow", "My Linear Algebra", nullptr));
        lable_matrix->setText(QCoreApplication::translate("MainWindow", "Input your matrix here...", nullptr));
        label_rows->setText(QCoreApplication::translate("MainWindow", "Rows", nullptr));
        label_columns->setText(QCoreApplication::translate("MainWindow", "Columns", nullptr));
        lable_matrix_2->setText(QCoreApplication::translate("MainWindow", "Get your results here...", nullptr));
        qcb_operation->setItemText(0, QCoreApplication::translate("MainWindow", "Choose one operation", nullptr));
        qcb_operation->setItemText(1, QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\347\237\251\351\230\265A(Load Matrix A)", nullptr));
        qcb_operation->setItemText(2, QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\347\237\251\351\230\265B(Load Matrix B)", nullptr));
        qcb_operation->setItemText(3, QCoreApplication::translate("MainWindow", "\347\237\251\351\230\265\344\271\230\346\263\225 (A * B)", nullptr));
        qcb_operation->setItemText(4, QCoreApplication::translate("MainWindow", "\347\237\251\351\230\265\350\275\254\347\275\256 (A^T)", nullptr));
        qcb_operation->setItemText(5, QCoreApplication::translate("MainWindow", "\351\253\230\346\226\257\346\266\210\345\205\203 (Gauss Elimination)", nullptr));
        qcb_operation->setItemText(6, QCoreApplication::translate("MainWindow", "\351\253\230\346\226\257\350\213\245\345\260\224\345\275\223\346\266\210\345\205\203 (Gauss-Jordan Elimination)", nullptr));
        qcb_operation->setItemText(7, QCoreApplication::translate("MainWindow", "\351\200\206\347\237\251\351\230\265 (Inversed Matrix)", nullptr));
        qcb_operation->setItemText(8, QCoreApplication::translate("MainWindow", "\350\241\214\345\210\227\345\274\217\350\256\241\347\256\227-\350\216\261\345\270\203\345\260\274\350\214\250\346\226\271\346\263\225(Determination Calculation - Leibniz)", nullptr));
        qcb_operation->setItemText(9, QCoreApplication::translate("MainWindow", "\350\241\214\345\210\227\345\274\217\350\256\241\347\256\227-\351\253\230\346\226\257\346\266\210\345\205\203\346\226\271\346\263\225(Determination Calculation - Gauss)", nullptr));
        qcb_operation->setItemText(10, QCoreApplication::translate("MainWindow", "LU \345\210\206\350\247\243 (LU Decomposition - PA = LU)", nullptr));

        qcb_operation->setCurrentText(QCoreApplication::translate("MainWindow", "Choose one operation", nullptr));
        pb_process->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        lable_status->setText(QCoreApplication::translate("MainWindow", "Ready...\n"
"Matrix A: Unloaded Matrix B: Unloaded", nullptr));
        menuMyLinearAlgebra->setTitle(QCoreApplication::translate("MainWindow", "MyLinearAlgebra", nullptr));
        menuOpen_JSON_Matrix->setTitle(QCoreApplication::translate("MainWindow", "Open JSON Matrix...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYLINEARALGEBRA_H
