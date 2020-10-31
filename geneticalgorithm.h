#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QVector>
#include <random>
#include "network/neuralnetwork.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(int populationNumber, int generationsNumber, double mutationProbability, double crossoverProbability, int genomeSize, NeuralNetwork nn);
    QVector<double> run();
    QVector<double> getTotalErrorsVec();

private:
    unsigned seed;
    NeuralNetwork nn;
    std::default_random_engine re;
    int populationNumber;
    int generationsNumber;
    double mutationProbability;
    double crossoverProbability;
    int parentsNumber;
    int genomeSize;
    QVector<QVector<double>> population;
    QVector<double> results;
    void initPopulation();
    void selection();
    QVector<QVector<double>> crossOver(QVector<QVector<double> > &parents);
    QVector<QVector<double>> getFittestIndividuals();
    void mutation(QVector<QVector<double>> &children);
    void printData(QVector<QVector<double>> data, QString description);
    void fillPopulation(QVector<QVector<double> > &newPopulation);
    QVector<double> totalErrorsVec;

};

#endif // GENETICALGORITHM_H
