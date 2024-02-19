#include "Comtrade.hpp"
#include "boost/convert.hpp"
#include "boost/convert/stream.hpp"
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
            str_sig_An, str_sig_ch_id, str_sig_ph, str_sig_ccbm, str_sig_uu, str_sig_a, str_sig_b, str_sig_skew, str_sig_min, str_sig_max, str_sig_primary, str_sig_secondary, str_sig_PS;

	sprintf(filename, "%s%s.cfg", c_Path_comtrade, basename_comtrade);//s -string, d - double
	out = fopen(filename, "w");

    str_out ="Microcap 12 64 bit,GenMicrocap,2013\n";
	fputs(str_out.c_str(), out);

    str_out = std::to_string(sign_quantity)+"," + std::to_string(n_an_sig)+"A" + "," + std::to_string(n_dis_sig)+"D" + "\n";
	fputs(str_out.c_str(), out);
    boost::cnv::cstream cnv;
    str_sig_primary = "1";
    str_sig_secondary = "1";
    str_sig_PS = "S";
	for (unsigned short i = 0; i < sign_quantity; i++)
	{
		if (in_signal[i].sig_type == 'A')
		{
            str_sig_An = std::to_string(i+1);
            str_sig_ch_id = in_signal[i].sig_ch_id;
        std::string str_sig_ph(1, in_signal[i].sig_ph);
        str_sig_ccbm = in_signal[i].sig_ccbm;
        str_sig_uu = in_signal[i].sig_uu;
            str_sig_a = convert<std::string>(in_signal[i].sig_a, cnv).value();
            str_sig_b = convert<std::string>(in_signal[i].sig_b, cnv).value();
        str_sig_skew = std::to_string(in_signal[i].sig_skew);
            str_sig_min = convert<std::string>(in_signal[i].sig_min, cnv).value();
            str_sig_max = convert<std::string>(in_signal[i].sig_max, cnv).value();
            str_sig_primary = std::to_string(in_signal[i].sig_primary);
            str_sig_secondary = std::to_string(in_signal[i].sig_secondary);
        str_out = str_sig_An +
                      "," + str_sig_ch_id +
                      "," + str_sig_ph +
                      "," + str_sig_ccbm +
                      "," + str_sig_uu +
                      "," + str_sig_a +
                      "," + str_sig_b +
                      "," + str_sig_skew +
                      "," + str_sig_min +
                      ","+ str_sig_max +
                      "," + str_sig_primary +
                      ","+ str_sig_secondary +
                      "," + str_sig_PS +
                      "\n";
		}
		fputs(str_out.c_str(), out);
	}

    str_out = std::to_string(f_network) + "\n";
	fputs(str_out.c_str(), out);
    str_out = std::to_string(nrates) + "\n";
	fputs(str_out.c_str(), out);
    str_out = std::to_string(f_sampl) + "," + std::to_string(n_sampl) + "\n";
	fputs(str_out.c_str(), out);
    str_out = "29/11/2023,10:41:04.000\n30/11/2023,15:26:05.000\nASCII\n1\n+5h,+5h\n6,0\n";
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
            str_out += std::to_string(in_signal[k].sig_data[i]*1000) + ",";
			if  (k == sign_quantity - 1)
                str_out += std::to_string(in_signal[k].sig_data[i]*1000);//Искусственно масштабируется значение, чтобы потом уменьшить его через коэффициент а = 0.001
		}
		str_out +="\n";
		fputs(str_out.c_str(), out);
	}
	fclose(out); // close file
}

