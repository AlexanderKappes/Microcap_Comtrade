#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

    Text_read TR("GenTrans_v2_TGV300", "D:\\work\\Microcap_osc\\");
	return a.exec();
}
