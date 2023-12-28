#include "Text_read.hpp"
#include <fstream>
#include <cmath>

inline float get_value(std::string& str, unsigned long ind_inf_beg)
{
    int j = 0;
	char tmp[10] {0};//для чтения цифр
    std::string::iterator  it = std::find_if( str.begin() + ind_inf_beg, str.end(), isdigit );
    int p = it - str.begin();//index = someIterator - vec.begin() ИЛИ index = std::distance(vec.begin(), someIterator);
	while (str[p] != '\n' && str[p] != ' ') {tmp[j] = str[p]; j++; p++;}
	return std::stof(tmp);
}

///Чтение цифры в экспонен
inline float get_value(std::string& str, unsigned long ind_inf_beg, unsigned short& shift)
{
	int j = 0;
	char tmp[10] {0};//для чтения цифр
	std::string::iterator  it = std::find_if( str.begin() + ind_inf_beg, str.end(), isdigit);
	int p = it - str.begin();//index = someIterator - vec.begin() ИЛИ index = std::distance(vec.begin(), someIterator);
	if (str[p-1] == '-' || str[p-1] == '+') p --;
	while (str[p] != 'E') {tmp[j] = str[p]; j++; p++;}
	shift = j;
	return std::stof(tmp);
}

///Обработка первой строки
inline void name_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, unsigned short& sig_num)
{
	char tmp_ch[20] {0};//для чтения цифр
	unsigned int j =0;
	if (stream[i] == 'i')
	{
        ASignal[sig_num].sig_uu = 'A';
	}
	if (stream[i] == 'v')
	{
        ASignal[sig_num].sig_uu = 'V';
	}
	while (stream[i] != ' ') {
		tmp_ch [j] = stream[i];
		if (tmp_ch [j] == '(')
			tmp_ch [j] = '_';
		if (tmp_ch [j] == ')')
		{
            ASignal[sig_num].sig_ph = tmp_ch [j - 1];
			tmp_ch [j] = '\0';
		}
		i++; j++;
	}
    ASignal[sig_num].sig_ch_id = std::string(tmp_ch);
    ASignal[sig_num].sig_num = sig_num;
	sig_num++;
}

inline void data_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, unsigned short s_quantity,
					   unsigned int& str_n, unsigned short& col_n, bool in_secondary_side, float in_Kvt, float in_Kct)
{
	if (stream[i] != ' ')
	{
		float data_tmp = 0;
		unsigned short shift_value = 0;
		int ten_degree = 0;
		data_tmp = get_value(stream, i, shift_value);
		i +=shift_value;
		if (stream[i] == 'E')
		{
			if (stream[i+1] == '+')
				ten_degree = (10*((int)stream[i+2] - 48) + ((int)stream[i+3]-48));
			if (stream[i+1] == '-')
				ten_degree = -1*(10*((int)stream[i+2] - 48) + ((int)stream[i+3]-48));
			i += 3;
		}
		if (col_n == 0)
		{
			for (unsigned short k = 0; k < s_quantity; k++)
            { ASignal[k].sig_time[str_n-1] = data_tmp*pow(10, ten_degree);}//Время
		}
		else
		{
		   if (in_secondary_side && ASignal[col_n - 1].sig_uu == "V")
			{
			   ASignal[col_n - 1].sig_data[str_n-1] = data_tmp*pow(10, ten_degree)/in_Kvt;//Значение
		   }
		   else if (in_secondary_side && ASignal[col_n - 1].sig_uu == "A")
		   {
			   ASignal[col_n - 1].sig_data[str_n-1] = data_tmp*pow(10, ten_degree)/in_Kct;
		   }
		   else if (!in_secondary_side)
		   {
               ASignal[col_n - 1].sig_data[str_n-1] = data_tmp*pow(10, ten_degree);
		   }
		}
		col_n++;
	}
}

Text_read::Text_read(std::string nameFile, std::string strPath, bool in_secondary_side, unsigned short in_sign_quantity)
{
	sign_quantity = in_sign_quantity;
	secondary_side = in_secondary_side;
	ArrSignal.resize(sign_quantity);
	std::string tmp_str, res;
	std::ifstream file_r(strPath+nameFile+".txt");
	while(getline(file_r, tmp_str))
	{
		res += tmp_str;
		res += '\n';
	}

	inf_maxTime_beg = res.find(needle_maxTime) + needle_maxTime.length();
	inf_startTime_beg = res.find(needle_startTime) + needle_startTime.length() ;
	inf_dT_beg = res.find(needle_dT) + needle_dT.length();
	resnum_beg = res.find(needle_Data) + needle_Data.length() + 1; // +1, т.к. еще "/n"

	d_maxTime = get_value(res, inf_maxTime_beg);
	d_startTime = get_value(res, inf_startTime_beg);
	d_dT_beg = get_value(res, inf_dT_beg);

	n_sampl = ((d_maxTime- d_startTime)/ d_dT_beg)+1;
	f_sampl = 1/d_dT_beg;

	while (res[resnum_beg++] != 'T'){}

	unsigned int str_num = 0;
	unsigned short col_num = 0;
	unsigned short sig_num = 0;

	for (unsigned short k = 0; k < sign_quantity; k++)
	{
      ArrSignal[k].sig_ccbm = Text_read_SIGCC;
      ArrSignal[k].sig_a = Text_read_SIGA;
      ArrSignal[k].sig_b = Text_read_SIGB;
      ArrSignal[k].sig_skew = Text_read_SIGSKEW;
      ArrSignal[k].sig_type = Text_read_SIGTYPE;
      ArrSignal[k].sig_m = Text_read_SIGM;
    ArrSignal[k].sig_time.resize(n_sampl);
    ArrSignal[k].sig_data.resize(n_sampl);
	}

	for (unsigned long i = resnum_beg; i < res.length(); i++)
	{
		if (str_num == 0)
		{
			if ((res[i] == 'i'&& res[i+1] == '(')|| (res[i] == 'v'&& res[i+1] == '('))
			{
				name_setup(ArrSignal, i, res, sig_num);
			}
		}
		if (str_num > 0 && col_num < (sign_quantity +1))
        {
			data_setup(ArrSignal, i, res,  sign_quantity, str_num, col_num, secondary_side, Kvt, Kct);
		}
		if (res[i] == '\n')
		{
			str_num++;
			col_num = 0;
		}
		if (str_num == n_sampl + 1)
		{
			break;
		}
	}

	for (unsigned short k = 0; k < sign_quantity; k++)
	{
        float max = ArrSignal[k].sig_data[0];
        float min = ArrSignal[k].sig_data[0];
		for(unsigned long i = 0; i < n_sampl; i++)
		{
            if (ArrSignal[k].sig_data[i] > max)
			{
                ArrSignal[k].sig_max = ArrSignal[k].sig_data[i];
			}
            if (ArrSignal[k].sig_data[i] < min)
			{
                ArrSignal[k].sig_min = ArrSignal[k].sig_data[i];
			}
		}
        if(ArrSignal[k].sig_uu == "A")
        {
            ArrSignal[k].sig_primary = Primary_CT;
            ArrSignal[k].sig_secondary = Secondary_CT;
        }
        else if (ArrSignal[k].sig_uu == "V")
        {
            ArrSignal[k].sig_primary = Primary_VT;
            ArrSignal[k].sig_secondary = Secondary_VT;
        }
        else{
            ArrSignal[k].sig_primary = 1;
            ArrSignal[k].sig_secondary = 1;
        }
	}
}
