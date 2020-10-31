#include "network/neuralnetwork.h"
#include "network/activationFunctions/sigmoidactivationfunction.h"
#include "network/activationFunctions/reluactivationfunction.h"
#include <QDebug>
#include <QtMath>

/**
 * @brief NeuralNetwork::NeuralNetwork
 * @param input - liczba neuronow warstwy wejsciowej
 * @param hidden - liczba neuronow warstwy ukrytej
 * @param output - liczba neuronow warstwy wyjsciowej
 *
 * Liczy calkowita liczbe wag w w sieci (potrzebne do algorytmu genetycznego)
 * i tworzy neurony dla poszczegolnych warstw
 */
NeuralNetwork::NeuralNetwork(int input, int hidden, int output):
    inputNeurons(input), hiddenNeurons(hidden), outputNeurons(output)
{
    nrOfWeights = (inputNeurons*hiddenNeurons) + (hiddenNeurons*outputNeurons);

    for(int i=0; i<hiddenNeurons; i++)
        hiddenLayer.push_back(Neuron(new ReluActivationFunction, inputNeurons));
    for(int i=0; i<outputNeurons; i++)
        outputLayer.push_back(Neuron(new SigmoidActivationFunction, hiddenNeurons));
    hiddenLayerOutput.fill(0, hiddenNeurons);
    outputLayerOutput.fill(0, outputNeurons);
}


/**
 * @brief NeuralNetwork::setAllWeights
 * @param allWeights - wskaznik do wektora ze wszystkimi wagami
 *
 * Przypisuje wagi z wektora ze wszystkimi wagami do
 * poszczegolnych neuronow
 */
void NeuralNetwork::setAllWeights(QVector<double> *allWeights)
{
    int index = 0;

    for(Neuron &n : hiddenLayer){
        n.setWeights(allWeights->mid(index, inputNeurons));
        index+=inputNeurons;
    }
    for(Neuron &n : outputLayer){
        n.setWeights(allWeights->mid(index, hiddenNeurons));
        index+=hiddenNeurons;
    }
}


/**
 * @brief NeuralNetwork::setInput
 * @param inputSet - wektor z danymi wejsciowymi
 *
 * Ustawia wektor z danymi wejsciowymi
 */
void NeuralNetwork::setInput(QVector<QVector<double> > *inputSet)
{
    this->input = inputSet;
}

/**
 * @brief NeuralNetwork::setOutputIndexes
 * @param outputIndexes - wektor z indeksami wyjsciowymi
 *
 * Ustawia indeksy danych, które mają być wyjsciem sieci
 */
void NeuralNetwork::setOutputIndexes(QVector<int> outputIndexes)
{
    this->outputIndexes = outputIndexes;
}

/**
 * @brief NeuralNetwork::getOutput
 * @param input - dane wejsciowe
 * @return wektor z wynikami wszystkich wyjsc sieci
 *
 * Liczy odpowiedz sieci dla podanych danych wejsciowych
 */
QVector<double> NeuralNetwork::getOutput(QVector<double> *input)
{
    for(int i=0; i<hiddenNeurons; i++){
       hiddenLayerOutput[i] = hiddenLayer[i].getValue(input);
    }

    for(int i=0; i<outputNeurons; i++){
        outputLayerOutput[i] = outputLayer[i].getValue(&hiddenLayerOutput);
    }
    return outputLayerOutput;
}


/**
 * @brief NeuralNetwork::getTotalError
 * @return suma bledow z kazdego rekordu
 *
 * Liczy sume bledow z kazdego rekordu
 */
double NeuralNetwork::getTotalError()
{
    QVector<double> errors;
    for(int i=0; i<input->size()-1; i++){
        QVector<double> currentRow = (*input)[i];
        QVector<double> out = getOutput(&(*input)[i]);

        double outputError = 0;
        for(int j=0; j<1; j++){//j<out.size()
            int currentOutputIndex = outputIndexes[j];
            outputError += qPow(out[j] - (*input)[i+1][currentOutputIndex], 2);
        }
        errors.push_back(outputError/outputIndexes.size());
    }

    double totalError = 0;
    for (double d : errors)
        totalError+=d;

    return totalError;
}

/**
 * @brief NeuralNetwork::getNrOfWeights
 * @return liczba wszystkich wag
 *
 * Zwraca liczbe wszystkich wag w calej sieci
 */
int NeuralNetwork::getNrOfWeights()
{
    return this->nrOfWeights;
}
