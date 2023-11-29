#include "Comtrade.hpp"
#include "boost/convert.hpp"
#include <boost/convert/stream.hpp>
using boost::convert;

Comtrade::Comtrade(std::string& in_strPath, std::string& in_FileName, unsigned short in_Fnetwork, QVector<SignalComtr>& in_signal,
				   unsigned long in_n_sampl, unsigned long in_f_sampl, unsigned short in_sign_quantity, unsigned short in_nrates)
{
    f_network = in_Fnetwork;
	char c_Path_comtrade [80] = {0};
	char basename_comtrade [80] = {0};
	for (std::string::size_type i = 0; i < in_FileName.length (); i ++) // строковый тип в тип char []
		{
			basename_comtrade[i]=in_FileName[i];
		}
	for (std::string::size_type i = 0; i < in_strPath.length (); i ++) // строковый тип в тип char []
		{
			c_Path_comtrade[i]=in_strPath[i];
		}
    int i = 0;
	f_sampl = in_f_sampl;
	n_sampl = in_n_sampl;
	sign_quantity = in_sign_quantity;
	nrates = in_nrates;
	time.resize(n_sampl);
	for (auto it = in_signal[0].sig_time.begin(); it != in_signal[0].sig_time.end(); ++it)
    {
        time[i] = *it;
        i++;
    }

	CfgFilePrint(in_signal, c_Path_comtrade, basename_comtrade);
	DatFilePrint(in_signal, c_Path_comtrade, basename_comtrade);
}

///Функция формирования .cfg-файла
void Comtrade::CfgFilePrint(QVector<SignalComtr>& in_signal, char c_Path_comtrade[], char basename_comtrade[])
{
	//Создаем пустой текстовый файл с расширением .cfg
	int n_an_sig=0;//число аналоговых сигналов
	int n_dis_sig=0;//число дискретных сигналов

	for(unsigned short i = 0; i < sign_quantity; i++)
	{
		if (in_signal[i].sig_type == 'A')
		{
			n_an_sig++;
		}
		if (in_signal[i].sig_type == 'D')
		{
			n_dis_sig++;
		}
	}

	char filename[100]= {0};
	FILE *out;
	std::string str_out,
			str_sig_id, str_sig_ph, str_sig_cc, str_sig_uu, str_sig_a, str_sig_b, str_sig_skew, str_sig_min, str_sig_max;

	sprintf(filename, "%s%s.cfg", c_Path_comtrade, basename_comtrade);//s -string, d - double
	out = fopen(filename, "w");

    str_out ="Microcap 12 64 bit, 2023\n";
	fputs(str_out.c_str(), out);

    str_out = std::to_string(sign_quantity)+"," + std::to_string(n_an_sig)+"A" + "," + std::to_string(n_dis_sig)+"D" + "\n";
	fputs(str_out.c_str(), out);
    boost::cnv::cstream cnv;
	for (unsigned short i = 0; i < sign_quantity; i++)
	{
		if (in_signal[i].sig_type == 'A')
		{
			str_sig_id = in_signal[i].sig_id;
			std::string str_sig_ph(1, in_signal[i].sig_ph);
			str_sig_cc = in_signal[i].sig_cc;
			str_sig_uu = in_signal[i].sig_uu;
            str_sig_a = convert<std::string>(in_signal[i].sig_a, cnv).value();
            str_sig_b = convert<std::string>(in_signal[i].sig_b, cnv).value();
			str_sig_skew = std::to_string(in_signal[i].sig_skew);
            str_sig_min = convert<std::string>(in_signal[i].sig_min, cnv).value();
            str_sig_max = convert<std::string>(in_signal[i].sig_max, cnv).value();
			str_out = std::to_string(i+1) + "," + str_sig_id +"," + str_sig_ph +"," + str_sig_cc +"," + str_sig_uu +"," + str_sig_a +","
                    + str_sig_b +"," + str_sig_skew +"," + str_sig_min +","+ str_sig_max + "\n";
                    //+ str_sig_b +"," + str_sig_skew +"," + str_sig_min +","+ str_sig_max + ",0,0,1,1,S\n";
		}
		fputs(str_out.c_str(), out);
	}

    str_out = std::to_string(f_network) + "\n";
	fputs(str_out.c_str(), out);
    str_out = std::to_string(nrates) + "\n";
	fputs(str_out.c_str(), out);
    str_out = std::to_string(f_sampl) + "," + std::to_string(n_sampl) + "\n";
	fputs(str_out.c_str(), out);
    str_out = "29/11/2023,10:41:04.000\n30/11/2023,15:26:05.000\nASCII\n";
	fputs(str_out.c_str(), out);
	fclose(out); // close file
}


void Comtrade::DatFilePrint(QVector<SignalComtr>& in_signal, char c_Path_comtrade[], char basename_comtrade[])
{
	char filename[100]= {0};
	FILE *out;
	std::string str_out,
			str_time;

	sprintf(filename, "%s%s.dat", c_Path_comtrade, basename_comtrade);//s -string, d - double
	out = fopen(filename, "w");
    boost::cnv::cstream cnv;
	for (unsigned long i = 0; i < n_sampl; i++)
	{
        str_time = convert<std::string>(round(time[i]*100000), cnv).value();
		str_out = std::to_string(i+1) + "," + str_time + ",";
		for (unsigned short k = 0; k < sign_quantity; k++)
		{
			str_out += std::to_string(in_signal[k].sig_data[i]) + ",";
			if  (k == sign_quantity - 1)
				str_out += std::to_string(in_signal[k].sig_data[i]);
		}
		str_out +="\n";
		fputs(str_out.c_str(), out);
	}
	fclose(out); // close file
}
