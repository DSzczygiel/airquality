#include "fileUtils/csvparser.h"
#include <QMessageBox>
#include <QTextStream>

CsvParser::CsvParser()
{
}

/**
 * @brief CsvParser::parse
 * @param fileName - nazwa pliku csv
 * @param separator - separator kolumn w pliku csv
 * @return - dane w postaci wektora listy stringów
 *
 * Przetwarza plik CSV i zapisuje każdą linie pliku
 * do QStringList, a QStringList dodaje do wektora
 */
QVector<QStringList> CsvParser::parse(QString fileName, char separator)
{
    QFile file;
    QVector<QStringList> vec;

    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(nullptr, "error", file.errorString());
        return vec;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(separator);
        vec.push_back(fields);
    }
    return vec;
}
