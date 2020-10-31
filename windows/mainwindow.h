#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadTrainingFilePushButton_clicked();

    void on_loadTestFilePushButton_clicked();

    void on_startTrainingPushButton_clicked();

    void on_loadWeightsPushButton_clicked();

    void on_runNetworkPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString trainingFilename;
    QString testFilename;
    QString weightsFilename;
    QVector<QVector<double>> trainingData;
    QVector<QVector<double>> testData;
    QVector<double> weights;
};
#endif // MAINWINDOW_H
