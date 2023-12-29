/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pB_Apply;
    QLineEdit *lE_strPath_microcap;
    QLineEdit *lE_file_microcap_name;
    QLineEdit *lE_strPath_comtrade;
    QLineEdit *lE_file_comtrade_name;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 281, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 281, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 281, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 160, 281, 16));
        pB_Apply = new QPushButton(centralwidget);
        pB_Apply->setObjectName("pB_Apply");
        pB_Apply->setGeometry(QRect(10, 220, 151, 24));
        lE_strPath_microcap = new QLineEdit(centralwidget);
        lE_strPath_microcap->setObjectName("lE_strPath_microcap");
        lE_strPath_microcap->setGeometry(QRect(10, 30, 281, 24));
        lE_file_microcap_name = new QLineEdit(centralwidget);
        lE_file_microcap_name->setObjectName("lE_file_microcap_name");
        lE_file_microcap_name->setGeometry(QRect(10, 80, 281, 24));
        lE_strPath_comtrade = new QLineEdit(centralwidget);
        lE_strPath_comtrade->setObjectName("lE_strPath_comtrade");
        lE_strPath_comtrade->setGeometry(QRect(10, 130, 281, 24));
        lE_file_comtrade_name = new QLineEdit(centralwidget);
        lE_file_comtrade_name->setObjectName("lE_file_comtrade_name");
        lE_file_comtrade_name->setGeometry(QRect(10, 180, 281, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203 \320\276\321\201\321\206\320\270\320\273\320\273\320\276\320\263\321\200\320\260\320\274\320\274 \320\270\320\267 Microcap", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\204\320\260\320\271\320\273\320\260 Microcap", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \320\277\320\260\320\277\320\272\320\265 \320\264\320\273\321\217 \321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265 COMTRADE \321\204\320\260\320\271\320\273\320\276\320\262", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 COMTRADE \321\204\320\260\320\271\320\273\320\260", nullptr));
        pB_Apply->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        lE_file_comtrade_name->setText(QCoreApplication::translate("MainWindow", "SDGDJHRTJRJDFDFHDFHDFHFGHTGFH", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
