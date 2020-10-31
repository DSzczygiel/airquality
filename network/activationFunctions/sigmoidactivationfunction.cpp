#include "network/activationFunctions/sigmoidactivationfunction.h"
#include <QtMath>


SigmoidActivationFunction::SigmoidActivationFunction()
{

}

double SigmoidActivationFunction::getValue(double x)
{
    return(1.0/(1.0+qExp(-x)));
}
