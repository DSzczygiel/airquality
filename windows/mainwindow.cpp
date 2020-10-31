#include "windows/mainwindow.h"
#include "ui_mainwindow.h"
#include "fileUtils/csvparser.h"
#include "fileUtils/airqualitydata.h"
#include "windows/trainingwidget.h"
#include "windows/testwidget.h"
#include "fileUtils/weightserializer.h"
#include <QDebug>
#include <QFileDialog>
#include <QIntValidator>
#include <QDoubleValidator>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 *
 * Główne okno programu
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("AirQuality");
    //Walidacja ustawien algorytmu
    ui->populationLineEdit->setValidator(new QIntValidator(0, 10000, this));
    ui->generationsLineEdit->setValidator(new QIntValidator(0, 100, this));
    ui->crossoverLineEdit->setValidator(new QDoubleValidator(0, 1, 2, this));
    ui->mutationLineEdit->setValidator(new QDoubleValidator(0, 1, 2, this));
    ui->verticalLayout_2->setAlignment(Qt::AlignHCenter);

    //Domyslnie ustawione pliki
    trainingFilename = "/home/daniel/OneDrive/Studia201920/AnalizaWizualizcja/Projekt2/train.csv";//--ff.csv
    testFilename = "/home/daniel/OneDrive/Studia201920/AnalizaWizualizcja/Projekt2/test.csv";
    weightsFilename = "/home/daniel/Dokumenty/wagi.txt";
    ui->trainingFilenameLabel->setText(trainingFilename);
    ui->testFilenameLabel->setText(testFilename);
    ui->weightsFilenameLabel->setText(weightsFilename);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_loadTrainingFilePushButton_clicked
 *
 * Otwiera okno do wyboru pliku z danymi uczacymi
 */
void MainWindow::on_loadTrainingFilePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Wybierz plik", QDir::homePath());
    ui->trainingFilenameLabel->setText(fileName);
    trainingFilename = fileName;
}

/**
 * @brief MainWindow::on_loadTestFilePushButton_clicked
 *
 * Otwiera okno do wyboru pliku z danymi testowymi
 */
void MainWindow::on_loadTestFilePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Wybierz plik", QDir::homePath());
    ui->testFilenameLabel->setText(fileName);
    testFilename = fileName;
}


/**
 * @brief MainWindow::on_startTrainingPushButton_clicked
 *
 * Rozpoczyna uczenie sieci i otwiera okno z wykresem po zakonczeniu
 */
void MainWindow::on_startTrainingPushButton_clicked()
{
    //Pobieranie ustawien algorytmu z formularza
    QLocale l(QLocale::Polish);
    int population = ui->populationLineEdit->text().toInt();
    int generations = ui->generationsLineEdit->text().toInt();
    double crossoverProb = l.toDouble(ui->crossoverLineEdit->text());
    double mutationProb = l.toDouble(ui->crossoverLineEdit->text());

    qDebug() << crossoverProb;

    //Wczytanie danych uczacych
    QVector<QStringList> trainStringList = CsvParser::parse(trainingFilename, ';');//Przetworzenie pliku csv do stringow
    AirQualityData airQualityTrainingData(trainStringList); //Przetworzenie danych ze stringow na double
    QVector<QVector<double>> trainingData = airQualityTrainingData.data; //Pobranie przetworzonych danych

    NeuralNetwork nn(13, 6, 1); //Tworzenie sieci, 13 neuronow wejsciowych, 6 ukrytych, 1 wyjsciowy
    nn.setInput(&trainingData); //Ustawienie danych uczacych na wejscie
    nn.setOutputIndexes(QVector<int>({1})); //Wybor atrybutu o indeksie 1 jako wyjscie

    GeneticAlgorithm ga(population, generations, mutationProb, crossoverProb, nn.getNrOfWeights(), nn); //Tworzenie algorytmu z wybranymi parametrami
    QVector<double> bestWeights = ga.run();//Uruchomienie algorytmu i otrzymanie najlepszych wag
    QVector<double> errors = ga.getTotalErrorsVec();//Pobranie wektora z bledami z kazdej generacji

    WeightSerializer::serialize("/home/daniel/Dokumenty/wagi.txt", bestWeights);//Zapis najlepszych wag do pliku

    //Wyswietlenie wykresu
    TrainingWidget *tw = new TrainingWidget(&errors);
    tw->show();
}

/**
 * @brief MainWindow::on_loadWeightsPushButton_clicked
 *
 * Otwiera okno do wyboru pliku z wagami
 */
void MainWindow::on_loadWeightsPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Wybierz plik", QDir::homePath());
    ui->testFilenameLabel->setText(fileName);
    weightsFilename = fileName;
}

/**
 * @brief MainWindow::on_runNetworkPushButton_clicked
 *
 * Uruchamia siec z wybranymi wagami i wyswietla wykres
 * z wyjsciem sieci oraz rzeczywista wartoscia
 */
void MainWindow::on_runNetworkPushButton_clicked()
{
    //Wczytanie danych testowych
    QVector<QStringList> testStringList = CsvParser::parse(testFilename, ';'); //Przetworzenie pliku csv do stringow
    AirQualityData airQualityTestData(testStringList); //Przetworzenie danych ze stringow na double
    QVector<QVector<double>> testData = airQualityTestData.data; //Pobranie przetworzonych danych

    weights = WeightSerializer::deserialize(weightsFilename); //Wczytanie wag z pliku

    NeuralNetwork nn(13, 6, 1); //Tworzenie sieci, 13 neuronow wejsciowych, 6 ukrytych, 1 wyjsciowy
    nn.setInput(&testData); //Ustawienie danych testowych na wejscie sieci
    nn.setOutputIndexes(QVector<int>({1})); //Wybor atrybutu o indeksie 1 jako wyjscie
    nn.setAllWeights(&weights); //Ustawienie wag wczytanych z pliku

    QVector<double> outputValues;
    QVector<double> expectedValues;
    for(int i=0; i<testData.size()-1; i++){
        QVector<double> output = nn.getOutput(&testData[i]); //Wyjscie sieci dla jednego rekordu
        outputValues.push_back(output.at(0));//--at1    //Zapis wartosci wyjscia sieci do wektora
        expectedValues.push_back(testData[i+1].at(1));  //Zapis oczekiwanej wartosci do wektora
    }

    //Wyswietlenie okna z wykresem
    TestWidget *tw = new TestWidget(&outputValues, &expectedValues);
    tw->show();
}
