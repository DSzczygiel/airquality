#include "fileUtils/airqualitydata.h"
#include <QDebug>
AirQualityData::AirQualityData()
{

}

/**
 * @brief AirQualityData::AirQualityData
 * @param stringData - dane odczytane z pliku csv
 *
 * Przetwarza dane zapisane jako string
 * i zapisuje do wektora typu double
 */
AirQualityData::AirQualityData(QVector<QStringList> stringData)
{
    QLocale l(QLocale::Polish);
    QVector<double> row;
    for(int i=0; i<stringData.size(); i++){
        for(int j=2; j<stringData.at(i).size(); j++){
            row.push_back(l.toDouble(stringData.at(i).at(j)));
        }
        data.push_back(row);
        row.clear();
    }
}
