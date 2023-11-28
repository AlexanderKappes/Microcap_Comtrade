#ifndef SIGNALCOMTR_H
#define SIGNALCOMTR_H
#include <fstream>
#include <QObject>

class SignalComtr
{
public:
	std::string SIGID;
	char SIGPH;
	std::string SIGCC;
	std::string SIGUU;
	float SIGA;
	float SIGB;
	float SIGSKEW;
	QVector<float> SIGDATA;
	QVector<float> TIME;
	float SIGMIN;
	float SIGMAX;
	char SIGTYPE;
	float SIGM;
	int SIGNUM;
	SignalComtr();
	~SignalComtr();
};

#endif // SIGNALCOMTR_H
