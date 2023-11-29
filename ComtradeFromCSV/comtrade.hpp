#ifndef COMTRADE_HPP
#define COMTRADE_HPP
#include <string>
#include <QObject>
#include "SignalComtr.hpp"
//1.Формат записываемого файла в ПК Simulink для записи в формат COMTRADE:
//1.1.Запись данных в модели ПК Simulink должна делаться с использованием
//    блоков "BusCreator" и "To Workspace"
//1.2.Первым записывается время с заданной дискретизацией выборки
//  "Sample Time"
//1.3.Запись остальных сигналов делается в произвольном порядке
//1.4.Дискретные переменные и сигналы должны быть переведены в формат
//    "double"
//1.5.Все сигналы, собираемые блоком "Bus Creator" должны иметь название,
//    формат которого описан ниже

//2.Формат наименованя измеряемых величин для их записи в формат COMTRADE:
//2.1.Названия дискретных сигналов начинаются с нижнего подчеркивания "_"

//2.2.Названия напряжений начинаются с U, далее следует наименование фазы с
//  маленькой буквы, далее - любые символы: "Ua" - напряжение фазы А.

//2.3.Названия токов начинаются с I, далее следует наименование фазы с
//  маленькой буквы, далее - любые символы: "Ia" - ток фазы А.
class Comtrade
{
private:
	unsigned short f_network;   //базовая частота сети
    QVector<float> time;
	unsigned long f_sampl;
	unsigned long n_sampl;
	unsigned short sign_quantity;
	unsigned short nrates;
public:
	Comtrade(std::string& in_strPath, std::string& in_FileName, unsigned short in_Fnetwork, QVector<SignalComtr>& in_signal,
			 unsigned long in_n_sampl, unsigned long in_f_sampl, unsigned short in_sign_quantity, unsigned short in_nrates);
	void CfgFilePrint(QVector<SignalComtr>& in_signal, char c_Path_comtrade[], char basename_comtrade[]);
	void DatFilePrint(QVector<SignalComtr>& in_signal, char c_Path_comtrade[], char basename_comtrade[]);
};

#endif // COMTRADE_HPP
