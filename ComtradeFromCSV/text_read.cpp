#include "text_read.hpp"

double get_value(std::string str, int ind_inf_beg)
{
    int j = 0;
	char tmp[10] {0};//для чтения цифр
    std::string::iterator  it = std::find_if( str.begin() + ind_inf_beg, str.end(), isdigit );
    int p = it - str.begin();//index = someIterator - vec.begin() ИЛИ index = std::distance(vec.begin(), someIterator);
	while (str[p] != '\n' && str[p] != ' ') {tmp[j] = str[p]; j++; p++;}
	return std::stod(tmp);
}

Text_read::Text_read(std::string nameFile, std::string strPath)
{
	std::string tmp_str, res;
	std::ifstream file_r(strPath+nameFile+".txt");
	while(getline(file_r, tmp_str))
	{
		res += tmp_str;
		res += '\n';
	}

    std::string needle_Data = "Actual Waveform Values";
    std::string needle_maxTime = "Maximum Run Time";
    std::string needle_startTime = "Output Start Time";
    std::string needle_dT = "Maximum Time Step";

    int inf_maxTime_beg = res.find(needle_maxTime);
    inf_maxTime_beg = inf_maxTime_beg + needle_maxTime.length();
    int inf_startTime_beg = res.find(needle_startTime);
    inf_startTime_beg = inf_startTime_beg + needle_startTime.length() ;
    int inf_dT_beg = res.find(needle_dT);
    inf_dT_beg = inf_dT_beg + needle_dT.length();
    int resnum_beg = res.find(needle_Data);
    resnum_beg = resnum_beg + needle_Data.length() + 1; // +1, т.к. еще "/n"

    double d_maxTime = get_value(res, inf_maxTime_beg);
    double d_startTime = get_value(res, inf_startTime_beg);
    double d_dT_beg = get_value(res, inf_dT_beg);

    while (res[resnum_beg++] == '='){}
		resnum_beg += 11;//11 символов до буквы T

    unsigned int j =0;
    unsigned int str_num = 0;
    unsigned int col_num = 0;
	//unsigned int res_data_len= res.length() - resnum_beg;
	//char *res_data = new char [res_data_len];
	Signal* ArrSignal = new Signal [sign_quantity];//ВРЕМЕННОЕ РЕШЕНИЕ, КОЛЛИЧЕСТВО СИГНАЛОВ ДОЛЖНО ОПРЕДЕЛЯТЬСЯ ИЗ ТЕКСТА
	const int num_tmp_ch = 20;
	char* tmp_ch = new char [num_tmp_ch];//для чтения цифр
	int signal_num = 0;
    double data_tmp = 0;

	for (int k = 0; k < sign_quantity; k++)
	{
		ArrSignal[k].SIGCC = Text_read_SIGCC;
		ArrSignal[k].SIGB = Text_read_SIGB;
		ArrSignal[k].SIGSKEW = Text_read_SIGSKEW;
		ArrSignal[k].SIGTYPE = Text_read_SIGTYPE;
		ArrSignal[k].SIGM = Text_read_SIGM;
	}

    for (unsigned int i = resnum_beg; i < res.length(); i++)
	{
		if ((res[i] == 'i'&& res[i+1] == '(')|| (res[i] == 'v'&& res[i+1] == '(')){
            if (res[i] == 'i')
            {
                ArrSignal[signal_num].SIGUU = 'A';
                ArrSignal[signal_num].SIGA = Kct;
            }
            if (res[i] == 'v')
            {
                ArrSignal[signal_num].SIGUU = 'V';
                ArrSignal[signal_num].SIGA = Kvt;
            }
			while (res[i] != ' ') {
				tmp_ch [j] = res[i];
				if (tmp_ch [j] == '(')
					tmp_ch [j] = '_';
				if (tmp_ch [j] == ')')
				{
					ArrSignal[signal_num].SIGPH = tmp_ch [j - 1];
					tmp_ch [j] = '\0';
				}
				i++; j++;
			}
			ArrSignal[signal_num].SIGPH = res[i - 2];
			ArrSignal[signal_num].SIGID = std::string(tmp_ch);
			j = 0;
			for (int k = 0; k < 20; k++)
			{
				tmp_ch [k] = {0};
			}
		}
        if (str_num > 0)
        {
            data_tmp = get_value(res, i);

            int check = 0;
        }
		if (res[i] == '\n')
			str_num++;

	}

	int check = 0;
}
