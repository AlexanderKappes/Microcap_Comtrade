#include "mainwindow.h"
#include <QApplication>
#include "Text_read.hpp"
#include "Comtrade.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	Text_read TR("GenTrans_v2_TGV300", "D:\\work\\Microcap_Comtrade\\");
    Comtrade file_comtrade ("GenTrans_v2_TGV300", 50, TR.ArrSignal, TR.number_of_lines);
	return a.exec();
}
