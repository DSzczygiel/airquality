#ifndef WEIGHTSERIALIZER_H
#define WEIGHTSERIALIZER_H

#include <QString>
#include <QVector>

class WeightSerializer
{
public:
    WeightSerializer();
    static void serialize(QString filename, QVector<double> weights);
    static QVector<double> deserialize(QString filename);
};

#endif // WEIGHTSERIALIZER_H
