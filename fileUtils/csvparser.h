#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QStringList>

class CsvParser
{
public:
    CsvParser();
    static QVector<QStringList> parse(QString fileName, char separator);
};

#endif // CSVPARSER_H
