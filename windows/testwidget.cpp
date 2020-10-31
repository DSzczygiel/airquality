#include "windows/testwidget.h"
#include "ui_testwidget.h"
#include "network/neuralnetwork.h"
#include "geneticalgorithm.h"

/**
 * @brief TestWidget::TestWidget
 * @param output - wektor z wyjsciami sieci
 * @param expectedOutput - wektor z oczekiwanymi wartosciami wyjscia
 * @param parent
 *
 * Okno pokazujace roznice pomiedzy wyjsciem sieci a wartoscia oczekiwana
 */
TestWidget::TestWidget(QVector<double> *output, QVector<double> *expectedOutput, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget), output(output), expectedOutput(expectedOutput)
{
    ui->setupUi(this);

    //Inicjalizacja wykresu
    this->setWindowTitle("Test sieci");
    outputSeries = new QLineSeries();
    expectedSeries = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView,0,0);

    //Dodawanie wartosci do wykresu
    for(int i=0; i<output->size()-1; i++){
        outputSeries->append(i+1, output->at(i));//--at(1
        expectedSeries->append(i+1, (expectedOutput->at(i)));
    }

    //Ustawianie kolorow i nazw dla danych
    outputSeries->setName("Wyjście sieci");
    outputSeries->setColor(Qt::red);
    expectedSeries->setName("Wartość oczekiwana");
    expectedSeries->setColor(Qt::green);

    //Dodawanie danych do wykresu
    chart->legend()->show();
    chart->addSeries(outputSeries);
    chart->addSeries(expectedSeries);
    chart->createDefaultAxes();
    chart->setTitle("Wykres ");
}

TestWidget::~TestWidget()
{
    delete ui;
}
