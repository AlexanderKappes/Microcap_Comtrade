#ifndef SIGNALCOMTR_H
#define SIGNALCOMTR_H
#include <QObject>

class SignalComtr
{
public:
    std::string sig_id;
    char sig_ph;
    std::string sig_cc;
    std::string sig_uu;
    float sig_a;
    float sig_b;
    float sig_skew;
    QVector<float> sig_data;
    QVector<float> sig_time;
    float sig_min;
    float sig_max;
    char sig_type;
    float sig_m;
    unsigned short sig_num;
	SignalComtr();
	~SignalComtr();
};

#endif // SIGNALCOMTR_H
