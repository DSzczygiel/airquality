#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QVector<double> *output, QVector<double> *expectedOutput, QWidget *parent = nullptr);
    ~TestWidget();

private:
    Ui::TestWidget *ui;
    QVector<double> *output;
    QVector<double> *expectedOutput;
    QLineSeries *outputSeries;
    QLineSeries *expectedSeries ;
    QChart *chart;
    QChartView *chartView;
    QValueAxis* axisY;
};

#endif // TESTWIDGET_H
