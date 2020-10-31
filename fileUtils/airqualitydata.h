#ifndef AIRQUALITYDATA_H
#define AIRQUALITYDATA_H
#include <QVector>

class AirQualityData
{
public:
    AirQualityData();
    AirQualityData(QVector<QStringList> stringData);
    QVector<QVector<double>> data;
};

#endif // AIRQUALITYDATA_H
