#ifndef TEXT_READ_H
#define TEXT_READ_H
#include "SignalComtr.hpp"

class Text_read
{
public:

	unsigned short sign_quantity;
	std::string Text_read_SIGCC = "";
        float Text_read_SIGA = 0.001;
	float Text_read_SIGB = 0.0;
	float Text_read_SIGSKEW = 0.0;
	char Text_read_SIGTYPE = 'A';
	float Text_read_SIGM = 0;
    unsigned int Primary_CT = 12000;
    unsigned int Secondary_CT = 1;
     unsigned int Primary_VT = 20000;
     unsigned int Secondary_VT = 100;
    float Kct = Primary_CT/Secondary_CT;
    float Kvt = Primary_VT/Secondary_VT;
	unsigned long n_sampl;//количество отсчетов
	unsigned long f_sampl;//частота дискретизации

	std::string needle_Data = "Actual Waveform Values";
	std::string needle_maxTime = "Maximum Run Time";
	std::string needle_startTime = "Output Start Time";
	std::string needle_dT = "Maximum Time Step";

	unsigned long inf_maxTime_beg = 0;
	unsigned long inf_startTime_beg = 0;
	unsigned long inf_dT_beg = 0;
	unsigned long resnum_beg = 0;

	double d_maxTime = 0.0;
	double d_startTime = 0.0;
	double d_dT_beg = 0.0;
	bool secondary_side;
	unsigned short nrates = 1;//	количество различных скоростей дискретизации в файле данных
	Text_read(std::string nameFile, std::string strPath, bool in_secondary_side, unsigned short in_sign_quantity);
	QVector<SignalComtr> ArrSignal;
};

inline float get_value(std::string str, int ind_inf_beg);
inline float get_value(std::string str, int ind_inf_beg, unsigned short& shift);
inline void name_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, unsigned short& sig_num);
inline void data_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, unsigned short s_quantity,
					   unsigned int& str_n, unsigned short& col_n, bool in_secondary_side, float in_Kvt, float in_Kct);
#endif // TEXT_READ_H
