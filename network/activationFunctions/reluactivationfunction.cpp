#include "network/activationFunctions/reluactivationfunction.h"
#include <algorithm>

ReluActivationFunction::ReluActivationFunction()
{

}

double ReluActivationFunction::getValue(double x)
{
    return std::max(0.0, x);
}
