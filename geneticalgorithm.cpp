#include "geneticalgorithm.h"

#include <chrono>
#include <random>
#include <QDebug>
#include <QtMath>

/**
 * @brief GeneticAlgorithm::GeneticAlgorithm
 * @param populationNumber - liczba populacji
 * @param generationsNumber - liczba generacji
 * @param mutationProbability - prawdopodobienstwo mutacji
 * @param crossoverProbability - prawdopodobienstwo krzyzowania
 * @param genomeSize - rozmiar genomu
 * @param nn - siec neuronowa dla ktorej maja byc znalezione wagi
 *
 * Klasa algorytmu genetycznego znajdujaca najlepsze wagi dla sieci neuronowej
 */
GeneticAlgorithm::GeneticAlgorithm(int populationNumber, int generationsNumber, double mutationProbability, double crossoverProbability, int genomeSize, NeuralNetwork nn):
    nn(nn), populationNumber(populationNumber), generationsNumber(generationsNumber),
    mutationProbability(mutationProbability), crossoverProbability(crossoverProbability),
    genomeSize(genomeSize)
{
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    re.seed(seed);
    initPopulation();   //Losowa inicjalizacja populacji poczatkowej
    parentsNumber = populationNumber/100;  //Liczba rodzicow
    results.fill(populationNumber, 99999);
}

/**
 * @brief GeneticAlgorithm::run
 * @return wektor wag
 *
 * Uruchomienie algorytmu
 */
QVector<double> GeneticAlgorithm::run()
{
    long minIndex=0;
    QVector<double>::iterator bestGenome;
    for(int i=0; i<generationsNumber; i++){

        selection();    //Selekcja

        bestGenome = std::min_element(results.begin(), results.end());
        minIndex = std::distance(results.begin(), bestGenome);
        double minVal = results.at(static_cast<int>(minIndex));
        qDebug() << "min element at: " << std::distance(results.begin(), bestGenome) << " value: " << minVal;//;
        totalErrorsVec.push_back(minVal);
    }

    return population[static_cast<int>(minIndex)];
}

/**
 * @brief GeneticAlgorithm::getTotalErrorsVec
 * @return wektor z bledami
 *
 * Zwraca wektor z bledami z kazdej generacji
 */
QVector<double> GeneticAlgorithm::getTotalErrorsVec()
{
    return this->totalErrorsVec;
}

/**
 * @brief GeneticAlgorithm::initPopulation
 *
 * Inicjalizuje populacje poczatkowa wagami z zakresu -0.1, 0.1
 */
void GeneticAlgorithm::initPopulation()
{
    std::uniform_real_distribution<double> unif(-0.1, 0.1);

    QVector<double> genome;

    for(int i=0; i<populationNumber; i++){
        for(int j=0; j<genomeSize; j++){
            genome.push_back(unif(re));
        }
        population.push_back(genome);
        genome.clear();
    }
    printData(population, "Init population");
}

/**
 * @brief GeneticAlgorithm::selection
 *
 * Dokonuje selekcji najlepszych osobnikow
 * i uzupelnia populacje do okreslonego rozmiaru
 */
void GeneticAlgorithm::selection()
{
    if(!results.empty())
        results.clear();

    //Obliczanie bledu dla kazdego osobnika(wektora wag) z populacji
    for(int i=0; i<populationNumber; i++){
        double val = population.at(i).at(0);
        QVector<double> weights = population.at(i);
        nn.setAllWeights(&weights);
        results.push_back((nn.getTotalError()));
    }

    QVector<QVector<double>> newPopulation = getFittestIndividuals(); //Wybor 50% osobnikow z obecnej populacji
    crossOver(newPopulation);   //Krzyzowanie
    mutation(newPopulation);    //Mutacja
    fillPopulation(newPopulation); //Uzupelnienie populacji

    this->population = newPopulation;
}

/**
 * @brief GeneticAlgorithm::crossOver
 * @param parents - populacja najlepszych osobnikow
 * @return
 *
 * Krzyzowanie czesci najlepszych osobnikow
 *
 */
