#ifndef NEURON_H
#define NEURON_H

#include <QVector>
#include "activationFunctions/activationfunction.h"

class Neuron
{
public:
    Neuron(){}
    Neuron(ActivationFunction *af, int inputs);
    ~Neuron();
    double getValue(const QVector<double> *inputVec);
    void setWeights(QVector<double> weights);

private:
    int inputs;
    QVector<double> weightVec;
    ActivationFunction *af;
    double bias;
};

#endif // NEURON_H
