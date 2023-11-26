#include "text_read.h"

double get_value(std::string str, int ind_inf_beg)
{
    int j = 0;
    char tmp2[10] {0};//для чтения цифр
    std::string::iterator  it = std::find_if( str.begin() + ind_inf_beg, str.end(), isdigit );
    int p = it - str.begin();//index = someIterator - vec.begin() ИЛИ index = std::distance(vec.begin(), someIterator);
    while (str[p] != '\n' && str[p] != ' ') {tmp2[j] = str[p]; j++; p++;}
    return std::stod(tmp2);
}
Text_read::Text_read(std::string nameFile, std::string strPath)
{
    std::string tmp1, res, res_data;



	std::ifstream file_r(strPath+nameFile+".txt");
    while(getline(file_r, tmp1))
	{
        res += tmp1;
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
    unsigned int str_num = 1;
    for (unsigned int i = resnum_beg; i < res.length(); i++)
	{
        if (res[i] == '\n') str_num++;
        char check2 = res[i];
		res_data[j++] = res[i];
	}

	int check = 0;
	/*for (unsigned int i = 0; i < res.length(); i++)
	{

		if (res [i] != ' ')
		{
			numberChar[n1] = res [i];
			n1++;
		}
		if (res [i] == '\n' &&  numCount == 1)
		{
			N = std::stof(numberChar);
			numCount++;
			n1 = n1 + 3;//два пробела и перенос
			break;
		}

		if (res [i] == ' ' &&  numCount == 0)
		{
			M = std::stof(numberChar);
			numCount++;
			n1 = 0;
		}
	}*/
}
