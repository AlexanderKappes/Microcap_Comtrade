#include "Text_read.hpp"

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
inline void name_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, float K_CT, float K_VT, unsigned short& sig_num)
{
	char tmp_ch[20] {0};//для чтения цифр
	unsigned int j =0;
	if (stream[i] == 'i')
	{
		ASignal[sig_num].SIGUU = 'A';
		ASignal[sig_num].SIGA = K_CT;
	}
	if (stream[i] == 'v')
	{
		ASignal[sig_num].SIGUU = 'V';
		ASignal[sig_num].SIGA = K_VT;
	}
	while (stream[i] != ' ') {
		tmp_ch [j] = stream[i];
		if (tmp_ch [j] == '(')
			tmp_ch [j] = '_';
		if (tmp_ch [j] == ')')
		{
			ASignal[sig_num].SIGPH = tmp_ch [j - 1];
			tmp_ch [j] = '\0';
		}
		i++; j++;
	}
	ASignal[sig_num].SIGPH = stream[i - 2];
	ASignal[sig_num].SIGID = std::string(tmp_ch);
	ASignal[sig_num].SIGNUM = sig_num;
	sig_num++;
}

inline void data_setup(QVector<SignalComtr>& ASignal, unsigned long& i, std::string& stream, unsigned short s_quantity, 	unsigned int& str_n, unsigned short& col_n)
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
			{ ASignal[k].TIME[str_n-1] = data_tmp*pow(10, ten_degree);}//Время
		}
		else
		{
			ASignal[col_n - 1].SIGDATA[str_n-1] = data_tmp*pow(10, ten_degree);//Значение
		}
		col_n++;
	}
}

Text_read::Text_read(std::string nameFile, std::string strPath)
{
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

	number_of_lines = ((d_maxTime- d_startTime)/ d_dT_beg)+1;

    while (res[resnum_beg++] == '='){}
		resnum_beg += 11;//11 символов до буквы T

	unsigned int str_num = 0;
	unsigned short col_num = 0;

	for (unsigned short k = 0; k < sign_quantity; k++)
	{
		ArrSignal[k].SIGCC = Text_read_SIGCC;
		ArrSignal[k].SIGB = Text_read_SIGB;
		ArrSignal[k].SIGSKEW = Text_read_SIGSKEW;
		ArrSignal[k].SIGTYPE = Text_read_SIGTYPE;
		ArrSignal[k].SIGM = Text_read_SIGM;
		ArrSignal[k].TIME.resize(number_of_lines);
		ArrSignal[k].SIGDATA.resize(number_of_lines);
	}

	for (unsigned long i = resnum_beg; i < res.length(); i++)
	{
		if (str_num == 0)
		{
			if ((res[i] == 'i'&& res[i+1] == '(')|| (res[i] == 'v'&& res[i+1] == '('))
			{
				name_setup(ArrSignal, i, res, Kct, Kvt, col_num);
			}
		}
		if (str_num > 0 && col_num < (sign_quantity +1))
        {
			data_setup(ArrSignal, i, res,  sign_quantity, str_num, col_num);
		}
		if (res[i] == '\n')
		{
			str_num++;
			col_num = 0;
		}
		if (str_num == number_of_lines + 1)
		{
			break;
		}
	}

	for (unsigned short k = 0; k < sign_quantity; k++)
	{
		float max = ArrSignal[k].SIGDATA[0];
		float min = ArrSignal[k].SIGDATA[0];
		for(unsigned long i = 0; i < number_of_lines; i++)
		{
			if (ArrSignal[k].SIGDATA[i] > max)
			{
				ArrSignal[k].SIGMAX = ArrSignal[k].SIGDATA[i];
			}
			if (ArrSignal[k].SIGDATA[i] < min)
			{
				ArrSignal[k].SIGMIN = ArrSignal[k].SIGDATA[i];
			}
		}
	}

	int check = 2;
}
