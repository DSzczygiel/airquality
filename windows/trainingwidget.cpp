#include "windows/trainingwidget.h"
#include "ui_trainingwidget.h"
#include "network/neuralnetwork.h"
#include "geneticalgorithm.h"

#include "windows/mainwindow.h"

/**
 * @brief TrainingWidget::TrainingWidget
 * @param errorsVec - wektor z bledami
 * @param parent
 *
 * Okno z wykresem pokazujacym bledy w procesie uczenia
 */
TrainingWidget::TrainingWidget(QVector<double> *errorsVec, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingWidget), errorsVec(errorsVec)
{
    //Inicjalizacja wykresu
    ui->setupUi(this);
    this->setWindowTitle("Proces uczenia");
    errorSeries = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView,0,0);

    //Wczytanie danych do wykresu
    for(int i=0; i<errorsVec->size(); i++){
        errorSeries->append(i+1, errorsVec->at(i));
    }

    //Kolor i opis danych
    errorSeries->setName("Błąd całkowity");
    errorSeries->setColor(Qt::red);

    //Dodanie danych do wykresu
    chart->legend()->show();
    chart->addSeries(errorSeries);
    chart->createDefaultAxes();
    chart->setTitle("Proces uczenia");
}

TrainingWidget::~TrainingWidget()
{
    delete ui;
}
