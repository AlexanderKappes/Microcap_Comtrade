#ifndef TEXT_READ_H
#define TEXT_READ_H
#include "SignalComtr.hpp"

class Text_read
{
public:
	Text_read(std::string nameFile, std::string strPath);

	const unsigned short sign_quantity = 8;
	std::string Text_read_SIGCC = "";
	float Text_read_SIGB = 0.0;
	float Text_read_SIGSKEW = 0.0;
	char Text_read_SIGTYPE = 'A';
	float Text_read_SIGM = 0;
	float Kct = 12000;
	float Kvt = 20000/100;
	unsigned long number_of_lines;

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

	QVector<SignalComtr> ArrSignal;
	SignalComtr h;
};

inline float get_value(std::string str, int ind_inf_beg);
inline float get_value(std::string str, int ind_inf_beg, unsigned short& shift);
inline void name_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, float K_CT, float K_VT, unsigned short& sig_num);
inline void data_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, unsigned short s_quantity, unsigned int& str_n, unsigned short& col_n);
#endif // TEXT_READ_H
