#ifndef ComtradeDataWriter_HPP
#define ComtradeDataWriter_HPP

//* Includes begin --------------------------------------------------------------------------------------
#include <stdint.h> // Целочисленные типы фиксированной ширины
#include <fstream>  // Файловый ввод/вывод
#include <iostream> // Поточный ввод/вывод
#include <sstream>  // std::istringstream
#include <string>   // Операции со строками (std::string)
#include <QObject>
#include "SignalComtr.hpp"
//* Includes end ----------------------------------------------------------------------------------------

//* User macros begin -----------------------------------------------------------------------------------
/**
 * @brief Формирование get-свойства для приватного поля
 * @author Di0nisP
 *
 */
#define GENERATE_GETTER(name) \
    decltype(name) get_##name() const { \
        return name; \
    }
//* User macros end -------------------------------------------------------------------------------------

/**
 * @brief Информация о частоте дискретизации
 * @author Di0nisP
 *
 */
struct _sampRateInfo {
    uint8_t n;                  ///< Номер частоты дискретизации в файле данных
    double samp;                ///< Заданная частота дискретизации, Гц
    uint32_t endSamp;           ///< Номер последней выборки с заданной частотой дискретизации
};

/**
 * @brief Класс для записи COMTRADE-файлов.
 * 
 * 1.Формат записываемого файла в ПК Simulink для записи в формат `COMTRADE`:
 * 1.1.Запись данных в модели ПК Simulink должна делаться с использованием блоков "BusCreator" и "To Workspace";
 * 1.2.Первым записывается время с заданной дискретизацией выборки "Sample Time";
 * 1.3.Запись остальных сигналов делается в произвольном порядке;
 * 1.4.Дискретные переменные и сигналы должны быть переведены в формат `double`;
 * 1.5.Все сигналы, собираемые блоком "Bus Creator" должны иметь название, формат которого описан в п. 2.
 * 
 * 2.Формат наименованя измеряемых величин для их записи в формат `COMTRADE`:
 * 2.1.Названия дискретных сигналов начинаются с нижнего подчеркивания "_";
 * 2.2.Названия напряжений начинаются с U, далее следует наименование фазы с маленькой буквы, далее - любые символы (например, "Ua" - напряжение фазы А);
 * 2.3.Названия токов начинаются с I, далее следует наименование фазы с маленькой буквы, далее - любые символы (например, "Ia" - ток фазы А).
 * 
 */
class ComtradeDataWriter {
private:
    unsigned short freqNetwork;     ///< Частота сети, Гц
    QVector<float> time;            
    unsigned long f_sampl;          ///< Частота дискретизации, Гц
    unsigned long n_sampl;          ///<
    unsigned short sign_quantity;   ///<
    unsigned short nRates;          ///< Количество частот дискретизации в файле данных
public:
    /**
     * @brief Construct a new Comtrade Data Writer object
     * 
     * @param in_strPath Путь к файлу.
     * @param in_fileName Имя файла
     * @param in_freqNetwork Частота сети, Гц
     * @param in_signal Вектор сигналов COMTRADE
     * @param in_n_sampl
     * @param in_f_sampl Частота дискретизации, Гц
     * @param in_sign_quantity 
     * @param in_nRates Количество частот дискретизации в файле данных
     */
    ComtradeDataWriter(std::string& in_strPath, std::string& in_fileName, unsigned short in_freqNetwork, QVector<SignalComtr>& in_signal,
                       unsigned long in_n_sampl, unsigned long in_f_sampl, unsigned short in_sign_quantity, unsigned short in_nRates);

    /**
     * @brief 
     * 
     * @param in_signal 
     * @param c_Path_ComtradeDataWriter 
     * @param basename_ComtradeDataWriter 
     */
	void cfgFilePrint(QVector<SignalComtr>& in_signal, char c_Path_ComtradeDataWriter[], char basename_ComtradeDataWriter[]);

    /**
     * @brief 
     * 
     * @param in_signal 
     * @param c_Path_ComtradeDataWriter 
     * @param basename_ComtradeDataWriter 
     */
	void datFilePrint(QVector<SignalComtr>& in_signal, char c_Path_ComtradeDataWriter[], char basename_ComtradeDataWriter[]);
};

/**
 * @brief Класс для чтения COMTRADE-файлов.
 * @author Di0nisP
 *
 */
class ComtradeDataReader {
private:
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
    //TODO Каналы частот дискретизации требуют доработки (не работает с более чем 1 каналом)
    QVector<_sampRateInfo> sampRateInfo;    ///< Контейннер длля хранения информации по каналам с разными частотами дискретизации

    //! Данные (DAT)
    QVector<QVector<double>> analogData;    ///< Контейнеры для хранения данных по аналоговым каналам
    QVector<QVector<bool>> digitalData;     ///< Контейнеры для хранения данных по дискретным каналам

public:
    /**
     * @brief Construct a new Comtrade Data Reader object
     *
     * @param comtradePath Путь к расположению COMTRADE-файлов
     * @param delimiter Разделитель данных (по умолчанию принят ',')
     */
    ComtradeDataReader(const std::string& comtradePath, const char delimiter = ',');

    //! Конфигурационные параметры (CFG)
    //* Группа параметров a
    GENERATE_GETTER(stationName)
    GENERATE_GETTER(recDevId)
    GENERATE_GETTER(revYear)

    //* Группа параметров b
    GENERATE_GETTER(numChannels)
    GENERATE_GETTER(numAnalogChannels)
    GENERATE_GETTER(numDigitalChannels)

    //* Группа параметров d
    GENERATE_GETTER(freqNetwork)

    //* Группа параметров e
    GENERATE_GETTER(nRates)
    GENERATE_GETTER(sampRateInfo)

    //! Данные (DAT)
    GENERATE_GETTER(analogData)
    GENERATE_GETTER(digitalData)
};

#endif // ComtradeDataWriter_HPP