QVector<QVector<double>> GeneticAlgorithm::crossOver(QVector<QVector<double>> &parents)
{
    //Obliczanie prawdopodobienstwa zajscia krzyzowania dla kazdego osobnika
    std::uniform_real_distribution<double> unif(0, 1);
    QVector<double> probabilities;
    QVector<QVector<double>> newPopulation;
    for(int i=0; i<parents.size()/2; i++)
        probabilities.push_back(unif(re));

    for(int i=0; i<probabilities.size(); i++){
        //Brak krzyzowania, przeniesienie pary rodzicow do nowej populacji
        if(probabilities.at(i) > crossoverProbability){
            newPopulation.push_back(parents.at(i*2));
            newPopulation.push_back(parents.at(i*2+1));
            //Losowanie miejsca podzialu rodzicow i zamiana podzielonej czesci
        }else{
            std::uniform_int_distribution<int> unif(1, parents.at(0).size()-1);
            int splitPosition = unif(re);
            QVector<double> p1 = parents.at(i*2);
            QVector<double> p2 = parents.at(i*2+1);
            for(int i=splitPosition; i<p1.size(); i++){
                std::swap(p1[i], p2[i]);
            }
            p1.swap(parents[i*2]);
            p2.swap(parents[i*2+1]);
        }
    }
    return newPopulation;
}

/**
 * @brief GeneticAlgorithm::getFittestIndividuals
 * @return wektor z najlepszymi osobnikami
 *
 * Wybor najlepszych osobnikow za pomoca metody turniejowej
 */
QVector<QVector<double>> GeneticAlgorithm::getFittestIndividuals()
{
    std::uniform_real_distribution<double> unif(0, population.size()-1);
    QVector<QVector<double>> fittestIndividuals;
    QVector<double> probabilities;

    //Wybor polowy populacji
    for(int i=0; i<populationNumber/2; i++){
        std::vector<int> choosenIndexes;
        //Losowanie liczbaPopulacji/5 osobnikow do udzialu w turnieju
        for(int k=0; k<populationNumber/5; k++){
            choosenIndexes.push_back(static_cast<int>(unif(re)));
        }

        int bestIndex = 0;
        double min = 999999;
        //Wybor najlepszego sposrod wczesniej wylosowanych osobnikow
        for(int i : choosenIndexes){
            if(results.at(i) < min){
                min = results.at(i);
                bestIndex = i;
            }
        }
        fittestIndividuals.push_back(population[bestIndex]);
    }
    return  fittestIndividuals;
}

/**
 * @brief GeneticAlgorithm::mutation
 * @param children - populacja po krzyzowaniu
 */
void GeneticAlgorithm::mutation(QVector<QVector<double> > &children)
{
    std::uniform_real_distribution<double> unif(0, 1);
    QVector<double> probabilities;

    for(int i=0; i<children.size(); i++){
        double probability = unif(re);
        //Losowy wybor genu i zamiana z nastepnym
        if(probability <= mutationProbability){
            std::uniform_int_distribution<int> unif2(0, children.at(i).size()-2);
            int geneToSwap = unif2(re);
            std::swap(children[i][geneToSwap], children[i][geneToSwap+1]);
        }
        probabilities.push_back(unif(re));
    }
}

/**
 * @brief GeneticAlgorithm::printData
 * @param data - dane
 * @param description - opis
 *
 * Funkcja do wypisywania danych w celach testowych
 */
void GeneticAlgorithm::printData(QVector<QVector<double>> data, QString description)
{
    qDebug() << description;
    QString ts;
    for(auto vec : data){
        for(auto value : vec){
            ts.append(QString::number(value)).append(" ");
        }
        qDebug() << ts;
        ts.clear();
    }
}

/**
 * @brief GeneticAlgorithm::fillPopulation
 * @param newPopulation - referencja do nowej populacji
 */
void GeneticAlgorithm::fillPopulation(QVector<QVector<double>> &newPopulation)
{
    //Jesli populacja mniejsza niz zakladany rozmiar to uzupelnia losowymi wartosciami z przedzialu -1,1
    if(newPopulation.size() < populationNumber){
        for(int i=newPopulation.size(); i<populationNumber; i++){
            std::uniform_real_distribution<double> unif(-1, 1);
            QVector<double> genome;
            for(int j=0; j<genomeSize; j++){
                genome.push_back(unif(re));
            }
            newPopulation.push_back(genome);
        }
    }
}
