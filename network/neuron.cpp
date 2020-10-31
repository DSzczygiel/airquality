#include "network/neuron.h"
#include <random>
#include <chrono>
#include <QDebug>

/**
 * @brief Neuron::Neuron
 * @param af - funkcja aktywacji dla neuronu
 * @param inputs - liczba wejść neuronu
 *
 * Konstruktor inicjuje wagi losowymi wartościami z zakresu -1,1
 */
Neuron::Neuron(ActivationFunction *af, int inputs):
    inputs(inputs), af(af)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> unif(-1, 1);
    std::default_random_engine re(seed);
    for(int i=0; i<inputs; i++){
        weightVec.push_back(unif(re));
    }
}

Neuron::~Neuron()
{
}

/**
 * @brief Neuron::getValue
 * @param inputVec - wektor z danymi wejściowymi
 * @return wartość funkcji aktywacji
 *
 * Liczy sume iloczynu wektora wag i wektora wejściowego,
 * a nastepnie zwraca wynik funkcji aktywacji dla tej wartosci
 */
double Neuron::getValue(const QVector<double> *inputVec)
{
    double val1 = 0;
    for(int i=0; i<inputVec->size(); i++){
        val1 += inputVec->at(i) * weightVec.at(i);
    }
    return  af->getValue(val1);
}


/**
 * @brief Neuron::setWeights
 * @param weights - wektor wag
 *
 * Ustawia wektor wag dla neuronu
 */
void Neuron::setWeights(QVector<double> weights)
{
    this->weightVec = weights;
}
