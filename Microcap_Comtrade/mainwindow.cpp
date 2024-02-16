#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Text_read.hpp"
#include "Comtrade.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pB_Apply_clicked()
{

    if (strPath_microcap == "")
    {
        strPath_microcap = "D:\\work\\Microcap_Comtrade\\";
        ui->lE_strPath_microcap->setText(strPath_microcap);
    }
    if (file_microcap_name == "")
    {
        file_microcap_name = "GenTrans_v2_TGV300";
        ui->lE_file_microcap_name->setText(file_microcap_name);
    }
    if (strPath_comtrade == "")
    {
        strPath_comtrade = "D:\\work\\Microcap_Comtrade\\Comtrade_Microcap_files\\";
        ui->lE_strPath_comtrade->setText(strPath_comtrade);
    }
    if (file_comtrade_name == "")
    {
        file_comtrade_name = "TestComtradeMicrocap";
        ui->lE_file_comtrade_name->setText(file_comtrade_name);
    }

    bool secondary_side = 1;
    unsigned  short sign_quantity = 11;
    std::string str_tmp_path = strPath_microcap.toLocal8Bit().constData();
    std::string str_tmp_name = file_microcap_name.toLocal8Bit().constData();

    Text_read TR(str_tmp_path, str_tmp_name, secondary_side, sign_quantity);

    str_tmp_path = strPath_comtrade.toLocal8Bit().constData();
    str_tmp_name = file_comtrade_name.toLocal8Bit().constData();
    Comtrade file_comtrade (str_tmp_path, str_tmp_name, 50, TR.ArrSignal, TR.n_sampl, TR.f_sampl, TR.sign_quantity, TR.nrates);
}

void MainWindow::on_lE_strPath_microcap_textChanged(const QString &arg1)
{
    strPath_microcap = ui->lE_strPath_microcap->text();
}
void MainWindow::on_lE_file_microcap_name_textChanged(const QString &arg1)
{
    file_microcap_name = ui->lE_file_microcap_name->text();
}
void MainWindow::on_lE_strPath_comtrade_textChanged(const QString &arg1)
{
    strPath_comtrade = ui->lE_strPath_comtrade->text();
}
void MainWindow::on_lE_file_comtrade_name_textChanged(const QString &arg1)
{
    file_comtrade_name = ui->lE_file_comtrade_name->text();
}