ComtradeDataReader::ComtradeDataReader(const std::string& comtradePath, const char delimiter)
{
    std::string lineData;

    //! Проверяем наличие обязательных (critical) CFG- и DAT-файлов
    std::string cfgFileName = comtradePath + ".CFG";
    std::string datFileName = comtradePath + ".DAT";

    std::ifstream cfgFile(cfgFileName);
    std::ifstream datFile(datFileName);

    if (!cfgFile.is_open() || !datFile.is_open()) {
        std::cerr << "Error: CFG or DAT file not found in the specified directory." << std::endl;
        return;
    }

    //! Чтение CFG-файла
    for (size_t i = 0; std::getline(cfgFile, lineData); i++) {
        std::istringstream iss(lineData);
        //* Группа параметров a
        if (i == 0u) {
            std::string stationName, recDevId;
            if (std::getline(iss, stationName, delimiter) &&
                std::getline(iss, recDevId, delimiter)) {
                this->stationName = stationName;
                this->recDevId = recDevId;
            } else {
                std::cerr << "Error: Critical data is missing." << std::endl;
                return;
            }
            if (iss >> revYear)
                this->revYear = revYear;
            else
                this->revYear = 1991;
        }
        //* Группа параметров b
        else if (i == 1u) {
            std::string numChannels, numAnalogChannels, numDigitalChannels;
            if (std::getline(iss, numChannels, delimiter) &&
                std::getline(iss, numAnalogChannels, delimiter) &&
                std::getline(iss, numDigitalChannels, delimiter)) {
                this->numChannels = std::stoi(numChannels);
                this->numAnalogChannels = std::stoi(numAnalogChannels);
                this->numDigitalChannels = std::stoi(numDigitalChannels);
            } else {
                std::cerr << "Error: Critical data is missing." << std::endl;
                return;
            }
        }
        //* Группа параметров d
        else if (i == 2u + this->numChannels) {
            std::string freqNetwork;
            if (std::getline(iss, freqNetwork, delimiter)) {
                this->freqNetwork = std::atof(freqNetwork.c_str());
            } else {
                std::cerr << "Error: Critical data is missing." << std::endl;
                return;
            }
        }
        //* Группа параметров e
        else if (i == 3u + this->numChannels) {
            std::string nRates;
            if (std::getline(iss, nRates, delimiter)) {
                this->nRates =  std::stoi(nRates);
            } else {
                std::cerr << "Error: Critical data is missing." << std::endl;
                return;
            }
        }
        //TODO Возможно, неправильно отработает с числом частот дискретизации, отличным от 1 (не было примера)
        else if (3u + this->numChannels < i && i <= 3u + this->numChannels + this->nRates) {
            _sampRateInfo info;
            std::string samp, endSamp;
            info.n = i - (3 + this->numChannels);
            if (std::getline(iss, samp, delimiter) &&
                std::getline(iss, endSamp, delimiter)) {
                info.samp = std::atof(samp.c_str());
                info.endSamp = std::stoi(samp);
                this->sampRateInfo.push_back(info);
            } else {
                std::cerr << "Error: Critical data is missing." << std::endl;
                return;
            }
        }
        // Прочие строки не обрабатываются
        else continue;
    }

    cfgFile.close();

    //! Чтение DAT-файла
    uint8_t idx0 = 2u;
    std::string str;
    //* Аналоговые каналы
    for (size_t i = 0; i < this->numAnalogChannels; i++) { // По каналам
        std::vector<double> values;

        while (std::getline(datFile, lineData)) { // По строкам
            std::istringstream iss(lineData);
            double value;

            for (size_t j = 0; j < idx0 + i; j++) { // Доходим до нужного канала
                if (!(std::getline(iss, str, delimiter))) {
                    std::cerr << "Error reading analog data." << std::endl;
                    return;
                }
            }

            value = std::atof(str.c_str());
            values.push_back(value);
        }

        this->analogData.push_back(values);
    }

    //* Дискретные каналы
    for (size_t i = 0; i < this->numDigitalChannels; i++) { // По каналам
        std::vector<bool> values;

        while (std::getline(datFile, lineData)) { // По строкам
            std::istringstream iss(lineData);
            bool value;

            for (size_t j = 0; j < idx0 + i; j++) { // Доходим до нужного канала
                if (!(std::getline(iss, str, delimiter))) {
                    std::cerr << "Error reading analog data." << std::endl;
                    return;
                }
            }

            value = (bool)std::stoi(str);
            values.push_back(value);
        }

        this->digitalData.push_back(values);
    }

    datFile.close();
}
