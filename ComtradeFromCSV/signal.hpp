#ifndef SIGNAL_HPP
#define SIGNAL_HPP
#include "Header.h"

class Signal
{
public:
	std::string SIGID; //имя сигнала
	float SIGPH;  //фаза сигнала
	float SIGCC;  //привязка сигнала к объекту, например, линии МКПА-2
	float SIGUU;  //единицы измерения сигнала
	float SIGA;   //коэффициент калибровки сигнала
	float SIGB;   //коэффициент смещения сигнала
	float SIGSKEW;//коэффициент компенсации фазовой задержки АЦП
	float SIGDATA;//выборка значений сигнала
	float TIME;   //моменты времени снятия значений выборки сигнала
	float SIGMIN; //минимальное значение сигнала
	float SIGMAX; //максимальное значение сигнала
	float SIGTYPE;//тип сигнала
	float SIGM;   //нормальное состояние дискретного сигнала (0 или 1)
	Signal();
};

#endif // SIGNAL_HPP
