#include "mainwindow.h"
#include <QApplication>
#include "Text_read.hpp"
#include "Comtrade.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	std::string strPath_microcap = "D:\\work\\Microcap_Comtrade\\";
	std::string file_microcap_name = "GenTrans_v2_TGV300";

	std::string strPath_comtrade = "D:\\work\\Comtrade_Microcap_files\\";
	std::string file_comtrade_name = "TestComtradeMicrocap";
	bool secondary_side = 1;
	unsigned  short sign_quantity = 11;
	Text_read TR(file_microcap_name, strPath_microcap, secondary_side, sign_quantity);

	Comtrade file_comtrade (strPath_comtrade, file_comtrade_name, 50, TR.ArrSignal, TR.n_sampl, TR.f_sampl, TR.sign_quantity, TR.nrates);
	return a.exec();
}
