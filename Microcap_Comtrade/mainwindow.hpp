#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString strPath_microcap;
    QString file_microcap_name;

    QString strPath_comtrade;
    QString file_comtrade_name;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pB_Apply_clicked();

    void on_lE_strPath_microcap_textChanged(const QString &arg1);

    void on_lE_file_microcap_name_textChanged(const QString &arg1);

    void on_lE_strPath_comtrade_textChanged(const QString &arg1);

    void on_lE_file_comtrade_name_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
