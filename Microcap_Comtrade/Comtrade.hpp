#ifndef COMTRADE_HPP
#define COMTRADE_HPP

//* Includes begin --------------------------------------------------------------------------------------
#include <stdint.h> // Целочисленные типы фиксированной ширины
#include <fstream>  // Файловый ввод/вывод
#include <iostream> // Поточный ввод/вывод
#include <sstream>  // std::istringstream
#include <string>   // Операции со строками (std::string)
#include <vector>
#include <QObject>
#include "SignalComtr.hpp"
//* Includes end ----------------------------------------------------------------------------------------

//1.Формат записываемого файла в ПК Simulink для записи в формат COMTRADE:
//1.1.Запись данных в модели ПК Simulink должна делаться с использованием
//    блоков "BusCreator" и "To Workspace"
//1.2.Первым записывается время с заданной дискретизацией выборки
//  "Sample Time"
//1.3.Запись остальных сигналов делается в произвольном порядке
//1.4.Дискретные переменные и сигналы должны быть переведены в формат
//    "double"
//1.5.Все сигналы, собираемые блоком "Bus Creator" должны иметь название,
//    формат которого описан ниже

//2.Формат наименованя измеряемых величин для их записи в формат COMTRADE:
//2.1.Названия дискретных сигналов начинаются с нижнего подчеркивания "_"

//2.2.Названия напряжений начинаются с U, далее следует наименование фазы с
//  маленькой буквы, далее - любые символы: "Ua" - напряжение фазы А.

//2.3.Названия токов начинаются с I, далее следует наименование фазы с
//  маленькой буквы, далее - любые символы: "Ia" - ток фазы А.

class Comtrade
{
private:
	unsigned short f_network;   //базовая частота сети
    QVector<float> time;
	unsigned long f_sampl;
	unsigned long n_sampl;
	unsigned short sign_quantity;
	unsigned short nrates;
public:
	Comtrade(std::string& in_strPath, std::string& in_FileName, unsigned short in_Fnetwork, QVector<SignalComtr>& in_signal,
			 unsigned long in_n_sampl, unsigned long in_f_sampl, unsigned short in_sign_quantity, unsigned short in_nrates);
	void CfgFilePrint(QVector<SignalComtr>& in_signal, char c_Path_comtrade[], char basename_comtrade[]);
	void DatFilePrint(QVector<SignalComtr>& in_signal, char c_Path_comtrade[], char basename_comtrade[]);
};


/**
 * @brief Информация о частоте дискретизации
 *
 */
struct _sampRateInfo {
    uint8_t n;                  ///< Номер частоты дискретизации в файле данных
    double samp;                ///< Заданная частота дискретизации, Гц
    uint32_t endSamp;           ///< Номер последней выборки с заданной частотой дискретизации
};

/**
 * @brief Класс для хранения информации о результате чтения COMTRADE-файлов
 *
 */
class ComtradeDataReader {
public:
    //! Конфигурационные параметры (CFG)
    //* Группа параметров a
    std::string stationName;        ///< Имя станции
    std::string recDevId;           ///< Идентификационный номер или название записывающего устройства
    uint16_t revYear;               ///< Год ревизии стандарта COMTRADE

    //* Группа параметров b
    uint16_t numChannels;           ///< Общее число каналов
    uint16_t numAnalogChannels;     ///< Число аналоговых каналов
    uint16_t numDigitalChannels;    ///< Число дискртеных каналов

    //* Группа параметров d
    double freqNetwork;             ///< Частота сети, Гц

    //* Группа параметров e
    uint8_t nRates;                 ///< Количество частот дискретизации в файле данных
    //TODO Каналы частот дискретизации требуют доработки (скорее всего не работает с более чем 1 каналом)
    std::vector<_sampRateInfo> sampRateInfo;        ///< Контейннер длля хранения информации по каналам с разными частотами дискретизации

    //! Данные (DAT)
    std::vector<std::vector<double>> analogData;    ///< Контейнеры для хранения данных по аналоговым каналам
    std::vector<std::vector<bool>> digitalData;     ///< Контейнеры для хранения данных по дискретным каналам

    /**
     * @brief Construct a new Comtrade Data Reader object
     *
     * @param comtradePath Путь к расположению COMTRADE-файлов
     * @param delimiter Разделитель данных (по умолчанию принят ',')
     */
    ComtradeDataReader(const std::string& comtradePath, const char delimiter = ',');
};

#endif // COMTRADE_HPP
