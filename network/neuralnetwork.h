#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QVector>
#include "network/neuron.h"

class NeuralNetwork
{
public:
    NeuralNetwork(int input, int hidden, int output);
    void init();
    void setAllWeights(QVector<double> *allWeights);
    void setInput(QVector<QVector<double>> *inputSet);
    void setOutputIndexes(QVector<int> outputIndexes);
    QVector<double> getOutput(QVector<double> *input);
    double getTotalError();
    int getNrOfWeights();

private:
    int inputNeurons;
    int hiddenNeurons;
    int outputNeurons;
    int nrOfWeights;
    QVector<Neuron> outputLayer;
    QVector<double> outputLayerOutput;
    QVector<Neuron> hiddenLayer;
    QVector<double> hiddenLayerOutput;
    QVector<int> outputIndexes;
    QVector<QVector<double>> *input;
    QVector<double> *allWeights;
    QVector<Neuron> inputLayer;    int nrOfNeurons;

};

#endif // NEURALNETWORK_H
