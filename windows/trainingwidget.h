#ifndef TRAININGWIDGET_H
#define TRAININGWIDGET_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include "geneticalgorithm.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class TrainingWidget;
}

class TrainingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingWidget(QVector<double> *errorsVec, QWidget *parent = nullptr);
    ~TrainingWidget();

private:
    Ui::TrainingWidget *ui;
    QVector<double> *errorsVec;
    QLineSeries *errorSeries;
    QChart *chart;
    QChartView *chartView;
    QValueAxis* axisY;
};

#endif // TRAININGWIDGET_H
