#include "fileUtils/weightserializer.h"
#include <QFile>
#include<QTextStream>

WeightSerializer::WeightSerializer()
{

}
/**
 * @brief WeightSerializer::serialize
 * @param filename - nazwa pliku do jakiego zapisze wagi
 * @param weights - wektor z wagami
 *
 * Zapisuje wagi z wektora double do pliku
 */
void WeightSerializer::serialize(QString filename, QVector<double> weights)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    for(double w : weights){
            out << w << '\n';
    }

    file.close();
}


/**
 * @brief WeightSerializer::deserialize
 * @param filename - nazwa pliku z wagami
 * @return - wektor wag
 *
 * Odczytuje wektor wag z pliku
 */
QVector<double> WeightSerializer::deserialize(QString filename)
{
    QVector<double> weights;

    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
       while (!in.atEnd()) {
           QString line = in.readLine();
          weights.push_back(line.toDouble());
       }

       return weights;
}
